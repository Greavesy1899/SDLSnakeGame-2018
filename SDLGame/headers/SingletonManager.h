#ifndef SingletonManagerFile
#define SingletonManagerFile
#include "include/SDL.h"
#include "headers/SpriteCollectionManager.h"
#include "InputManager.h"
#include "AudioManager.h"

class Singleton
{
private:
	static Singleton* instance;
	SpriteCollectionManager* spriteManager;
	InputManager* inputManager;
	AudioManager* audioManager;
	int* keyMaps;
	int gameState; //0 = playing; 1 = paused; 2 = game over, 3 = main menu, 4 = option, 5 = exit.
	int score;
	int fps;
	bool eatenGhost;

public:
	static Singleton* getInstance();
	int GetGameState() const;
	void SetGameState(int gs);
	void IncrementScore();
	void ResetScore();
	int GetScore() const;
	int* GetKeyMaps() const;
	void SetKeyMaps(int* keys);
	int GetFPS() const;
	void SetFPS(int val);
	bool GetHasEatenGhostFood() const;
	void SetHasEatenGhostFood(bool val);
	SpriteCollectionManager* GetSM() const;
	InputManager* GetIM() const;
	AudioManager* GetAM() const;

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

private:
	Singleton();
	~Singleton();
};
#endif