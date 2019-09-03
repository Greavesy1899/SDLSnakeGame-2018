#include "headers/FoodController.h"
#include "headers/SingletonManager.h"
#include <time.h>

FoodControllerObject::FoodControllerObject(const std::string & name)
{
	Init(name);
}

FoodControllerObject::FoodControllerObject()
{
}

FoodControllerObject::~FoodControllerObject()
{
	delete food;
}

void FoodControllerObject::Init(const std::string& name)
{
	this->pickupAppleSound = Singleton::getInstance()->GetAM()->LookupAudioClip("AUD_APPLE_PICKUP");
	this->pickupPowerupSound = Singleton::getInstance()->GetAM()->LookupAudioClip("AUD_POWER_PICKUP");
	std::string foodPath = "content/apple_sprite.png";
	std::string ghostPath = "content/power_ghost.png";

	auto* foodData = new SpriteData(foodPath);
	auto* ghostData = new SpriteData(ghostPath);

	Singleton::getInstance()->GetSpriteManager()->PushBack(foodData);
	Singleton::getInstance()->GetSpriteManager()->PushBack(ghostData);
	srand(time(NULL));
	this->name = name;
	SpawnFood();
	SDL_Log("Food controller has initialized..");
}

void FoodControllerObject::Input()
{
}

void FoodControllerObject::Update()
{
}

void FoodControllerObject::Render(SDL_Renderer* renderer)
{
	food->Render(renderer);
}

void FoodControllerObject::SpawnFood()
{
	curType = rand() % 2;
	SpriteData* obj = nullptr;

	if(curType == 0)
		obj = Singleton::getInstance()->GetSpriteManager()->GetSpriteByName("content/apple_sprite.png");
	else
		obj = Singleton::getInstance()->GetSpriteManager()->GetSpriteByName("content/power_ghost.png");

	int randX = 0, randY = 0;

	while(!(randX > 48 && randX < 592))
		randX = rand() % 640;

	while(!(randY > 80 && randY < 432))
		randY = rand() % 480;

	SDL_Log("Random values %i, %i", randX, randY);

	food = new GameObject();
	food->Init("Food", obj, 3, randX, randY);


}

void FoodControllerObject::EatenFood()
{
	switch(curType)
	{
	case 0:
		Singleton::getInstance()->IncrementScore();
			this->pickupAppleSound->Play();
		break;
	case 1:
		Singleton::getInstance()->IncrementScore();
		Singleton::getInstance()->SetHasEatenGhostFood(true);
		this->pickupPowerupSound->Play();
		break;
	default:
		break;
	}
	
	SpawnFood();
}

std::string FoodControllerObject::GetObjectType() const
{
	return FoodControllerObject::ObjectType;
}
