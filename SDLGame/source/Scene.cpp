#include "headers/Scene.h"
#include "include/tinyxml2.h"
#include "headers/SingletonManager.h"
#include "headers/SnakeObject.h"
#include "headers/FoodController.h"
#include "headers/ProgressBarObject.h"
#include "headers/DiscordManager.h"
#include <ctime>

using namespace tinyxml2;

void Scene::SetName(std::string name)
{
	this->name = name;
}

std::string Scene::GetName() const
{
	return name;
}

void Scene::AddObject(GameObject *object)
{
	objects.push_back(object);
}

void Scene::AddUIElement(TextObject* element)
{
	ui.push_back(element);
}

void Scene::RemoveObject(GameObject object)
{
	SDL_Log("Scene::RemoveObject() Not implemented");
}

void Scene::RemoveUIElement(TextObject element)
{
	SDL_Log("Scene::RemoveObject() Not implemented");
}

int Scene::ReadSceneXML(const std::string& path)
{
	SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Reading Scene XML: %s", path.c_str());

	XMLDocument doc;
	doc.LoadFile(path.c_str());

	if (doc.Error())
		return 1;

	//select root, check attributes. 
	//version needs to be 1. 
	//name is stored.
	XMLElement* node = doc.RootElement();
	
	if (strcmp(node->Attribute("version"), "1") != 0)
		return 1;
	this->name = node->Attribute("name");
	this->type = node->Attribute("type");
	
	//get object data.
	XMLElement* objectsNode = node->FirstChildElement("Objects");
	for (const XMLElement* child = objectsNode->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
	{
		std::string name = child->FirstChildElement("Name")->GetText();
		std::string text;
		std::string spritePath;
		int colType, x, y, h, w = 0;
		SpriteData* data = nullptr;

		if(strcmp(child->Attribute("type"), "GameObject") == 0)
		{
			auto* obj = new GameObject();
			//do variables for GameObject
			spritePath = child->FirstChildElement("Sprite")->GetText();

			data = Singleton::getInstance()->GetSpriteManager()->GetSpriteByName(spritePath);

			if (data == nullptr)
			{
				data = new SpriteData(spritePath);
				Singleton::getInstance()->GetSpriteManager()->PushBack(data);
			}

			colType = atoi(child->FirstChildElement("ColType")->GetText());
			x = atoi(child->FirstChildElement("X")->GetText());
			y = atoi(child->FirstChildElement("Y")->GetText());

			obj->Init(name, data, colType, x, y);
			AddObject(obj);
		}
		else if (strcmp(child->Attribute("type"), "CollisionObject") == 0)
		{
			auto* obj = new GameObject();

			colType = atoi(child->FirstChildElement("ColType")->GetText());
			x = atoi(child->FirstChildElement("X")->GetText());
			y = atoi(child->FirstChildElement("Y")->GetText());
			h = atoi(child->FirstChildElement("H")->GetText());
			w = atoi(child->FirstChildElement("W")->GetText());
			obj->Init(name, colType, x, h, y, w);
			AddObject(obj);
		}
		else if(strcmp(child->Attribute("type"), "SnakeObject") == 0)
		{
			auto* obj = new SnakeObject();
			//do variables for SnakeObject
			spritePath = child->FirstChildElement("Sprite")->GetText();

			data = Singleton::getInstance()->GetSpriteManager()->GetSpriteByName(spritePath);

			if(data == nullptr)
			{
				data = new SpriteData(spritePath);
				Singleton::getInstance()->GetSpriteManager()->PushBack(data);
			}
			
			colType = atoi(child->FirstChildElement("ColType")->GetText());
			x = atoi(child->FirstChildElement("X")->GetText());
			y = atoi(child->FirstChildElement("Y")->GetText());

			obj->Init(name, data, colType, x, y);
			AddObject(obj);
		}
		else if (strcmp(child->Attribute("type"), "FoodControllerObject") == 0)
		{
			auto* obj = new FoodControllerObject();
			//do variables for FoodControllerObject
			obj->Init(name);
			AddObject(obj);
		}
		else if(strcmp(child->Attribute("type"), "TextObject") == 0)
		{
			auto* obj = new TextObject();
			//do variables for TextObject;
			text = child->FirstChildElement("Text")->GetText();
			x = atoi(child->FirstChildElement("X")->GetText());
			y = atoi(child->FirstChildElement("Y")->GetText());

			obj->Init(name, text, x, y);
			AddUIElement(obj);
		}
		else if (strcmp(child->Attribute("type"), "ProgressBarObject") == 0)
		{
			auto* obj = new ProgressBarObject();
			x = atoi(child->FirstChildElement("X")->GetText());
			y = atoi(child->FirstChildElement("Y")->GetText());
			auto time = atoi(child->FirstChildElement("Time")->GetText());
			auto width = atoi(child->FirstChildElement("Width")->GetText());
			obj->Init(name, x, y, time, width);
			AddObject(obj);
		}
		else if(strcmp(child->Attribute("type"), "ScenePopulater") == 0)
		{
			int minX = atoi(child->FirstChildElement("MinX")->GetText());
			int maxX = atoi(child->FirstChildElement("MaxX")->GetText());
			int minY = atoi(child->FirstChildElement("MinY")->GetText());
			int maxY = atoi(child->FirstChildElement("MaxY")->GetText());
			this->generateBackground(minX, maxY, minY, maxY);
		}

	}

	this->gameOverSound = Singleton::getInstance()->GetAM()->LookupAudioClip("AUD_GAME_OVER");
	font = TTF_OpenFont("content/VCR.ttf", 21);
	smallFont = TTF_OpenFont("content/VCR.ttf", 17);

	if (font && smallFont)
		SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Loaded font 'VCR.ttf'!");

	SDL_Log("Finished reading XML.");
	
	return 0;
}

void Scene::Clean()
{
	TTF_CloseFont(font);
	TTF_CloseFont(smallFont);
	objects.clear();
	objects.shrink_to_fit();
	ui.clear();
	ui.shrink_to_fit();
}

void Scene::Input()
{
	for (auto object : objects)
		object->Input();
}

//specific updates for playing game state.
void Scene::playingUpdate()
{
	for (size_t i = 0; i != objects.size(); i++)
	{
		objects[i]->Update();
		
		if (strcmp(objects[i]->GetObjectType().c_str(), "SnakeObject") == 0)
		{
			auto* snake = dynamic_cast<SnakeObject*>(objects[i]);

			for (size_t z = 0; z != objects.size(); z++)
			{
				if (z == i)
					continue;

				if (GameObject::CheckCollision(snake->rectangle, objects[z]->rectangle))
				{
					if (objects[z]->GetCollisionType() == 2)
						Singleton::getInstance()->SetGameState(2);
				}
				else if (strcmp(objects[z]->GetObjectType().c_str(), "FoodController") == 0)
				{
					auto* controller = dynamic_cast<FoodControllerObject*>(objects[z]);

					if (GameObject::CheckCollision(snake->rectangle, controller->food->rectangle))
					{
						controller->EatenFood();
						snake->Grow();
					}
				}
			}
		}
		else if(strcmp(objects[i]->GetObjectType().c_str(), "ProgressBarObject") == 0)
		{
			auto* bar = dynamic_cast<ProgressBarObject*>(objects[i]);

			if (bar->GetTicks() >= 20000 && bar->GetTicks() < 40000)
				Singleton::getInstance()->SetFPS(25);

			if (bar->GetTicks() >= 40000 && bar->GetTicks() < 60000)
				Singleton::getInstance()->SetFPS(30);

			if (bar->GetTicks() >= 60000)
				Singleton::getInstance()->SetGameState(2);
		}
	}
	for (size_t i = 0; i != ui.size(); i++)
	{
		if (ui[i]->GetName() == "GameScore")
		{
			std::string score = std::to_string(Singleton::getInstance()->GetScore());
			ui[i]->SetText("Score: " + score);
			DiscordManager::UpdatePresence("Collected " + score + " points.");
			ui[i]->Update(font);
		}
		else if (ui[i]->GetName() == "GameStateText")
		{
			ui[i]->SetText("");
			ui[i]->Update(font);
		}
	}
}
void Scene::pausedUpdate()
{
	for (size_t i = 0; i != ui.size(); i++)
	{
		if (ui[i]->GetName() == "GameStateText")
		{
			ui[i]->SetText(" Paused  ");
			ui[i]->Update(font);
		}
	}
}
void Scene::gameOverUpdate()
{
	for (size_t i = 0; i != ui.size(); i++)
	{
		if (ui[i]->GetName() == "GameStateText")
		{
			ui[i]->SetText("Game Over");
			ui[i]->Update(font);
		}
	}
	if (!this->playedGameOver)
	{
		this->gameOverSound->Play();
		this->playedGameOver = true;
	}
}

void Scene::generateBackground(int minX, int maxX, int minY, int maxY)
{
	srand(time(NULL));

	//load in all grass data.
	for(int i = 0; i <= 7; i++)
	{
		std::string path = "content/grass_";
		path += std::to_string(i);
		path += ".png";
		auto* data = new SpriteData(path);
		Singleton::getInstance()->GetSpriteManager()->PushBack(data);
	}

	const int cellSizeX = (maxX - minX) / 32;
	const int cellSizeY = (maxY - minY) / 32;

	for (int x = 0; x <= cellSizeX+6; x++)
	{
		for (int y = 0; y <= cellSizeY; y++)
		{
			const bool doSpawn = rand() % 2;

			if (doSpawn)
			{
				int randGrass = rand() % 7;
				std::string path = "content/grass_" + std::to_string(randGrass) + ".png";
				auto* grass = new GameObject();
				grass->Init("Grass" + std::to_string(cellSizeX) + std::to_string(cellSizeY), Singleton::getInstance()->GetSpriteManager()->GetSpriteByName(path), 0, (x*32)+32, (y * 32) + 64);
				this->objects.push_back(grass);
			}
		}
	}
}

void Scene::Update()
{
	switch (Singleton::getInstance()->GetGameState())
	{
	case 0:
		playingUpdate();
		break;
	case 1:
		pausedUpdate();
		break;
	case 2:
		gameOverUpdate();
		break;
	case 3:
		break;
	default:
		SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "GameState is unknown, setting to 0");
		Singleton::getInstance()->SetGameState(0);
		break;
	}
}

void Scene::Render(SDL_Renderer* renderer)
{
	for (auto object : objects)
		object->Render(renderer);

	for (auto element : ui)
		element->Render(renderer);
}

std::string Scene::GetSceneType() const
{
	return Scene::SceneType;
}

Vector Scene::GetSceneSize() const
{
	return this->sceneSize;
}

Scene::Scene()
{
	this->font = nullptr;
}

Scene::~Scene()
{
	Clean();
}
