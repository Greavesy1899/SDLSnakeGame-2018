#include "headers/SingletonManager.h"
#include <include/SDL_mixer.h>
Singleton* Singleton::instance = nullptr;
Singleton* Singleton::getInstance()
{
	if (instance == nullptr)
		instance = new Singleton();

	return instance;
}

int Singleton::GetGameState() const
{
	return this->gameState;
}

void Singleton::SetGameState(int gs)
{
	this->gameState = gs;
}

void Singleton::IncrementScore()
{
	this->score++;
}

void Singleton::ResetScore()
{
	this->score = 0;
}

int Singleton::GetScore() const
{
	return this->score;
}

int * Singleton::GetKeyMaps() const
{
	return this->keyMaps;
}

void Singleton::SetKeyMaps(int * keys)
{
	this->keyMaps = keys;
}

int Singleton::GetFPS() const
{
	return this->fps;
}

void Singleton::SetFPS(int val)
{
	this->fps = val;
}

bool Singleton::GetHasEatenGhostFood() const
{
	return this->eatenGhost;
}

void Singleton::SetHasEatenGhostFood(bool val)
{
	this->eatenGhost = val;
}

SpriteCollectionManager * Singleton::GetSpriteManager() const
{
	return this->spriteManager;
}

InputManager* Singleton::GetIM() const
{
	return this->inputManager;
}

AudioManager* Singleton::GetAM() const
{
	return this->audioManager;
}

Singleton::~Singleton()
{
	delete spriteManager;
	delete instance;
	delete inputManager;
	delete keyMaps;
}
Singleton::Singleton() 
{
	this->spriteManager = new SpriteCollectionManager();
	this->inputManager = new InputManager();
	this->audioManager = new AudioManager();
	this->keyMaps = new int[5];
}

