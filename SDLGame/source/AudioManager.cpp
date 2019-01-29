#include "headers/AudioManager.h"

bool AudioManager::GetSoundMuted() const
{
	return this->isSoundMuted;
}

void AudioManager::SetSoundMuted(bool val)
{
	this->isSoundMuted = val;
}

bool AudioManager::GetMusicMuted() const
{
	return this->isMusicMuted;
}

void AudioManager::SetMusicMuted(bool val)
{
	this->isMusicMuted = val;
}

int AudioManager::GetMusicVolume() const
{
	return this->musicVolume;
}

void AudioManager::SetMusicVolume(int val)
{
	this->musicVolume = val;
}

int AudioManager::GetSoundVolume() const
{
	return this->soundVolume;
}

void AudioManager::SetSoundVolume(int val)
{
	this->soundVolume = val;
}

int AudioManager::GetMusicChannel() const
{
	return this->musicChannel;
}

int AudioManager::GetSoundChannel() const
{
	return this->soundChannel;
}

AudioManager::~AudioManager() = default;

AudioManager::AudioManager()
{
	this->isMusicMuted = false;
	this->isSoundMuted = false;
	this->musicVolume = 100;
	this->soundVolume = 20;
}
