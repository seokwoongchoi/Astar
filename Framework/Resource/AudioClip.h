#pragma once
#include "IResource.h"

enum class PlayMode : uint
{
	Sound,
	Stream
};

class AudioClip : public IResource
{
public:
	AudioClip(class Context* context);
	AudioClip(const AudioClip& rhs);
	virtual ~AudioClip();

	void Play();
	void Pause();
	void Stop();
	void Update();

	void SetLoop(const bool& bLoop);
	void SetVolume(const float& volume);
	void SetMute(const bool& bMute);
	void SetPriority(const int& priority);
	void SetPitch(const float& pitch);
	void SetPan(const float& pan);

	const bool IsPlaying();

	void Write(Xml::XMLDocument& doc) override {}
	void Read(Xml::XMLElement* element) override {}

	void SaveToFile(const string & saveFilePath) override;
	void LoadFromFile(const string & loadFilePath) override;

private:
	void CreateSound(const string& filePath);
	void CreateStream(const string& filePath);

	const int GetSoundMode();
	const bool IsChannelValid();//ü���� ��ȿ���� �ƴ��� üũ

private:
	FMOD::System* system;
	FMOD::Sound* sound;//���� ��ü
	FMOD::Channel* channel;//������� ����

	class Transform* transform;
	PlayMode playMode;
	int loopMode;
	int rolloffMode;
	float minDistance;
	float maxDistance;
	int result;
};