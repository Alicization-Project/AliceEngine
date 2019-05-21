#pragma once

class aiTimer
{
private:
	static double PCFreq;
	static __int64 CounterStart;

	double lastTime;
public:
	aiTimer();
	~aiTimer();

	static void Start();
	static double TotalTime();

	//start recording
	void record();
	//elapsed time since record()
	double elapsed();
};