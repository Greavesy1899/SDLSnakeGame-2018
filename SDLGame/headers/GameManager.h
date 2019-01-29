#ifndef GameManagerFile
#define GameManagerFile
#include "include/SDL.h"
#include "SceneManager.h"
#include "Menu.h"

class GameManager {
private:
	bool isRunning;
	SceneManager* sceneManager;
	SDL_Window* window;
	int windowID;
	Mix_Chunk* music;
	bool isMusicOn;
	void HandleMusic();
	void HandlePausing();
public:
	GameManager();
	~GameManager();
	int LoadConfig() const;
	bool GetRunning() const;
	void Init();
	void Input();
	void Update();
	void Render() const;
};
#endif