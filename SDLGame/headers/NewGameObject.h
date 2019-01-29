#pragma once
#ifndef NewGameObjectFile
#define NewGameObjectFile
#include "include/SDL.h"
#include <string>
#include "SpriteData.h"

class GameObject {
public:

	//functions
	void Init(std::string&);
	void Init(const std::string& name, SpriteData* data, int colType, int x, int y);
	void Init(const std::string& name, int colType, int x, int h, int y, int w);
	virtual void Input();
	virtual void Update();
	virtual void Render(SDL_Renderer*);

	//accessors
	int GetCollisionType() const;
	virtual std::string GetName() const;
	SpriteData* GetSpriteData() const;
	void SetSpriteData(SpriteData* sprite);
	int GetRotation() const;
	void SetRotation(int);
	static bool CheckCollision(SDL_Rect rect1, SDL_Rect rect2);

	//constructors/destructors.
	GameObject(std::string&);
	GameObject(const GameObject& obj);
	GameObject();
	virtual ~GameObject();

	SDL_Rect rectangle;

	virtual std::string GetObjectType() const;
private:
	SpriteData* spriteData;
	int collisionMat;	//0 null, 1 snake, 2 wall, 3 food, 4 power-up
	std::string ObjectType = "GameObject";
protected:
	std::string name;
	int rotation;
	bool debug = false;
};
#endif