#include "stdafx.h"
#include "AudioClip.h"

AudioClip::AudioClip(Context * context)
	: IResource(context)
	, sound(nullptr)
	, channel(nullptr)
	, transform(nullptr)
	, playMode(PlayMode::Sound)
	, minDistance(1.0f)
	, maxDistance(10000.0f)
	, loopMode(FMOD_LOOP_OFF)
	, rolloffMode(FMOD_3D_LINEARROLLOFF)
{
	system = context->GetSubsystem<Audio>()->GetFMODDevice();
}

AudioClip::AudioClip(const AudioClip & rhs)
	: IResource(rhs.context)
	, sound(nullptr)
	, channel(nullptr)
	, transform(nullptr)
	, playMode(rhs.playMode)
	, minDistance(rhs.minDistance)
	, maxDistance(rhs.maxDistance)
	, loopMode(rhs.loopMode)
	, rolloffMode(rhs.rolloffMode)
{
	system = rhs.system;
	LoadFromFile(rhs.filePath);
}

AudioClip::~AudioClip()
{
	if (!sound)
		return;

	result = sound->release();
	assert(result == FMOD_OK);
}

void AudioClip::Play()
{
	//사운드가 플레이 중인지 체크
	if (IsChannelValid())
	{
		bool bPlaying = false;
		result = channel->isPlaying(&bPlaying);
		assert(result == FMOD_OK);
		
		//현재 플래이 중이면 리턴
		if (bPlaying)
			return;
	}

	//사운드 플레이
	result = system->playSound(sound, nullptr, false, &channel);
	assert(result == FMOD_OK);
}

void AudioClip::Pause()
{
	if (!IsChannelValid())
		return;

	//사운드가 일시정지상태인지 체크
	bool bPause = false;
	result = channel->getPaused(&bPause);
	assert(result == FMOD_OK);

	if (bPause)
		return;
	
	//사운드 일시정지
	result = channel->setPaused(true);
	assert(result == FMOD_OK);
}

void AudioClip::Stop()
{
	if (!IsChannelValid())
		return;

	//사운드가 플레이 중인지 체크
	if (!IsPlaying())
		return;

	//사운드 중지
	result = channel->stop();
	assert(result == FMOD_OK);

	channel = nullptr;
}

void AudioClip::Update()
{
	if (!IsChannelValid() || !transform)
		return;

	//TODO : Transform 만들고 처리할것
}

void AudioClip::SetLoop(const bool & bLoop)
{
	loopMode = bLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;

	if (!sound)
		return;

	if (bLoop)
	{
		result = sound->setLoopCount(-1);
		assert(result == FMOD_OK);
	}

	result = sound->setMode(GetSoundMode());
	assert(result == FMOD_OK);
}

void AudioClip::SetVolume(const float & volume)
{
	if (!IsChannelValid())
		return;

	result = channel->setVolume(volume);
	assert(result == FMOD_OK);
}

void AudioClip::SetMute(const bool & bMute)
{
	if (!IsChannelValid())
		return;

	result = channel->setMute(bMute);
	assert(result == FMOD_OK);
}

void AudioClip::SetPriority(const int & priority)
{
	if (!IsChannelValid())
		return;

	result = channel->setPriority(priority);
	assert(result == FMOD_OK);
}

void AudioClip::SetPitch(const float & pitch)
{
	if (!IsChannelValid())
		return;

	result = channel->setPitch(pitch);
	assert(result == FMOD_OK);
}

void AudioClip::SetPan(const float & pan)
{
	if (!IsChannelValid())
		return;

	result = channel->setPan(pan);
	assert(result == FMOD_OK);
}

const bool AudioClip::IsPlaying()
{
	if (!IsChannelValid())
		return false;

	bool bPlaying = false;
	result = channel->isPlaying(&bPlaying);
	assert(result == FMOD_OK);

	return bPlaying;
}

void AudioClip::SaveToFile(const string & saveFilePath)
{
}

void AudioClip::LoadFromFile(const string & loadFilePath)
{
	switch (playMode)
	{
	case PlayMode::Sound: CreateSound(loadFilePath); break;
	case PlayMode::Stream: CreateStream(loadFilePath); break;
	}
}

void AudioClip::CreateSound(const string & filePath)
{
	result = system->createSound
	(
		filePath.c_str(),
		GetSoundMode(),
		nullptr,
		&sound
	);
	assert(result == FMOD_OK);

	result = sound->set3DMinMaxDistance(minDistance, maxDistance);
	assert(result == FMOD_OK);
}

void AudioClip::CreateStream(const string & filePath)
{
	result = system->createStream
	(
		filePath.c_str(),
		GetSoundMode(),
		nullptr,
		&sound
	);
	assert(result == FMOD_OK);

	result = sound->set3DMinMaxDistance(minDistance, maxDistance);
	assert(result == FMOD_OK);
}

const int AudioClip::GetSoundMode()
{
	return FMOD_3D | loopMode | rolloffMode;
}

const bool AudioClip::IsChannelValid()
{
	if (!channel)
		return false;

	bool dummy;
	return channel->isPlaying(&dummy) == FMOD_OK;
}
