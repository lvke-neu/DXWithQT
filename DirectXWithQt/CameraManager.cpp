#include "CameraManager.h"
#include "Reflection.h"
#include"rapidjson/document.h"
#include "CameraFly.h"

REGISTER_CLASS(IManager, "CameraManager", CameraManager)


CameraManager::CameraManager(void** parameter)
{
	m_functions["setCameraPosition"] = std::bind(&CameraManager::setCameraPosition, this, std::placeholders::_1);
	m_functions["setCameraRotation"] = std::bind(&CameraManager::setCameraRotation, this, std::placeholders::_1);
	m_functions["setCameraFly"] = std::bind(&CameraManager::setCameraFly, this, std::placeholders::_1);
	
}


void CameraManager::runFunction(const std::string functionName, void** parameter)
{
	m_functions[functionName](parameter);
}

void* CameraManager::setCameraPosition(void** parameter)
{
	GameApp* gameApp = (GameApp*)parameter[0];

	rapidjson::Value* funcParameter = (rapidjson::Value*)parameter[1];

	XMFLOAT3 pos
	{
		(*funcParameter)["x"].GetFloat(),
		(*funcParameter)["y"].GetFloat(),
		(*funcParameter)["z"].GetFloat()
	}; 

	
	gameApp->getScene()->getPerspectiveCamera().setPosition(pos);
	gameApp->getScene()->notifyCameraMove();

	return nullptr;
}

void* CameraManager::setCameraRotation(void** parameter)
{
	GameApp* gameApp = (GameApp*)parameter[0];

	rapidjson::Value* funcParameter = (rapidjson::Value*)parameter[1];

	XMFLOAT3 rot
	{
		(*funcParameter)["x"].GetFloat(),
		(*funcParameter)["y"].GetFloat(),
		(*funcParameter)["z"].GetFloat()
	};

	gameApp->getScene()->getPerspectiveCamera().setRotation(rot);
	gameApp->getScene()->notifyCameraMove();

	return nullptr;
}

void* CameraManager::setCameraFly(void** parameter)
{
	GameApp* gameApp = (GameApp*)parameter[0];

	CameraFly* cameraFly = new CameraFly(&gameApp->getScene()->getPerspectiveCamera(), gameApp);
	

	return nullptr;
}