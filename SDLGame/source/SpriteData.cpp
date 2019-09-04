#include "..\headers\SpriteData.h"
#include <include/SDL_image.h>

SDL_Surface * SpriteData::GetSurface() const
{
	return this->surface;
}

SDL_Texture * SpriteData::GetTexture() const
{
	return this->texture;
}

std::string SpriteData::GetName() const
{
	return this->name;
}

SDL_Point* SpriteData::GetCentrePoint() const
{
	return this->centrePoint;
}

int SpriteData::InitialiseData(std::string path, std::string name)
{
	this->name = name;
	this->surface = IMG_Load(path.c_str());

	if (this->surface == nullptr)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, "Failed to load %s", path.c_str());
	}

	this->centrePoint = new SDL_Point{ surface->w / 2, surface->h / 2 };
	return 0;
}

int SpriteData::CreateTextureSprite(SDL_Renderer* renderer)
{
	if (this->texture != nullptr)
		return 1;
	
	this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);

	if (!this->texture)
		return -1;

	return 0;
}

SpriteData::SpriteData()
{
	this->name = "NULL";
	this->centrePoint = new SDL_Point();
	surface = nullptr;
	texture = nullptr;
}

//SpriteData::SpriteData(std::string& path)
//{
//	this->InitialiseData(path);
//}

SpriteData::~SpriteData()
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	delete centrePoint;
}
