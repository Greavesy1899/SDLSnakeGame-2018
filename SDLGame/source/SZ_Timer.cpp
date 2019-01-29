#include "headers/SZ_Timer.h"
#include <include/SDL.h>

SZ_Timer::SZ_Timer()
{
	startTicks = 0;
	isRunning = false;
};
void SZ_Timer::resetTicksTimer()
{
	startTicks = SDL_GetTicks(); // numbers of milliseconds since start of SDL program
	isRunning = true;
	//printf("timer started! %i \n", startTicks);
}
int SZ_Timer::getTicks() const
{
	//printf("getTicks! %i \n", SDL_GetTicks() - startTicks);
	return (SDL_GetTicks() - startTicks); //Return the current time minus the start time
}

bool SZ_Timer::IsRunning() const
{
	return this->isRunning;
}

void SZ_Timer::StopTimer()
{
	this->isRunning = false;
}
