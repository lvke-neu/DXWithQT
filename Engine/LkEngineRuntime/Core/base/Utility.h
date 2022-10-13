#include "../log/LogManager.h"
#include  <direct.h>
#include  <stdio.h>
#include <windows.h>
#include <string>

using namespace LkEngine;

#define SAFE_DELETE_SET_NULL(p) { if ((p)) { delete (p); (p) = nullptr; } } 
#define SAFERELEASE(p) { if ((p)) { (p)->Release(); (p) = nullptr; } }

#define LOG_HELPER(LOG_LEVEL, ...) \
    LogManager::getInstance().log(LOG_LEVEL, "[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__);

#define LOG_DEBUG(...) LOG_HELPER(LogManager::LogLevel::debug, __VA_ARGS__);

#define LOG_INFO(...) LOG_HELPER(LogManager::LogLevel::info, __VA_ARGS__);

#define LOG_WARN(...) LOG_HELPER(LogManager::LogLevel::warn, __VA_ARGS__);

#define LOG_ERROR(...) LOG_HELPER(LogManager::LogLevel::error, __VA_ARGS__);

#define LOG_FATAL(...) LOG_HELPER(LogManager::LogLevel::fatal, __VA_ARGS__);


#define SHOW_WIREFRAME m_pd3dImmediateContext->RSSetState(RenderStates::RSWireframe.Get());

void RelativePath2AbsolutePath(const std::string& relativePath, std::string& absolutePath);

void AbsolutePath2RelativePath(const std::string& absolutePath, std::string& relativePath);

wchar_t* multiByteToWideChar(const std::string& pKey);

char* wideCharToMultiByte(const wchar_t* pWCStrKey);

void readRelativeFile(const std::string& relativeFilePath, std::string& readContent);

void writeRelativeFile(const std::string& relativeFilePath, const std::string& writerContent);

void readAbsoluteFile(const std::string& absoluteFilePath, std::string& readContent);

void writeabsoluteFile(const std::string& absoluteFilePath, const std::string& writerContent);



