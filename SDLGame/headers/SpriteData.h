#pragma once
#ifndef SpriteDataFile
#define SpriteDataFile
#include "include/SDL.h"
#include <string>
class SpriteData {
private:
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Point* centrePoint;
	std::string name;
public:
	SDL_Surface* GetSurface() const;
	SDL_Texture* GetTexture() const;
	std::string GetName() const;
	SDL_Point* GetCentrePoint() const;
	int InitialiseData(std::string& path);
	int CreateTextureSprite(SDL_Renderer * renderer);

	SpriteData();
	SpriteData(std::string& path);
	~SpriteData();
};

#endif