#include "CameraManager.h"


CameraManager::CameraManager()
{
	m_functions["setCameraPosition"] = std::bind(&CameraManager::setCameraPosition, this, std::placeholders::_1, std::placeholders::_2);
	m_functions["setCameraRotation"] = std::bind(&CameraManager::setCameraRotation, this, std::placeholders::_1, std::placeholders::_2);
}


void CameraManager::runFunction(const std::string& funcName, Camera& camera, const XMFLOAT3& pos)
{
	m_functions[funcName](camera, pos);
}

void CameraManager::setCameraPosition(Camera& camera, const XMFLOAT3& pos)
{
	camera.setPosition(pos);
}

void CameraManager::setCameraRotation(Camera& camera, const XMFLOAT3& rot)
{
	camera.setRotation(rot);
}