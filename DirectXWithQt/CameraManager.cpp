#include "CameraManager.h"


CameraManager::CameraManager()
{
	m_functions["setCameraPosition"] = std::bind(&CameraManager::setCameraPosition, this, std::placeholders::_1);
	m_functions["setCameraRotation"] = std::bind(&CameraManager::setCameraRotation, this, std::placeholders::_1);
}


void CameraManager::runFunction(const std::string& funcName, void** parameter)
{
	m_functions[funcName](parameter);
}

void* CameraManager::setCameraPosition(void** parameter)
{
	((Camera*)parameter[0])->setPosition(*(XMFLOAT3*)parameter[1]);

	return nullptr;
}

void* CameraManager::setCameraRotation(void** parameter)
{
	((Camera*)parameter[0])->setRotation(*(XMFLOAT3*)parameter[1]);

	return nullptr;
}