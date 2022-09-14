#pragma once

#include <map>
#include <string>
#include <functional>
#include "Camera.h"
#include "PluginInterface.h"

class CameraManager :IPlugin
{

public:
	void* setCameraPosition(void** parameter);
	void* setCameraRotation(void** parameter);

	void runFunction(const std::string& funcName, void** parameter);

private:
	std::map<std::string, std::function<void(void**)>> m_functions;


private:
	CameraManager();
	~CameraManager() {}
	CameraManager(const CameraManager& cameraManager) {}
	CameraManager& operator = (const CameraManager& cameraManager) {}

public:
	static CameraManager& getInstance()
	{
		static CameraManager instance;
		return instance;
	}
};