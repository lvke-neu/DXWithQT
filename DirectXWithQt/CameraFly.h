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

		m_TimeSum = 0.0f;
		m_oldCameraPos = m_pCamera->getPosition();
		m_oldCameraRot = m_pCamera->getRotation();

		EventManager::getInstance().registerFrameMoveEvent(this);
	}
	~CameraFly()
	{
		EventManager::getInstance().unregisterFrameMoveEvent(this);
	}

	template<typename V, typename V1, typename V2, typename N>
	inline void Vector3Lerp(V& vOut, const V1& v1, const V2& v2, N s)
	{
		vOut.x = decltype(vOut.x)(v1.x + (v2.x - v1.x) * s);
		vOut.y = decltype(vOut.y)(v1.y + (v2.y - v1.y) * s);
		vOut.z = decltype(vOut.z)(v1.z + (v2.z - v1.z) * s);
	}

	void onFrameMove(float deltaTime)
	{
		m_TimeSum += deltaTime;


		if (m_TimeSum > 2)
			return;

		XMFLOAT3 newPos;
		Vector3Lerp(newPos, m_oldCameraPos, XMFLOAT3(0.0f, 0.0f, 0.0f), m_TimeSum / 2.0f);
		m_pCamera->setPosition(newPos);

		XMFLOAT3 newRot;
		Vector3Lerp(newRot, m_oldCameraRot, XMFLOAT3(0.0f, 0.0f, 0.0f), m_TimeSum / 2.0f);
		m_pCamera->setRotation(newRot);
	

		m_pGameApp->getScene()->notifyCameraMove();

	}
private:
	GameApp* m_pGameApp{nullptr};
	Camera* m_pCamera{ nullptr };

	float m_TimeSum{ 0.0f };
	XMFLOAT3 m_oldCameraPos;
	XMFLOAT3 m_oldCameraRot;
};