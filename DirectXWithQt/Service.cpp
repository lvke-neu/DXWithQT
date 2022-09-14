#include "Service.h"
#include "CameraManager.h"

void Service::call(const std::string& jsonContent, GameApp* gameApp)
{
	if (gameApp && gameApp->getScene())
	{

		CameraManager::getInstance().runFunction("setCameraPosition", gameApp->getScene()->getPerspectiveCamera(), XMFLOAT3(0, 0, 0));
		CameraManager::getInstance().runFunction("setCameraRotation", gameApp->getScene()->getPerspectiveCamera(), XMFLOAT3(0, 0, 0));
	}
}