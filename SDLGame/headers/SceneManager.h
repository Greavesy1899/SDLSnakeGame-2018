#pragma once
#ifndef SceneManagerFile
#define SceneManagerFile
#include "include/SDL.h"
#include "SingletonManager.h"
#include "Scene.h"
class SceneManager {
private:
	Scene* currentScene;
	std::vector<Scene*>scenes;
	SDL_Renderer* renderer;
public:
	void SetCurrentScene(int index);
	void SetCurrentScene(std::string name);
	Scene* GetCurrentScene() const;
	SDL_Renderer* GetRenderer() const;
	void AddScene(Scene* scene);
	void Input() const;
	void Update();
	void Render() const;
	SceneManager(SDL_Window* window);
	~SceneManager();
};
#endif
