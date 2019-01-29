#ifndef AudioManagerFile
#define AudioManagerFile
class AudioManager
{
private:
	bool isMusicMuted;
	bool isSoundMuted;
	int musicVolume;
	int soundVolume;
	int musicChannel = 0;
	int soundChannel = 1;
public:
	bool GetSoundMuted() const;
	void SetSoundMuted(bool val);
	bool GetMusicMuted() const;
	void SetMusicMuted(bool val);
	int GetMusicVolume() const;
	void SetMusicVolume(int val);
	int GetSoundVolume() const;
	void SetSoundVolume(int val);
	int GetMusicChannel() const;
	int GetSoundChannel() const;

	//constructor/destructor
	~AudioManager();
	AudioManager();
	AudioManager(const AudioManager &im) = delete;
	AudioManager(AudioManager &&im) = delete;

	//operators.
	AudioManager operator=(const AudioManager &im) = delete;
	AudioManager operator=(AudioManager &&im) = delete;
};
#endif
