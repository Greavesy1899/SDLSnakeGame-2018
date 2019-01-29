#pragma once
#ifndef InputManagerFile
#define InputManagerFile
#include <vector>
#include "headers/Vector.h"
#include <include/SDL.h>

#define XBOX_BUTTON_A 0
#define XBOX_BUTTON_B 1
#define XBOX_BUTTON_X 2
#define XBOX_BUTTON_Y 3
#define XBOX_BUTTON_START 7
#define XBOX_TOGGLE_Y 0
#define XBOX_TOGGLE_X 1
#define DEADZONE 3000
#define MAX 32767
#define MIN -32768

class InputManager
{
public:
	//constructor/destructor
	~InputManager();
	InputManager();
	InputManager(const InputManager &im) = delete;
	InputManager(InputManager &&im) = delete;

	//operators.
	InputManager operator=(const InputManager &im) = delete;
	InputManager operator=(InputManager &&im) = delete;

	//functions
	void ClearKeyVector();
	int CheckForKey(int ik) const;
	void AddKeyToVector(int code);
	void SetMousePos(Vector& pos);
	Vector GetMousePos() const;
	bool GetHasLeftClicked() const;
	void SetHasLeftClicked(bool val);
	SDL_Joystick* GetJoystick();

private:
	SDL_Joystick* joystick;
	std::vector<int> pressedKeys;
	//std::vector<SDL_Event> events; i might do this.
	Vector mousePos;
	bool hasLeftClicked;

	//private; we don't want this to be called.
	void checkForJoySticks();
};
#endif