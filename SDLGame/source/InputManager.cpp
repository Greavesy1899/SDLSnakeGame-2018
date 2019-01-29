#include "headers/InputManager.h"

InputManager::~InputManager()
{
	this->ClearKeyVector();

	if (SDL_JoystickGetAttached(this->joystick))
		SDL_JoystickClose(joystick);
}

InputManager::InputManager()
{
	this->pressedKeys = std::vector<int>();
	this->hasLeftClicked = false;
	this->joystick = nullptr;

	if (!this->joystick)
		checkForJoySticks();
}

void InputManager::ClearKeyVector()
{
	this->pressedKeys.clear();
	this->pressedKeys.shrink_to_fit();
}

int InputManager::CheckForKey(int ik) const
{
	for (auto key : this->pressedKeys)
	{
		if (key == ik)
			return 1;
	}

	return 0;
}

void InputManager::AddKeyToVector(const int code)
{
	this->pressedKeys.push_back(code);
}

void InputManager::SetMousePos(Vector& pos)
{
	this->mousePos = pos;
}

Vector InputManager::GetMousePos() const
{
	return this->mousePos;
}

bool InputManager::GetHasLeftClicked() const
{
	return this->hasLeftClicked;
}

void InputManager::SetHasLeftClicked(bool val)
{
	this->hasLeftClicked = val;
}

SDL_Joystick* InputManager::GetJoystick()
{
	//this will try and retrieve a recently connected joystick.
	//or if the joystick has been detached, a new one will be applied.
	//Possible bug is if the joystick is leaking memory because its not being deleted..
	if (!this->joystick || !SDL_JoystickGetAttached(this->joystick))
		checkForJoySticks(); 

	return this->joystick;
}

void InputManager::checkForJoySticks()
{
	this->pressedKeys = std::vector<int>();
	this->joystick = nullptr;
	this->hasLeftClicked = false;

	if (SDL_NumJoysticks() > 0)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_INPUT, "Found %i joystick(s).\n", SDL_NumJoysticks());
		this->joystick = SDL_JoystickOpen(0);

		if (this->joystick)
		{
			SDL_LogCritical(SDL_LOG_CATEGORY_INPUT, "Opened Joystick 0\n");
			SDL_LogCritical(SDL_LOG_CATEGORY_INPUT, "Name: %s\n", SDL_JoystickNameForIndex(0));
		}
		else
		{
			SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Failed to load joystick!\n");
		}
	}
}
