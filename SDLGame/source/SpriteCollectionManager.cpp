#include "headers/SpriteCollectionManager.h"
#include "../include/tinyxml2.h"

void SpriteCollectionManager::ParseSpriteXML()
{
	std::string spriteFile = "Content/sprites.xml";

	SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Reading Sprites XML: %s", spriteFile.c_str());

	tinyxml2::XMLDocument doc;
	doc.LoadFile(spriteFile.c_str());

	if (doc.Error())
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "XML Reading error on [%s]. %s\n", spriteFile.c_str(), doc.ErrorStr());
	}

	tinyxml2::XMLElement* node = doc.RootElement();

	//get object data.
	tinyxml2::XMLElement* objectsNode = node->FirstChildElement("Sprites");
	for (const tinyxml2::XMLElement* child = objectsNode->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
	{
		SpriteData* data = new SpriteData();
		const char* name = child->Attribute("name");
		const char* path = child->GetText();
		data->InitialiseData(path, name);
		this->PushBack(data);
	}
}

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
	SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, "Created Sprite Manager");
	spriteData = std::vector<SpriteData*>();
	this->ParseSpriteXML();
}

SpriteCollectionManager::~SpriteCollectionManager()
{
	SDL_Log("Cleaned sprite manager..");
	for (auto* data : spriteData)
		delete data;
	spriteData.clear();
	spriteData.shrink_to_fit();
}
