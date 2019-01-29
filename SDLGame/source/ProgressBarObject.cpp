#include "headers/ProgressBarObject.h"
#include "headers/FoodController.h"

ProgressBarObject::ProgressBarObject(std::string name)
{
	this->name = name;
}

ProgressBarObject::ProgressBarObject()
{
}

ProgressBarObject::~ProgressBarObject()
{
}

void ProgressBarObject::Init(std::string name, int x, int y, int time, int width)
{
	this->color.r = 255;
	this->color.g = 0;
	this->color.b = 0;
	this->color.a = SDL_ALPHA_OPAQUE;
	this->name = name;
	this->rectangle.x = x;
	this->rectangle.y = y;
	this->maxTime = time;
	this->maxWidth = width;
	this->rectangle.h = 32;
	this->totalTicks = 0;
	this->iteration = ceil(this->maxWidth / this->maxTime)+1;
	timer.resetTicksTimer();
}
void ProgressBarObject::Input()
{
}

void ProgressBarObject::Update()
{
	if (timer.getTicks() >= 1000)
	{
		if (this->rectangle.w < this->maxWidth)
			this->rectangle.w += this->iteration;
		else
			this->rectangle.w = this->maxWidth;

		totalTicks += 1000;
		timer.resetTicksTimer();
	}
}

void ProgressBarObject::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &this->rectangle);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &this->rectangle);
}

void ProgressBarObject::SetColor(SDL_Color color)
{
	this->color = color;
}

void ProgressBarObject::SetTime(int maxTime)
{
	this->maxTime = maxTime;
}

void ProgressBarObject::SetMaxWidth(int maxWidth)
{
	this->maxWidth = maxWidth;
}

int ProgressBarObject::GetTicks() const
{
	return this->totalTicks;
}

std::string ProgressBarObject::GetObjectType() const
{
	return ProgressBarObject::ObjectType;
}