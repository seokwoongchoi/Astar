#include "stdafx.h"
#include "AudioSource.h"

void AudioSource::SetIsMute(const bool & bMute)
{
	if (this->bMute == bMute)
		return;

	this->bMute = bMute;
	audioClip->SetMute(bMute);
}

void AudioSource::SetPriority(const int & priority)
{
}

void AudioSource::SetVolume(const float & volume)
{
	if (this->volume = volume)
		return;

	this->volume = Math::Clamp(volume, 0.0f, 1.0f);
	audioClip->SetVolume(this->volume);
}

void AudioSource::SetPitch(const float & pitch)
{
	if (this->pitch = pitch)
		return;

	this->pitch = Math::Clamp(pitch, 0.0f, 3.0f);
	audioClip->SetPitch(this->pitch);
}

void AudioSource::SetPan(const float & pan)
{
	if (this->pan = pan)
		return;

	this->pan = Math::Clamp(pan, -1.0f, 1.0f);
	audioClip->SetPan(this->pan);
}
