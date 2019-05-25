/*
 * This program uses the device CURAND API to calculate what
 * proportion of quasi-random 3D points fall within a sphere
 * of radius 1, and to derive the volume of the sphere.
 *
 * In particular it uses 64 bit scrambled Sobol direction
 * vectors from the file sobol_direction_vectors.h, to
 * generate double precision uniform samples.
 *
 */

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <curand_kernel.h>
#include <curand.h>

#define THREADS_PER_BLOCK 64
#define BLOCK_COUNT 64
#define TOTAL_THREADS (THREADS_PER_BLOCK * BLOCK_COUNT)

 /* Number of 64-bit vectors per dimension */
#define VECTOR_SIZE 64


#define CUDA_CALL(x) do { if((x) != cudaSuccess) { \
    printf("Error at %s:%d\n",__FILE__,__LINE__); \
    return EXIT_FAILURE;}} while(0)

#define CURAND_CALL(x) do { if((x) != CURAND_STATUS_SUCCESS) { \
    printf("Error at %s:%d\n",__FILE__,__LINE__); \
    return EXIT_FAILURE;}} while(0)

/* This kernel initializes state per thread for each of x, y, and z */

__global__ void setup_kernel(unsigned long long * sobolDirectionVectors,
	unsigned long long *sobolScrambleConstants,
	curandStateScrambledSobol64 *state)
{
	int id = threadIdx.x + blockIdx.x * THREADS_PER_BLOCK;
	int dim = 3 * id;
	/* Each thread uses 3 different dimensions */
	curand_init(sobolDirectionVectors + VECTOR_SIZE * dim,
		sobolScrambleConstants[dim],
		1234,
		&state[dim]);

	curand_init(sobolDirectionVectors + VECTOR_SIZE * (dim + 1),
		sobolScrambleConstants[dim + 1],
		1234,
		&state[dim + 1]);

	curand_init(sobolDirectionVectors + VECTOR_SIZE * (dim + 2),
		sobolScrambleConstants[dim + 2],
		1234,
		&state[dim + 2]);
}

/* This kernel generates random 3D points and increments a counter if
 * a point is within a unit sphere
 */
__global__ void generate_kernel(curandStateScrambledSobol64 *state,
	int n,
	long long int *result)
{
	int id = threadIdx.x + blockIdx.x * THREADS_PER_BLOCK;
	int baseDim = 3 * id;
	long long int count = 0;
	double x, y, z;

	/* Generate quasi-random double precision coordinates */
	for (int i = 0; i < n; i++) {
		x = curand_uniform_double(&state[baseDim]);
		y = curand_uniform_double(&state[baseDim + 1]);
		z = curand_uniform_double(&state[baseDim + 2]);

		/* Check if within sphere of radius 1 */
		if ((x*x + y * y + z * z) < 1.0) {
			count++;
		}
	}
	/* Store results */
	result[id] += count;
}

int main(int argc, char *argv[])
{
	int i;
	long long total;
	curandStateScrambledSobol64 *devSobol64States;
	curandDirectionVectors64_t *hostVectors64;
	unsigned long long int * hostScrambleConstants64;
	unsigned long long int * devDirectionVectors64;
	unsigned long long int * devScrambleConstants64;
	long long int *devResults, *hostResults;
	int sampleCount = 10000;
	int iterations = 100;
	double fraction;
	double pi = 3.1415926535897932;

	/* Allow over-ride of sample count */
	if (argc == 2) {
		sscanf(argv[1], "%d", &sampleCount);
	}

	/* Allocate space for results on host */
	hostResults = (long long int*)calloc(TOTAL_THREADS,
		sizeof(long long int));

	/* Allocate space for results on device */
	CUDA_CALL(cudaMalloc((void **)&devResults,
		TOTAL_THREADS * sizeof(long long int)));

	/* Set results to 0 */
	CUDA_CALL(cudaMemset(devResults, 0,
		TOTAL_THREADS * sizeof(long long int)));

	/* Get pointers to the 64 bit scrambled direction vectors and constants*/
	CURAND_CALL(curandGetDirectionVectors64(&hostVectors64,
		CURAND_SCRAMBLED_DIRECTION_VECTORS_64_JOEKUO6));

	CURAND_CALL(curandGetScrambleConstants64(&hostScrambleConstants64));


	/* Allocate memory for 3 states per thread (x, y, z), each state to get a unique dimension */
	CUDA_CALL(cudaMalloc((void **)&devSobol64States,
		TOTAL_THREADS * 3 * sizeof(curandStateScrambledSobol64)));

	/* Allocate memory and copy 3 sets of vectors per thread to the device */

	CUDA_CALL(cudaMalloc((void **)&(devDirectionVectors64),
		3 * TOTAL_THREADS * VECTOR_SIZE * sizeof(long long int)));

	CUDA_CALL(cudaMemcpy(devDirectionVectors64, hostVectors64,
		3 * TOTAL_THREADS * VECTOR_SIZE * sizeof(long long int),
		cudaMemcpyHostToDevice));

	/* Allocate memory and copy 3 scramble constants (one costant per dimension)
	   per thread to the device */

	CUDA_CALL(cudaMalloc((void **)&(devScrambleConstants64),
		3 * TOTAL_THREADS * sizeof(long long int)));

	CUDA_CALL(cudaMemcpy(devScrambleConstants64, hostScrambleConstants64,
		3 * TOTAL_THREADS * sizeof(long long int),
		cudaMemcpyHostToDevice));

	/* Initialize the states */

	setup_kernel << <BLOCK_COUNT, THREADS_PER_BLOCK >> > (devDirectionVectors64,
		devScrambleConstants64,
		devSobol64States);

	/* Generate and count quasi-random points  */

	for (i = 0; i < iterations; i++) {
		generate_kernel << <BLOCK_COUNT, THREADS_PER_BLOCK >> > (devSobol64States, sampleCount, devResults);
	}

	/* Copy device memory to host */

	CUDA_CALL(cudaMemcpy(hostResults,
		devResults,
		TOTAL_THREADS * sizeof(long long int),
		cudaMemcpyDeviceToHost));

	/* Tally and show result */

	total = 0;
	for (i = 0; i < TOTAL_THREADS; i++) {
		total += hostResults[i];
	}

	fraction = (double)total / ((double)TOTAL_THREADS * (double)sampleCount * (double)iterations);
	printf("Fraction inside sphere was %g\n", fraction);
	printf("(4/3) pi = %g, sampled volume = %g\n", (4.0*pi / 3.0), 8.0 * fraction);

	/* Cleanup */

	CUDA_CALL(cudaFree(devSobol64States));
	CUDA_CALL(cudaFree(devDirectionVectors64));
	CUDA_CALL(cudaFree(devScrambleConstants64));
	CUDA_CALL(cudaFree(devResults));
	free(hostResults);
	printf("^^^^ kernel_sobol_example PASSED\n");


	return EXIT_SUCCESS;
}