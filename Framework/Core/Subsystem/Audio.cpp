#include "stdafx.h"
#include "Audio.h"

Audio::Audio(Context * context)
	: ISubsystem(context)
	, system(nullptr)
	, maxChannel(32)
	, distanceFactor(1.0f)
	, result(FMOD_OK)
	, listener(nullptr)
	, bInitialized(false)
{
}

Audio::~Audio()
{
	if (!bInitialized)
		return;

	result = system->close();
	assert(result == FMOD_OK);

	result = system->release();
	assert(result == FMOD_OK);
}

void Audio::Initialize()
{
	if (bInitialized)
		return;

	//FMOD ��ġ ����
	result = System_Create(&system);
	assert(result == FMOD_OK);

	//FMOD ���� üũ
	uint version = 0;
	result = system->getVersion(&version);
	assert(result == FMOD_OK);
	assert(version >= FMOD_VERSION);

	//�ý��ۿ� ���� ī�� ��ġ�� �ִ��� Ȯ��
	int driverCount = 0;
	result = system->getNumDrivers(&driverCount);
	assert(result == FMOD_OK);
	assert(driverCount > 0);

	//FMOD system �ʱ�ȭ
	result = system->init(maxChannel, FMOD_INIT_NORMAL, nullptr);
	assert(result == FMOD_OK);

	//FMOD 3D Setting
	result = system->set3DSettings
	(
		1.0f, //���÷� ������
		distanceFactor,
		0.0f // rolloff ���� ������
	);
	assert(result == FMOD_OK);

	bInitialized = true;
}

void Audio::Update()
{
	if (!bInitialized)
		return;

	result = system->update();
	assert(result == FMOD_OK);

	if (listener)
	{
		//TODO : Transform Ŭ���� ����� ó���Ұ�
	}
}
