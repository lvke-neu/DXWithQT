#pragma once

#include <map>
#include <string>
#include <functional>
#include "Camera.h"
#include "PluginInterface.h"

class CameraManager :IPlugin
{

public:
	void setCameraPosition(Camera& camera, const XMFLOAT3& pos);
	void setCameraRotation(Camera& camera, const XMFLOAT3& rot);

	void runFunction(const std::string& funcName, Camera& camera, const XMFLOAT3& pos);

private:
	std::map<std::string, std::function<void(Camera& camera, const XMFLOAT3& pos)>> m_functions;


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