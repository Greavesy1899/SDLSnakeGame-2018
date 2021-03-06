#include <iostream>
#include "include/SDL.h"
#include "headers/SingletonManager.h"
#include "headers/GameManager.h"
#include "headers/SZ_timer.h"
#include "headers/FileLogger.h"
#include "include/SDL_ttf.h"
#include "include/SDL_image.h"
#include "include/SDL_mixer.h"
#include "headers/DiscordManager.h"

SZ_Timer aTimer;
const int FPS = 5;
const int DELTA_TIME = 1000 / FPS;
bool isRunning = false;

int main(int argc, char** argv)
{
	DiscordManager::Init();
	DiscordManager::UpdatePresence("On the main menu.", true);
	GameManager* gameManager = new GameManager();
	FileLogger* logger = new FileLogger("game-log.txt");

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_LogError(SDL_LOG_PRIORITY_CRITICAL, "SDL did not initialise!");
		return 1;
	}

	if (IMG_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_LogError(SDL_LOG_PRIORITY_CRITICAL, "SDL_IMG did not initialise!");
		return 1;
	}

	if (TTF_Init() < 0)
	{
		SDL_LogError(SDL_LOG_PRIORITY_CRITICAL, "SDL_TTF did not initialise!");
		return 1;
	}

	if(Mix_Init(MIX_INIT_MP3) < 0)
	{
		SDL_LogError(SDL_LOG_PRIORITY_CRITICAL, "SDL_Mixer did not initialise!");
		return 1;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		SDL_LogError(SDL_LOG_PRIORITY_CRITICAL, "OpenAudio() Failed");
		return 1;
	}

	Singleton::getInstance();
	Singleton::getInstance()->SetFPS(60);


	SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "SDL has initialized.");
	SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "SDL_Image has initialized.");
	SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "SDL_TTF has initialized");
	SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "SDL_Mixer has initialized");
	gameManager->Init();
	while (gameManager->GetRunning())
	{
		aTimer.resetTicksTimer();
		gameManager->Input();
		gameManager->Update();
		gameManager->Render();
		const int fps = 1000/Singleton::getInstance()->GetFPS();
		if (aTimer.getTicks() < fps)
		{
			SDL_Delay(fps - aTimer.getTicks());
		}
	}

	delete gameManager;
	SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "SDL_Image will close.");
	SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "SDL TTF will close.");
	SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "SDL_Mixer will close.");
	SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "SDL will close.");
	IMG_Quit();
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
	Discord_Shutdown();
	delete logger;
	return 0;
}