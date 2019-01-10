#include "stdafx.h"
#include "Timer.h"

Timer::Timer(Context * context)
	: ISubsystem(context)
	, deltaTimeMs(0.0f)
	, deltaTimeSec(0.0f)
{
}

Timer::~Timer()
{
}

void Timer::StopwatchStart()
{
	//스탑워치 시작시간을 현재시간으로 초기화
	stopwatchStartTime = chrono::high_resolution_clock::now();
}

const float Timer::GetStopwatchTimeMs()
{
	// -------- stopwatch start!!!
	//
	//
	//
	// -->GetStopwatchTImeMs() --------stopwatch stop!!


	chrono::duration<double, milli> ms
		= chrono::high_resolution_clock::now() - stopwatchStartTime;

	return static_cast<float>(ms.count());
}

const float Timer::GetStopwatchTimeSec()
{
	return GetStopwatchTimeMs() * 0.001f;
}

void Timer::Initialize()
{
	prevTime = chrono::high_resolution_clock::now();
}

void Timer::Update()
{
	auto curTime = chrono::high_resolution_clock::now();
	chrono::duration<double, milli> ms = curTime - prevTime;
	prevTime = curTime;

	deltaTimeMs  = static_cast<float>(ms.count());
	deltaTimeSec = static_cast<float>(ms.count() * 0.001f);
}
