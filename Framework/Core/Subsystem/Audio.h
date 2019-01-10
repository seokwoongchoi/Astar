#pragma once
#include "ISubsystem.h"

class Audio : public ISubsystem
{
public:
	Audio(class Context* context);
	virtual ~Audio();

	FMOD::System* GetFMODDevice() { return system; }
	void SetListener(class Transform* transform) { listener = transform; }

	void Initialize() override;
	void Update() override;

private:
	FMOD::System* system;//FMOD의 Device
	int maxChannel;//최대 재생목록수
	float distanceFactor;//거리 단위, 가중치
	int result; //FMOD의 함수가 잘 작동됬는지 체크(HRESULT)
	bool bInitialized; //오디오가 초기화됬는지 체크

	class Transform* listener;
};