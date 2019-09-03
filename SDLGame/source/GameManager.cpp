#include "headers/GameManager.h"
#include "include/tinyxml2.h"

void GameManager::HandleMusic()
{
	if (!Singleton::getInstance()->GetAM()->GetMusicMuted())
	{
		if (!this->isMusicOn)
		{
			SDL_LogCritical(SDL_LOG_CATEGORY_AUDIO, "Music should have started playing!");
			this->music->Play();
			this->isMusicOn = true;
		}
		this->music->SetVolume(100);
	}
	else
	{
		this->music->SetVolume(0);
	}
}

void GameManager::HandlePausing()
{
	int state = Singleton::getInstance()->GetGameState();

	if (state == 1 || state == 0)
	{
		if (state == 1)
			Singleton::getInstance()->SetGameState(0);
		else
			Singleton::getInstance()->SetGameState(1);
	}
}

GameManager::GameManager()
{
	this->isRunning = false;
	this->isMusicOn = false;
	this->music = nullptr;
	this->windowID = 0;
	this->window = nullptr;
	this->sceneManager = nullptr;
}

GameManager::~GameManager() {
	SDL_DestroyWindow(window);
	delete sceneManager;
	isRunning = false;
}

int GameManager::LoadConfig() const
{
	std::string config = "content/config.xml";

	SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Reading Scene XML: %s", config.c_str());

	tinyxml2::XMLDocument doc;
	doc.LoadFile(config.c_str());

	if (doc.Error())
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "XML Reading error on [%s]. %s\n", config.c_str(), doc.ErrorStr());
		return 1;
	}

	//select root, check attributes. 
	//version needs to be 1. 
	//name is stored.
	tinyxml2::XMLElement* node = doc.RootElement();
	if (strcmp(node->Attribute("version"), "1") != 0)
		return 1;

	int* key = Singleton::getInstance()->GetKeyMaps();

	//get object data.
	tinyxml2::XMLElement* objectsNode = node->FirstChildElement("Options");
	for (const tinyxml2::XMLElement* child = objectsNode->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
	{
		//get the Left keymap..
		if (strcmp(child->Name(), "SnakeMoveLeftKey") == 0)
			key[0] = atoi(child->GetText());
		//get the up keymap..
		if (strcmp(child->Name(), "SnakeMoveUpKey") == 0)
			key[1] = atoi(child->GetText());
		//get the right keymap..
		if (strcmp(child->Name(), "SnakeMoveRightKey") == 0)
			key[2] = atoi(child->GetText());
		//get the down keymap..
		if (strcmp(child->Name(), "SnakeMoveDownKey") == 0)
			key[3] = atoi(child->GetText());
		//get the pause keymap..
		if (strcmp(child->Name(), "PauseKey") == 0)
			key[4] = atoi(child->GetText());
		//toggle sounds
		if (strcmp(child->Name(), "MuteSounds") == 0)
			Singleton::getInstance()->GetAM()->SetSoundMuted(strcmp(child->GetText(), "1") == 0);
		//toggle music
		if(strcmp(child->Name(), "MuteMusic") == 0)
			Singleton::getInstance()->GetAM()->SetSoundMuted(strcmp(child->GetText(), "1") == 0);
	}
	Singleton::getInstance()->SetKeyMaps(key);
	return 0;
}

bool GameManager::GetRunning() const
{
	return GameManager::isRunning;
}

void GameManager::Init() {
	const Uint32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;

	//define and create window.
	window = SDL_CreateWindow("Connor Greaves, 17640379, CGP2011M, Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, flags);
	windowID = SDL_GetWindowID(window);
	SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, "SDL Window has been defined with flags %i", flags);

	this->LoadConfig();

	//build scene.
	sceneManager = new SceneManager(window);

	Scene* scene = new Scene();
	scene->ReadSceneXML("content/level1.xml");

	Menu* menu = new Menu();
	menu->ReadSceneXML("content/menu.xml");

	sceneManager->AddScene(scene);
	sceneManager->AddScene(menu);
	sceneManager->SetCurrentScene(1);
	Singleton::getInstance()->SetGameState(3);
	Singleton::getInstance()->ResetScore();
	this->music = Singleton::getInstance()->GetAM()->LookupAudioClip("MUS_MAIN01");
	//finish init.
	this->isRunning = true;
	HandleMusic();

	SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Game Manager Initialized.");
}

void GameManager::Input() {
	Singleton::getInstance()->GetIM()->ClearKeyVector();
	SDL_Event event;
	Vector pos;
	while (SDL_PollEvent(&event) == 1)
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			Singleton::getInstance()->GetIM()->AddKeyToVector(event.key.keysym.scancode);
			break;
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_WINDOWEVENT_RESIZED:
			//SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, "Resizing window to %i, %i", event.window.data1, event.window.data2);
			SDL_SetWindowSize(window, event.window.data1, event.window.data2);
			break;
		case SDL_MOUSEMOTION:
			pos = Vector(event.motion.x, event.motion.y);
			Singleton::getInstance()->GetIM()->SetMousePos(pos);
			break;
		default:
			break;
		}
	}

	if (Singleton::getInstance()->GetIM()->CheckForKey(SDL_SCANCODE_ESCAPE))
		isRunning = false;

	if (Singleton::getInstance()->GetIM()->CheckForKey(Singleton::getInstance()->GetKeyMaps()[4]))
		HandlePausing();

	sceneManager->Input();

	if (Singleton::getInstance()->GetIM()->GetJoystick())
	{
		if (SDL_JoystickGetButton(Singleton::getInstance()->GetIM()->GetJoystick(), XBOX_BUTTON_START))
			HandlePausing();
	}


}

void GameManager::Update() {

	this->HandleMusic();

	switch(Singleton::getInstance()->GetGameState())
	{
	case 0:
		Singleton::getInstance()->SetFPS(20);
		sceneManager->SetCurrentScene("Level1Scene");
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		Singleton::getInstance()->SetFPS(60);
		sceneManager->SetCurrentScene("Menu");
		break;
	case 5:
		isRunning = false;
		break;
	default:
		break;
	}

	//no point in running another frame.
	if (!isRunning)
		return;

	sceneManager->Update();
}

void GameManager::Render() const {
	sceneManager->Render();
}