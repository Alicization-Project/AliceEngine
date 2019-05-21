#include "aiTimer.h"
#include "aiHelper.h"

double aiTimer::PCFreq = 0;
__int64 aiTimer::CounterStart = 0;

aiTimer::aiTimer()
{
	if (CounterStart == 0)
		Start();
	record();
}


aiTimer::~aiTimer()
{
}

void aiTimer::Start()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		aiHelper::messageBox("QueryPerformanceFrequency failed!\n");

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double aiTimer::TotalTime()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

void aiTimer::record()
{
	lastTime = TotalTime();
}
double aiTimer::elapsed()
{
	return TotalTime() - lastTime;
}