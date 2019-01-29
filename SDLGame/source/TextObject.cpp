#include "headers/TextObject.h"

void TextObject::Init(const std::string& name, const std::string& text, int x, int y)
{
	this->name = name;
	this->text = text;
	this->rectangle.x = x;
	this->rectangle.y = y;
	this->origin = Vector(this->rectangle.x, this->rectangle.y);
	this->color = SDL_Color{ 255, 255, 255, SDL_ALPHA_OPAQUE };
}

void TextObject::Input()
{

}

void TextObject::Update(TTF_Font* font, bool forceFree)
{
	if (forceFree && surface)
		SDL_FreeSurface(this->surface);

	this->surface = TTF_RenderText_Solid(font, this->text.c_str(), this->color);
}

void TextObject::Render(SDL_Renderer* renderer)
{
	if (surface)
	{
		if (surface->h == 0 && surface->w == 0)
			return;

		this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
		this->rectangle.h = this->surface->h;
		this->rectangle.w = this->surface->w;
		SDL_RenderCopy(renderer, this->texture, nullptr, &this->rectangle);

		if (debug)
		{
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_RenderDrawRect(renderer, &rectangle);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		}

		SDL_DestroyTexture(texture);	
	}
}

void TextObject::SetText(std::string text)
{
	this->text = text;
	SDL_FreeSurface(this->surface);
}

void TextObject::SetColor(SDL_Color color)
{
	this->color = color;
}

void TextObject::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_Color color = SDL_Color{ r, g, b, a };
	SetColor(color);
}

std::string TextObject::GetObjectType() const
{
	return this->ObjectType;
}

TextObject::TextObject(std::string &)
{
}

TextObject::TextObject(const TextObject & obj)
{
	this->name = obj.name;
	this->color = obj.color;
	this->surface = obj.surface;
	this->texture = obj.texture;
}

TextObject::TextObject()
{
}

TextObject::~TextObject()
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}
