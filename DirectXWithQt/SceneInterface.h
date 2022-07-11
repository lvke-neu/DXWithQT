/************************************************************************
Author: lvke
Date:2022/7/2 9:41
Description:
场景接口类，每个章节的场景均继承自该类
************************************************************************/
#pragma once 


#include "Camera.h"


class IScene
{
public:
	virtual ~IScene() = default;
public:
	virtual void initScene() = 0;
	virtual void updateScene(float deltaTime) = 0;
	virtual void drawScene() = 0;
	void onResize(float width, float height) 
	{
		m_perspectiveCamera.setFrustum(XM_PI / 3, static_cast<float>(width) / height, 0.5f, 1000.0f);
	}

protected:
	Camera m_perspectiveCamera;
};