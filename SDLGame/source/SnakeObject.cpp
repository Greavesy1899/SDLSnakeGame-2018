#include "headers/SnakeObject.h"
#include "headers/SingletonManager.h"

SnakeObject::SnakeObject(const std::string& name)
{
	this->name = name;
	this->rotation = 0;
	this->direction = Vector::Up();
	this->body = std::vector<GameObject*>();
}

SnakeObject::SnakeObject()
{
	this->name = "NULL";
	this->rotation = 0;
	this->direction = Vector::Up();
	this->body = std::vector<GameObject*>();
}

SnakeObject::~SnakeObject() = default;

void SnakeObject::Init(const std::string& name, SpriteData* spriteData, int colType, int x, int y)
{
	GameObject::Init(name, spriteData, colType, x, y);
	this->headSprite = Singleton::getInstance()->GetSM()->GetSpriteByName("SNAKE_HEAD");
	this->bodySprite = Singleton::getInstance()->GetSM()->GetSpriteByName("SNAKE_BODY");
	this->tailSprite = Singleton::getInstance()->GetSM()->GetSpriteByName("SNAKE_TAIL");
	this->ghostHeadSprite = Singleton::getInstance()->GetSM()->GetSpriteByName("POWER_HEAD");
	this->ghostBodySprite = Singleton::getInstance()->GetSM()->GetSpriteByName("POWER_BODY");
	this->ghostTailSprite = Singleton::getInstance()->GetSM()->GetSpriteByName("POWER_TAIL");

	auto* headPart = new GameObject();
	headPart->Init("SnakeHead", headSprite, colType, x, y);
	body.push_back(headPart);

	int offset = 16;
	for(int i = 0; i != 3; i++)
	{
		auto* bodyPart = new GameObject();
		bodyPart->Init("SnakeBody" + i, bodySprite, colType, x, y+offset);
		body.push_back(bodyPart);
		offset += 16;
	}
	this->length = body.size() - 1;

	auto* tailPart = new GameObject();
	tailPart->Init("SnakeTail", tailSprite, colType, x, y+offset);
	body.push_back(tailPart);

	direction = Vector::Up();
	moveLeftKey = Singleton::getInstance()->GetKeyMaps()[0];
	moveUpKey = Singleton::getInstance()->GetKeyMaps()[1];
	moveRightKey = Singleton::getInstance()->GetKeyMaps()[2];
	moveDownKey = Singleton::getInstance()->GetKeyMaps()[3];
	this->snakeMode = 0;
}

void SnakeObject::Input()
{	 
	//using elseif breaks keyboard input..
	const Vector previous = this->direction;

	if (Singleton::getInstance()->GetIM()->CheckForKey(moveUpKey) && (this->rotation != 180)) {
		this->direction = Vector::Up();
		this->rotation = 0;
	}
	else if (Singleton::getInstance()->GetIM()->CheckForKey(moveLeftKey) && (this->rotation != 90)) {
		this->direction = Vector::Left();
		this->rotation = -90;
	}
	else if (Singleton::getInstance()->GetIM()->CheckForKey(moveRightKey) && (this->rotation != -90)) {
		this->direction = Vector::Right();
		this->rotation = 90;
	}
	else if (Singleton::getInstance()->GetIM()->CheckForKey(moveDownKey) && (this->rotation != 0)) {
		this->direction = Vector::Down();
		this->rotation = 180;
	}

	if(Singleton::getInstance()->GetIM()->GetJoystick())
	{
		if ((SDL_JoystickGetAxis(Singleton::getInstance()->GetIM()->GetJoystick(), XBOX_TOGGLE_X) <= -DEADZONE) && (this->rotation != 180)) {
			this->direction = Vector::Up();
			this->rotation = 0;
		}
		if ((SDL_JoystickGetAxis(Singleton::getInstance()->GetIM()->GetJoystick(), XBOX_TOGGLE_Y) <= -DEADZONE) && (this->rotation != 90)) {
			this->direction = Vector::Left();
			this->rotation = -90;
		}
		if ((SDL_JoystickGetAxis(Singleton::getInstance()->GetIM()->GetJoystick(), XBOX_TOGGLE_Y) >= DEADZONE) && (this->rotation != -90)) {
			this->direction = Vector::Right();
			this->rotation = 90;
		}
		if ((SDL_JoystickGetAxis(Singleton::getInstance()->GetIM()->GetJoystick(), XBOX_TOGGLE_X) >= DEADZONE) && (this->rotation != 0)) {
			this->direction = Vector::Down();
			this->rotation = 180;
		}
	}

	if(previous != this->direction)
		SDL_Log("Snake Direction is: %i %i", this->direction.GetX(), this->direction.GetY());
}

void SnakeObject::Update()
{
	for (size_t z = body.size() - 1; z > 0; z--)
	{
		body[z]->rectangle = body[z - 1]->rectangle;
		body[z]->SetRotation(body[z - 1]->GetRotation());
	}

	if (direction == Vector::Up())
	{
		body[0]->rectangle.y -= 16;
		body[0]->SetRotation(0);
	}
	else if (direction == Vector::Down())
	{
		body[0]->rectangle.y += 16;
		body[0]->SetRotation(180);
	}
	else if (direction == Vector::Right())
	{
		body[0]->rectangle.x += 16;
		body[0]->SetRotation(90);
	}
	else if (direction == Vector::Left())
	{
		body[0]->rectangle.x -= 16;
		body[0]->SetRotation(-90);
	}

	this->rectangle = body[0]->rectangle;
	this->snakeMode = Singleton::getInstance()->GetHasEatenGhostFood() ? 1 : 0;

	if((snakeMode == 1) && (!ghostTimer.IsRunning()))
		ghostTimer.resetTicksTimer();

	if (ghostTimer.IsRunning() && ghostTimer.getTicks() > 5000)
	{
		snakeMode = 0;
		Singleton::getInstance()->SetHasEatenGhostFood(false);
		ghostTimer.StopTimer();
	}

	for (size_t z = 0; z != body.size(); z++)
	{
		if (snakeMode == 1)
		{
			if (strcmp(body[z]->GetSpriteData()->GetName().c_str(), "SNAKE_HEAD") == 0)
				body[z]->SetSpriteData(ghostHeadSprite);
			else if (strcmp(body[z]->GetSpriteData()->GetName().c_str(), "SNAKE_TAIL") == 0)
				body[z]->SetSpriteData(ghostTailSprite);
			else if (strcmp(body[z]->GetSpriteData()->GetName().c_str(), "SNAKE_BODY") == 0)
				body[z]->SetSpriteData(ghostBodySprite);
		}
		else if(snakeMode == 0)
		{
			if (strcmp(body[z]->GetSpriteData()->GetName().c_str(), "POWER_HEAD") == 0)
				body[z]->SetSpriteData(headSprite);
			else if (strcmp(body[z]->GetSpriteData()->GetName().c_str(), "POWER_TAIL") == 0)
				body[z]->SetSpriteData(tailSprite);
			else if (strcmp(body[z]->GetSpriteData()->GetName().c_str(), "POWER_BODY") == 0)
				body[z]->SetSpriteData(bodySprite);
		}

		if (z != 0)
		{
			if ((CheckCollision(body[0]->rectangle, body[z]->rectangle)) && (snakeMode != 1))
				Singleton::getInstance()->SetGameState(2);
		}
	}
}

void SnakeObject::Render(SDL_Renderer * renderer)
{
	//fix
	if(!this->body[0]->GetSpriteData()->GetTexture())
		this->body[0]->GetSpriteData()->CreateTextureSprite(renderer);

	for(auto* bodyPiece : body)
		bodyPiece->Render(renderer);
}

void SnakeObject::Grow()
{
	this->length++;
	auto* bodyPart = new GameObject();
	auto* sprite = snakeMode == 1 ? ghostBodySprite : bodySprite;
	bodyPart->Init("SnakeBody" + length, sprite, 1, body[length]->rectangle.x, body[length]->rectangle.y);
	bodyPart->SetRotation(body[length]->GetRotation());
	body.insert(body.begin()+length, bodyPart);
}

std::string SnakeObject::GetObjectType() const
{
	return this->ObjectType;
}
