#pragma once
#include "ISubsystem.h"

class Timer : public ISubsystem
{
public:
	Timer(class Context* context);
	virtual ~Timer();

	//��ž��ġ ��ŸƮ
	void StopwatchStart();

	//��ž��ġ ��ž
	const float GetStopwatchTimeMs();
	const float GetStopwatchTimeSec();

	const float& GetDeltaTimeMs() const { return deltaTimeMs; }
	const float& GetDeltaTimeSec() const { return deltaTimeSec; }

	void Initialize() override;
	void Update() override;

private:
	float deltaTimeMs;
	float deltaTimeSec;

	chrono::high_resolution_clock::time_point prevTime;
	chrono::high_resolution_clock::time_point stopwatchStartTime;
};