#ifndef AudioClip_H
#define AudioClip_H
#include <include/SDL_mixer.h>
#include <include/SDL.h>
#include <string>

class AudioClip
{
	Mix_Chunk* chunk;
	int volume;
	int channel;
	bool isLooped;
	std::string name;

public:
	void Init(std::string text, std::string name, int volume, int channel, bool isLooped);
	void Play();


	//accessors
	void SetVolume(int volume);
	int GetVolume() const;
	void SetChannel(int channel);
	int GetChannel() const;
	std::string GetName() const;

	AudioClip();
	~AudioClip();
};

#endif