#include "headers/AudioManager.h"
#include "../include/tinyxml2.h"

bool AudioManager::GetSoundMuted() const
{
	return this->isSoundMuted;
}

void AudioManager::SetSoundMuted(bool val)
{
	SDL_LogCritical(SDL_LOG_CATEGORY_AUDIO, "isSoundMuted: %i", val);
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

AudioClip* AudioManager::LookupAudioClip(std::string name)
{
	for (auto clip : this->clips)
	{
		if (clip->GetName() == name)
			return clip;
	}

	SDL_LogCritical(SDL_LOG_CATEGORY_AUDIO, "AudioManager.cpp: Failed to retrieve AudioClip %s ", name.c_str());
	return nullptr;
}

AudioManager::~AudioManager()
{
	for (int i = 0; i != this->clips.size(); i++)
		delete this->clips[i];

	this->clips = std::vector<AudioClip*>();
}

void AudioManager::ParseAudioFile()
{
	std::string audioFile = "Content/audio.xml";

	SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Reading Audio XML: %s", audioFile.c_str());

	tinyxml2::XMLDocument doc;
	doc.LoadFile(audioFile.c_str());

	if (doc.Error())
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "XML Reading error on [%s]. %s\n", audioFile.c_str(), doc.ErrorStr());
	}

	tinyxml2::XMLElement* node = doc.RootElement();

	//get object data.
	tinyxml2::XMLElement * objectsNode = node->FirstChildElement("AudioClips");
	for (const tinyxml2::XMLElement* child = objectsNode->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
	{
		AudioClip* clip = new AudioClip();
		int volume = child->IntAttribute("volume");
		int channel = child->IntAttribute("channel");
		bool loop = child->BoolAttribute("loop");
		const char* name = child->Attribute("name");
		const char* path = child->GetText();
		clip->Init(path, name, volume, channel, loop);
		this->clips.push_back(clip);		
	}
}
AudioManager::AudioManager()
{
	this->isMusicMuted = false;
	this->isSoundMuted = false;
	this->musicVolume = 100;
	this->soundVolume = 20;
	this->clips = std::vector<AudioClip*>();
	this->ParseAudioFile();
}
