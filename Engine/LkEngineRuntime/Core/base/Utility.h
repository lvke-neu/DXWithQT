#include "../log/LogManager.h"
#include  <direct.h>
#include  <stdio.h>
#include <windows.h>
#include <string>

using namespace LkEngine;

#define SAFE_DELETE_SET_NULL(p) { if ((p)) { delete (p); (p) = nullptr; } } 


#define LOG_HELPER(LOG_LEVEL, ...) \
    LogManager::getInstance().log(LOG_LEVEL, "[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__);

#define LOG_DEBUG(...) LOG_HELPER(LogManager::LogLevel::debug, __VA_ARGS__);

#define LOG_INFO(...) LOG_HELPER(LogManager::LogLevel::info, __VA_ARGS__);

#define LOG_WARN(...) LOG_HELPER(LogManager::LogLevel::warn, __VA_ARGS__);

#define LOG_ERROR(...) LOG_HELPER(LogManager::LogLevel::error, __VA_ARGS__);

#define LOG_FATAL(...) LOG_HELPER(LogManager::LogLevel::fatal, __VA_ARGS__);



void RelativePath2AbsolutePath(std::string inVsShaderPath, std::string inPsShaderPath, std::string& outVsShaderPath, std::string& outPsShaderPath);

wchar_t* multiByteToWideChar(const std::string& pKey);

char* wideCharToMultiByte(const wchar_t* pWCStrKey);