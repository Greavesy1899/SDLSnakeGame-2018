#include "headers/NewGameObject.h"

void GameObject::Init(std::string &name)
{
	this->name = name;
	this->rectangle = SDL_Rect{ 0, 0, 0, 0 };
	this->spriteData = nullptr;
	this->collisionMat = 0;
}

void GameObject::Init(const std::string& name, SpriteData* data, int colType, int x, int y)
{
	this->name = name;
	this->spriteData = data;
	this->collisionMat = colType;
	rectangle = SDL_Rect{ x, y, data->GetSurface()->w, data->GetSurface()->h };
}

void GameObject::Init(const std::string& name, int colType, int x, int h, int y, int w)
{
	this->name = name;
	this->spriteData = nullptr;
	this->collisionMat = colType;
	rectangle = SDL_Rect{ x, y, w, h };
}

void GameObject::Input()
{
}

void GameObject::Update()
{
}

void GameObject::Render(SDL_Renderer * renderer)
{
	if (this->spriteData)
	{
		//this->GetSpriteData()->CreateTextureSprite(renderer);
		SDL_RenderCopyEx(renderer, this->spriteData->GetTexture(), nullptr, &rectangle, this->rotation, this->spriteData->GetCentrePoint(), SDL_FLIP_NONE);
	}

	if(debug && this->collisionMat != 0)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(renderer, &rectangle);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	}
}

int GameObject::GetCollisionType() const
{
	return this->collisionMat;
}

std::string GameObject::GetName() const
{
	return this->name;
}

SpriteData * GameObject::GetSpriteData() const
{
	return this->spriteData;
}

void GameObject::SetSpriteData(SpriteData* sprite)
{
	this->spriteData = sprite;
}

int GameObject::GetRotation() const
{
	return this->rotation;
}

void GameObject::SetRotation(int value)
{
	this->rotation = value;
}

bool GameObject::CheckCollision(SDL_Rect rect1, SDL_Rect rect2)
{
	//Rect1
	int left1 = rect1.x;
	int right1 = rect1.x + rect1.w;
	int top1 = rect1.y;
	int bottom1 = rect1.y + rect1.h;

	//Rect2
	int left2 = rect2.x;
	int right2 = rect2.x + rect2.w;
	int top2 = rect2.y;
	int bottom2 = rect2.y + rect2.h;

	if (bottom1 <= top2)
		return false;

	if (top1 >= bottom2)
		return false;

	if (right1 <= left2)
		return false;

	if (left1 >= right2)
		return false;

	//If none of the sides from A are outside B
	return true;
}

GameObject::GameObject(std::string &name)
{
	this->Init(name);
}

GameObject::GameObject(const GameObject & obj)
{
	this->name = obj.name;
	this->rectangle = obj.rectangle;
	this->spriteData = obj.spriteData;
	this->collisionMat = obj.collisionMat;
}

GameObject::GameObject()
{
	this->name = "NULL_NAME";
	this->rectangle = SDL_Rect{0, 0, 0, 0};
	this->spriteData = nullptr;
	this->collisionMat = 0;
}

GameObject::~GameObject()
{
	delete spriteData;
}

std::string GameObject::GetObjectType() const
{
	return ObjectType;
}
