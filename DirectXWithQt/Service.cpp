#include "Service.h"
#include "CameraManager.h"

void Service::call(const std::string& jsonContent, GameApp* gameApp)
{



	if (gameApp && gameApp->getScene())
	{
		XMFLOAT3 pos_rot(0, 0, 0);

		void* parameter[2];
		parameter[0] = &gameApp->getScene()->getPerspectiveCamera();
		parameter[1] = &pos_rot;

		CameraManager::getInstance().runFunction("setCameraPosition", parameter);
		CameraManager::getInstance().runFunction("setCameraRotation", parameter);
	}
}