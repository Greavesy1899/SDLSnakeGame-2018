#pragma once
#ifndef TextObjectFile
#define TextObjectFile
#include "include/SDL.h"
#include <string>
#include "NewGameObject.h"
#include <include/SDL_ttf.h>
#include "SZ_Timer.h"
#include "Vector.h"

class TextObject : public GameObject {
public:
	//functions
	void Init(const std::string& name, const std::string& text, int x, int y);
	void Input();
	void Update(TTF_Font* font, bool forceFree = false);
	void Render(SDL_Renderer* renderer);
	void SetText(std::string text);
	void SetColor(SDL_Color color);
	void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	std::string GetObjectType() const override;

	//constructors/destructors.
	TextObject(std::string&);
	TextObject(const TextObject& obj);
	TextObject();
	~TextObject();

private:
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Color color;
	std::string text;
	std::string ObjectType = "TextObject";
	Vector origin;
};
#endif