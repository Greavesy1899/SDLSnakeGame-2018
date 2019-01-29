#include "headers/SpriteCollectionManager.h"

int SpriteCollectionManager::CheckSpriteDataExistence(const std::string& name)
{
	int exists = 0;

	for (size_t i = 0; i != spriteData.size(); i++)
	{
		auto* sprite = spriteData.at(i);

		if (strcmp(sprite->GetName().c_str(), name.c_str()) == 0)
		{
			exists = 1;
			return exists;
		}
	}

	return exists;
}

SpriteData* SpriteCollectionManager::GetSpriteByName(const std::string& name)
{
	for (size_t i = 0; i != this->spriteData.size(); i++)
	{
		auto* sprite = spriteData.at(i);

		if (strcmp(sprite->GetName().c_str(), name.c_str()) == 0)
		{
			return sprite;
		}
	}

	return nullptr;
}

void SpriteCollectionManager::CreateTextures(SDL_Renderer* renderer)
{
	for (size_t i = 0; i < this->spriteData.size(); i++)
	{
		spriteData.at(i)->CreateTextureSprite(renderer);
	}
}

void SpriteCollectionManager::PushBack(SpriteData* data)
{
	if (CheckSpriteDataExistence(data->GetName()) == 0)
	{
		this->spriteData.push_back(data);
		SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Added sprite with name %s into the manager", data->GetName().c_str());
	}
	else
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Sprite %s already exists in manager; skipping", data->GetName().c_str());
	}
}

SpriteCollectionManager::SpriteCollectionManager()
{
	SDL_Log("Created sprite manager");
	spriteData = std::vector<SpriteData*>();
}

SpriteCollectionManager::~SpriteCollectionManager()
{
	SDL_Log("Cleaned sprite manager..");
	for (auto* data : spriteData)
		delete data;
	spriteData.clear();
	spriteData.shrink_to_fit();
}
