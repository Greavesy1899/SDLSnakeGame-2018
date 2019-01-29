#include "headers/SceneManager.h"
#include "headers/Menu.h"

void SceneManager::SetCurrentScene(int index)
{
	currentScene = scenes.at(index);
}

void SceneManager::SetCurrentScene(std::string name)
{
	if (strcmp(name.c_str(), this->currentScene->GetName().c_str()) == 0)
		return;

	bool swapped = false;

	for (auto *scene : scenes)
	{
		if (scene->GetName() == name) {
			currentScene = scene;
			return;
		}		
	}
}

Scene * SceneManager::GetCurrentScene() const
{
	return currentScene;
}

SDL_Renderer * SceneManager::GetRenderer() const
{
	return this->renderer;
}

void SceneManager::AddScene(Scene* scene)
{
	scenes.push_back(scene);
}

void SceneManager::Input() const
{
	if (strcmp(currentScene->GetSceneType().c_str(), "MenuScene") == 0)
		static_cast<Menu*>(currentScene)->Input();
	else
		static_cast<Scene*>(currentScene)->Input();
}

void SceneManager::Update()
{
	if (strcmp(currentScene->GetSceneType().c_str(), "MenuScene") == 0)
		static_cast<Menu*>(currentScene)->Update();
	else
		static_cast<Scene*>(currentScene)->Update();
}

void SceneManager::Render() const
{
	Singleton::getInstance()->GetSpriteManager()->CreateTextures(renderer);
	SDL_RenderClear(renderer);
	currentScene->Render(renderer);
	SDL_RenderPresent(renderer);
}

SceneManager::SceneManager(SDL_Window* window)
{
	const Uint32 flags = SDL_RENDERER_PRESENTVSYNC;
	renderer = SDL_CreateRenderer(window, -1, flags);
	SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, "SDL Renderer has been defined with flag: %i", flags);
}

SceneManager::~SceneManager()
{
	delete currentScene;
}
