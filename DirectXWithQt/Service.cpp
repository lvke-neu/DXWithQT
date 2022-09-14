#include "Service.h"

void Service::call(const std::string& jsonContent, GameApp* gameApp)
{
	if (gameApp && gameApp->getScene())
	{
		gameApp->getScene()->getPerspectiveCamera().setPosition(0, 0, 0);
		gameApp->getScene()->getPerspectiveCamera().setRotation(0, 0, 0);
	}
}