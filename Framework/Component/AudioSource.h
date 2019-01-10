#pragma once

class AudioSource
{
public:
	AudioSource(class Context* context);
	virtual ~AudioSource();

	void Initialize();
	void Update();

	void SetAudioClip(AudioClip* audioClip);

	void Play();
	void Stop();

	const bool& GetIsPlay() const { return bPlay; }
	const bool& GetIsLoop() const { return bLoop; }
	const bool& GetIsMute() const { return bMute; }
	const int& GetPriority() const { return priority; }
	const float& GetVolume() const { return volume; }
	const float& GetPitch() const { return pitch; }
	const float& GetPan() const { return pan; }

	void SetIsPlay(const bool& bPlay) { this->bPlay = bPlay; }
	void SetIsLoop(const bool& bLoop) { this->bLoop = bLoop; }
	void SetIsMute(const bool& bMute);
	void SetPriority(const int& priority);
	void SetVolume(const float& volume);
	void SetPitch(const float& pitch);
	void SetPan(const float& pan);

private:
	class Context* context;
	class AudioClip* audioClip;
	string filePath;	
	bool bPlay;
	bool bMute;
	bool bLoop;
	int priority;
	float volume;
	float pitch;
	float pan;
};