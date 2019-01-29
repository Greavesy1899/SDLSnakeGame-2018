#pragma once
#ifndef FileLoggerFile
#define FileLoggerFile
#include <fstream>
#include <string>
#include "include/SDL.h"
class FileLogger
{
public:
	FileLogger(const std::string& logFilePath);
	~FileLogger();
	void LoggingFunction(void* userdata, int category, SDL_LogPriority priority, const char* message);
	static void LoggingFunctionCB(void* userdata, int category, SDL_LogPriority priority, const char* message);
private:
	std::ofstream logFile;
};
#endif