#pragma once
#ifndef FoodControllerFile
#define FoodControllerFile
#include "headers/NewGameObject.h"
#include <vector>
#include <include/SDL_mixer.h>
#include "AudioClip.h"

class FoodControllerObject : public GameObject
{
public:
	FoodControllerObject(const std::string& name);
	FoodControllerObject();
	~FoodControllerObject();

	void Init(const std::string& name);
	void Input();
	void Update();
	void Render(SDL_Renderer*);
	void SpawnFood();
	void EatenFood();
	GameObject* food;
	std::string GetObjectType() const;
private:
	std::string ObjectType = "FoodController";
	int curType;
	AudioClip* pickupAppleSound;
	AudioClip* pickupPowerupSound;
};
#endif
