/***************************************************************************************
Author: lvke
Date:2022/9/18 12:26
Description:
SceneManager
****************************************************************************************/

#pragma once

#include "../Core/base/SingletonInterface.h"
#include "../Core/base/ManagerInterface.h"
#include "Component/Interface/ComponentInterface.h"
#include "Component/Camera/Cameracontroller.h"


namespace LkEngine
{
	class SceneManager : public ISingleton<SceneManager>, public IManager
	{
	public:
		virtual void init() override;
		void updateScene(float deltaTime);
		void drawScene();

	public:
		virtual ~SceneManager();
	private:
		IComponent* m_pBoxComponent{ nullptr };
		Cameracontroller* m_cameracontroller{ nullptr };
	};
}