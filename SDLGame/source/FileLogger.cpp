#include "headers/FileLogger.h"
#include <iostream>

void FileLogger::LoggingFunction(void * userdata, int category, SDL_LogPriority priority, const char * message)
{
	std::string prefix;

	switch (category)
	{
	case SDL_LOG_CATEGORY_APPLICATION:
		prefix = "[APP] ";
		break;
	case SDL_LOG_CATEGORY_INPUT:
		prefix = "[INPUT] ";
		break;
	case SDL_LOG_CATEGORY_RENDER:
		prefix = "[RENDER] ";
		break;
	case SDL_LOG_CATEGORY_SYSTEM:
		prefix = "[SYSTEM] ";
		break;
	case SDL_LOG_CATEGORY_ERROR:
		prefix = "[ERROR] ";
		break;
	case SDL_LOG_CATEGORY_AUDIO:
		prefix = "[AUDIO] ";
		break;
	default:
		prefix = "[DEFAULT] ";
		break;
	}
	std::cout << prefix << message << std::endl;
	logFile << prefix << message << std::endl;
}

void FileLogger::LoggingFunctionCB(void * userdata, int category, SDL_LogPriority priority, const char * message)
{
	FileLogger * ptr = (FileLogger *)userdata;
	if (ptr)
	{
		ptr->LoggingFunction(userdata, category, priority, message);
	}
}

FileLogger::FileLogger(const std::string & logFilePath)
{
	logFile.open(logFilePath);
	SDL_LogSetOutputFunction(&FileLogger::LoggingFunctionCB, (void*)this);

	if (!logFile.is_open())
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Could not open log file!");
}

FileLogger::~FileLogger()
{
	logFile.close();
}
