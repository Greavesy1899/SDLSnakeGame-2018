#pragma once
#ifndef ProgressBarFile
#define ProgressBarFile
#include "include/SDL.h"
#include "SZ_Timer.h"
#include "NewGameObject.h"

class ProgressBarObject : public GameObject {
private:
	SZ_Timer timer;
	std::string ObjectType = "ProgressBarObject";
	SDL_Color color;
	int iteration;
	int maxTime;
	int maxWidth;
	int totalTicks;
public:
	ProgressBarObject(std::string);
	ProgressBarObject();
	~ProgressBarObject();
	void Init(std::string name, int x, int y, int time, int width);
	void Input() override;
	void Update() override;
	void Render(SDL_Renderer* renderer) override;

	void SetColor(SDL_Color color);
	void SetTime(int maxTime);
	void SetMaxWidth(int maxWidth);
	std::string GetObjectType() const;
	int GetTicks() const;
};
#endif