#include "aiRandom.h"
#include <random>

namespace aiRandom
{
	std::random_device           rand_dev;
	std::mt19937                 generator(rand_dev());

	int aiRandom::getRandom(int minValue, int maxValue)
	{
		std::uniform_int_distribution<int>  distr(minValue, maxValue);
		return distr(generator);
	}
	int aiRandom::getRandom(int maxValue)
	{
		return getRandom(0, maxValue);
	}
}
