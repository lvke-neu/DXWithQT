/************************************************************************
Author: lvke
Date:2022/09/14 21:47
Description:
相机管理类，设置相机属性（相机飞行、线框模式等等）
************************************************************************/

#pragma once


#include "Camera.h"
#include "ManagerInterface.h"
#include "CameraFly.h"

class CameraManager : public IManager
{
public:

	CameraManager(void** parameter);
	virtual ~CameraManager();
public:
	void* setCameraPosition(void** parameter);
	void* setCameraRotation(void** parameter);
	void* setCameraFly(void** parameter);
	void* setWireframe(void** parameter);

	void runFunction(const std::string functionName, void** parameter) override;
private:
	CameraFly* m_pCameraFly{ nullptr };
};