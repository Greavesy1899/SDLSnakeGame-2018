#pragma once
#ifndef MenuFile
#define MenuFile


#include <string>
#include <vector>
#include "Vector.h"
#include "Scene.h"

#include "SZ_Timer.h"
#include <include/SDL_mixer.h>

class Menu : public Scene {
private:
	int menuCurIdx = 0;
	int menuPressedIdx = -1;
	std::string SceneType = "MenuScene";
	SZ_Timer toggleInputDelay;
	bool IsButton(std::string name1, std::string name2);
	void moveUp();
	void moveDown();
	void select();
	Mix_Chunk* menuUpSound;
	Mix_Chunk* menuDownSound;
	Mix_Chunk* menuSelectSound;
public:
	std::string GetSceneType() const override;
	void Input();
	void Update();
	Menu();
	~Menu();
};
#endif