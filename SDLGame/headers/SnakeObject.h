#pragma once
#ifndef SnakeObjectFile
#define SnakeObjectFile
#include "headers/NewGameObject.h"
#include "headers/Vector.h"
#include <vector>
#include "SZ_Timer.h"

class SnakeObject : public GameObject
{
public:
	SnakeObject(const std::string& name);
	SnakeObject();
	~SnakeObject();

	void Init(const std::string & name, SpriteData * spriteData, int colType, int x, int y);
	void Input();
	void Update();
	void Render(SDL_Renderer*);
	void Grow();

	std::string GetObjectType() const;
private:
	Vector direction;
	std::vector<GameObject*> body;
	SpriteData* bodySprite;
	SpriteData* tailSprite;
	SpriteData* headSprite;
	SpriteData* ghostBodySprite;
	SpriteData* ghostTailSprite;
	SpriteData* ghostHeadSprite;

	int length;

	int moveLeftKey;
	int moveUpKey;
	int moveRightKey;

	int moveDownKey;
	int snakeMode;
	SZ_Timer ghostTimer;


	std::string ObjectType = "SnakeObject";
};
#endif
