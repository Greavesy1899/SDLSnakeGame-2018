#pragma once
#ifndef SceneFile
#define SceneFile

#include "include/SDL.h"
#include "NewGameObject.h"
#include "TextObject.h"
#include <string>
#include <vector>
#include "Vector.h"
#include <include/SDL_ttf.h>
#include <include/SDL_mixer.h>

class Scene {
private:
	std::string SceneType = "GameScene";
	std::string name;
	std::string type;
	Vector sceneSize;
	Mix_Chunk* gameOverSound;
	bool playedGameOver;
	void playingUpdate();
	void pausedUpdate();
	void gameOverUpdate();
	void generateBackground(int minX, int maxX, int minY, int maxY);
protected:
	TTF_Font* font;
	TTF_Font* smallFont;
	std::vector<GameObject*> objects;
	std::vector<TextObject*> ui;
public:
	void SetName(std::string name);
	std::string GetName() const;
	void AddObject(GameObject *object);
	void AddUIElement(TextObject *element);
	void RemoveObject(GameObject object);
	void RemoveUIElement(TextObject element);
	int ReadSceneXML(const std::string& path);
	virtual void Clean();
	virtual void Input();
	virtual void Update();
	virtual void Render(SDL_Renderer* renderer);
	virtual std::string GetSceneType() const;
	Vector GetSceneSize() const;
	Scene();
	~Scene();
};
#endif