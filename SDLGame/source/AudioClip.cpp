#include "..\headers\AudioClip.h"
#include "../headers/SingletonManager.h"

void AudioClip::Init(std::string path, std::string name, int volume, int channel, bool isLooped)
{
	this->chunk = Mix_LoadWAV(path.c_str());
	this->channel = channel;
	this->volume = volume;
	this->isLooped = isLooped;
	this->name = name;


	if(this->chunk == nullptr)
		SDL_LogCritical(SDL_LOG_CATEGORY_AUDIO, "AudioClip.cpp: Failed to load audio clip %s", path.c_str());

	Mix_VolumeChunk(this->chunk, this->volume);
	SDL_LogCritical(SDL_LOG_CATEGORY_AUDIO, "Loaded Audio Clip: %s", path.c_str());
}

void AudioClip::Play()
{
	bool isSoundMuted = Singleton::getInstance()->GetAM()->GetSoundMuted();
	if(this->chunk != nullptr && this->channel == 0) //for music
		Mix_PlayChannel(this->channel, this->chunk, this->isLooped ? -1 : 0);

	if (this->chunk != nullptr && !isSoundMuted)
		Mix_PlayChannel(this->channel, this->chunk, this->isLooped ? -1 : 0);
}

void AudioClip::SetVolume(int volume)
{
	this->volume = volume;
	Mix_VolumeChunk(this->chunk, this->volume);
}

int AudioClip::GetVolume() const
{
	return this->volume;
}

void AudioClip::SetChannel(int channel)
{
	this->channel = channel;
}

int AudioClip::GetChannel() const
{
	return this->channel;
}

std::string AudioClip::GetName() const
{
	return this->name;
}

AudioClip::AudioClip()
{
	this->chunk = nullptr;
	this->channel = 0;
	this->volume = 0;
	this->isLooped = false;
}

AudioClip::~AudioClip()
{
	Mix_FreeChunk(this->chunk);
}
