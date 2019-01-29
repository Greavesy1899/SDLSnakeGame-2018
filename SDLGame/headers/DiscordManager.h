#pragma once
#ifndef  DISCORD_MANAGER
#define DISCORD_MANAGER
#include <string>
#include <include/discord_rpc.h>

class DiscordManager
{
public:
	static void Init();
	static void UpdatePresence(std::string details, bool startTimer = false);
};

inline void DiscordManager::Init()
{
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));

	// Discord_Initialize(const char* applicationId, DiscordEventHandlers* handlers, int autoRegister, const char* optionalSteamId)
	Discord_Initialize("523878781488726027", NULL, 1, NULL);
}

inline void DiscordManager::UpdatePresence(std::string details, bool startTimer)
{
	char buffer[256];
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.state = "Playing snake in SDL";
	discordPresence.details = details.c_str();

	//discordPresence.startTimestamp = SDL_GetTicks();

	discordPresence.largeImageKey = "snake";
	discordPresence.smallImageKey = "snake";
	Discord_UpdatePresence(&discordPresence);
}
#endif
