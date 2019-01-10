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
	FMOD::System* system;//FMOD�� Device
	int maxChannel;//�ִ� �����ϼ�
	float distanceFactor;//�Ÿ� ����, ����ġ
	int result; //FMOD�� �Լ��� �� �۵������ üũ(HRESULT)
	bool bInitialized; //������� �ʱ�ȭ����� üũ

	class Transform* listener;
};