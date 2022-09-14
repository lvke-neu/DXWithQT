/***************************************************************************************
Author: lvke
Date:2022/9/14 23:00
Description:
相机飞行效果（通过贝塞尔插值）
****************************************************************************************/
#pragma once
#include "EventManager.h"
#include "Camera.h"
#include "gameApp.h"

class CameraFly : public FrameMoveEvent
{
public:
	CameraFly(Camera* camera, GameApp* gameApp)
	{
		m_pCamera = camera;
		m_pGameApp = gameApp;
		EventManager::getInstance().registerFrameMoveEvent(this);
	}
	~CameraFly()
	{
		EventManager::getInstance().unregisterFrameMoveEvent(this);
	}

	void onFrameMove(float deltaTime)
	{
		static float rot = 0.0f;
		rot += deltaTime;
		m_pCamera->setRotation(0.0f, rot, 0.0f);
		m_pGameApp->getScene()->notifyCameraMove();

	}
private:
	GameApp* m_pGameApp{nullptr};
	Camera* m_pCamera{ nullptr };
};