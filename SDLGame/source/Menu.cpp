#include "headers/Menu.h"
#include "headers/SingletonManager.h"
#include "include/SDL.h"
#include "headers/NewGameObject.h"
#include "headers/TextObject.h"
#include "headers/Vector.h"
#include <include/SDL_mixer.h>


bool Menu::IsButton(std::string name1, std::string name2)
{
	return strcmp(name1.c_str(), name2.c_str()) == 0;
}

void Menu::moveUp()
{
	if (menuCurIdx > 0)
	{
		menuCurIdx--;

		if (!Singleton::getInstance()->GetAM()->GetSoundMuted())
			Mix_PlayChannel(1, this->menuUpSound, 0);
	}
}

void Menu::moveDown()
{
	if (menuCurIdx < 3)
	{
		menuCurIdx++;

		if (!Singleton::getInstance()->GetAM()->GetSoundMuted())
			Mix_PlayChannel(1, this->menuDownSound, 0);
	}
}

void Menu::select()
{
	this->menuPressedIdx = menuCurIdx;

	if (!Singleton::getInstance()->GetAM()->GetSoundMuted())
		Mix_PlayChannel(1, this->menuSelectSound, 0);
}


std::string Menu::GetSceneType() const
{
	return Menu::SceneType;
}

void Menu::Input()
{
	if (!toggleInputDelay.IsRunning())
	{
		if (SDL_JoystickGetAxis(Singleton::getInstance()->GetIM()->GetJoystick(), XBOX_TOGGLE_X) <= MIN + 20000)
		{
			this->moveUp();
			SDL_LogCritical(SDL_LOG_CATEGORY_INPUT, "Gamepad pressed [Left Stick Up]");
		}
		else if (SDL_JoystickGetAxis(Singleton::getInstance()->GetIM()->GetJoystick(), XBOX_TOGGLE_X) >= MAX - 20000)
		{
			this->moveDown();
			SDL_LogCritical(SDL_LOG_CATEGORY_INPUT, "Gamepad pressed [Left Stick Down]");
		}
		else if (SDL_JoystickGetButton(Singleton::getInstance()->GetIM()->GetJoystick(), XBOX_BUTTON_A))
		{
			this->select();
			SDL_LogCritical(SDL_LOG_CATEGORY_INPUT, "Gamepad pressed [Button A]");
		}
		toggleInputDelay.resetTicksTimer();
	}

	if (Singleton::getInstance()->GetIM()->CheckForKey(22))
	{
		this->moveDown();
		SDL_LogCritical(SDL_LOG_CATEGORY_INPUT, "Keyboard pressed [W]");
	}
	else if (Singleton::getInstance()->GetIM()->CheckForKey(26))
	{
		this->moveUp();
		SDL_LogCritical(SDL_LOG_CATEGORY_INPUT, "Keyboard pressed [S]");
	}
	else if (Singleton::getInstance()->GetIM()->CheckForKey(40))
	{
		this->select();
		SDL_LogCritical(SDL_LOG_CATEGORY_INPUT, "Keyboard pressed [Enter]");
	}

	Scene::Input();
}

void Menu::Update()
{
	int gs = Singleton::getInstance()->GetGameState();
	
	//do the interface stuff first; most important.
	if (menuCurIdx > 3)
		menuCurIdx = 3;
	if (menuCurIdx < 0)
		menuCurIdx = 0;

	if (toggleInputDelay.getTicks() >= 100)
		toggleInputDelay.StopTimer();

	//now we can configure the latest updates.

	if (gs == 3)
	{
		switch (menuPressedIdx)
		{
		case 0:
			Singleton::getInstance()->SetGameState(0);
			break;
		case 1:
			Singleton::getInstance()->GetAM()->SetSoundMuted(!Singleton::getInstance()->GetAM()->GetSoundMuted());
			break;
		case 2:
			Singleton::getInstance()->GetAM()->SetMusicMuted(!Singleton::getInstance()->GetAM()->GetMusicMuted());
			break;
		case 3:
			Singleton::getInstance()->SetGameState(5);
			break;
		default:
			break;
		}
		menuPressedIdx = -1;
	}

	for (size_t i = 0; i != ui.size(); i++)
	{
		Vector pos = Singleton::getInstance()->GetIM()->GetMousePos();
		SDL_Rect temp = SDL_Rect{ pos.GetX(), pos.GetY(), 2, 2 };

		ui[i]->Update(smallFont, true);
		if (IsButton(ui[i]->GetName(), "SnakeGameTitle"))
		{
			ui[i]->SetText("SDL Snake Game");
			ui[i]->Update(font, false);
		}
		else if (IsButton(ui[i]->GetName(), "JoystickDetected"))
		{
			if (Singleton::getInstance()->GetIM()->GetJoystick())
				ui[i]->SetText("Joystick has been detected!");
			else
				ui[i]->SetText("No joysticks have been detected!");

			ui[i]->Update(smallFont, false);
		}
		else if(IsButton(ui[i]->GetName(), "ControlSnakeUp"))
		{
			std::string keyConvert = "Snake Up: Left Toggle Up, '";
			SDL_Keycode key = SDL_GetKeyFromScancode((SDL_Scancode)Singleton::getInstance()->GetKeyMaps()[1]);
			keyConvert += SDL_GetKeyName(key);
			keyConvert += "' key";
			ui[i]->SetText(keyConvert);
			ui[i]->Update(smallFont, false);
		}
		else if (IsButton(ui[i]->GetName(), "ControlSnakeDown"))
		{
			std::string keyConvert = "Snake Up: Left Toggle Down, '";
			SDL_Keycode key = SDL_GetKeyFromScancode((SDL_Scancode)Singleton::getInstance()->GetKeyMaps()[3]);
			keyConvert += SDL_GetKeyName(key);
			keyConvert += "' key";
			ui[i]->SetText(keyConvert);
			ui[i]->Update(smallFont, false);
		}
		else if (IsButton(ui[i]->GetName(), "ControlSnakeLeft"))
		{
			std::string keyConvert = "Snake Up: Left Toggle Left, '";
			SDL_Keycode key = SDL_GetKeyFromScancode((SDL_Scancode)Singleton::getInstance()->GetKeyMaps()[0]);
			keyConvert += SDL_GetKeyName(key);
			keyConvert += "' key";
			ui[i]->SetText(keyConvert);
			ui[i]->Update(smallFont, false);
		}
		else if (IsButton(ui[i]->GetName(), "ControlSnakeRight"))
		{
			std::string keyConvert = "Snake Up: Left Toggle Right, '";
			SDL_Keycode key = SDL_GetKeyFromScancode((SDL_Scancode)Singleton::getInstance()->GetKeyMaps()[2]);
			keyConvert += SDL_GetKeyName(key);
			keyConvert += "' key";
			ui[i]->SetText(keyConvert);
			ui[i]->Update(smallFont, false);
		}
		else if (IsButton(ui[i]->GetName(), "MenuUp"))
		{
			ui[i]->SetText("Menu Up: Left Toggle Up, 'W' Key");
			ui[i]->Update(smallFont, false);
		}
		else if (IsButton(ui[i]->GetName(), "MenuDown"))
		{
			ui[i]->SetText("Menu Down: Left Toggle Down, 'S' Key");
			ui[i]->Update(smallFont, false);
		}
		else if (IsButton(ui[i]->GetName(), "MenuAccept"))
		{
			ui[i]->SetText("Menu Accept: 'A' Button, 'Enter' Key");
			ui[i]->Update(smallFont, false);
		}

		if (GameObject::CheckCollision(ui[i]->rectangle, temp))
		{
			menuCurIdx = i;

			if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_LEFT)
			{
				this->select();
				if (IsButton(ui[i]->GetName(), "PlayButton"))
					Singleton::getInstance()->SetGameState(0);
				else if (IsButton(ui[i]->GetName(), "OptionButton"))
					Singleton::getInstance()->SetGameState(4);
				else if (IsButton(ui[i]->GetName(), "ExitButton"))
					Singleton::getInstance()->SetGameState(5);
				else if (IsButton(ui[i]->GetName(), "SoundToggle"))
					Singleton::getInstance()->GetAM()->SetSoundMuted(!Singleton::getInstance()->GetAM()->GetSoundMuted());
				else if(IsButton(ui[i]->GetName(), "MusicToggle"))
					Singleton::getInstance()->GetAM()->SetMusicMuted(!Singleton::getInstance()->GetAM()->GetMusicMuted());
			}
		}
		else
		{
			ui[i]->SetColor(255, 255, 255, SDL_ALPHA_OPAQUE);
		}

	}

	if (menuCurIdx > -1 && menuCurIdx < 4)
		ui[menuCurIdx]->SetColor(255, 0, 0, SDL_ALPHA_OPAQUE);
}

Menu::Menu()
{
	this->menuDownSound = Mix_LoadWAV("Content/MenuMoveDown.wav");
	this->menuUpSound = Mix_LoadWAV("Content/MenuMoveUp.wav");
	this->menuSelectSound = Mix_LoadWAV("content/MenuSelect.wav");
	Mix_VolumeChunk(menuDownSound, 20);
	Mix_VolumeChunk(menuUpSound, 20);
	Mix_VolumeChunk(menuSelectSound, 20);
}

Menu::~Menu()
{
	Mix_FreeChunk(this->menuDownSound);
	Mix_FreeChunk(this->menuUpSound);
}
