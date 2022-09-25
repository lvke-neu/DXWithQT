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
#include "Component/Camera/CameraController.h"
#include "Component/BoxComponent.h"
#include "Component/SkyBoxComponent.h"
#include "Component/PlaneComponent.h"

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

	public:
		std::string getSkyBoxTexture();
		void setSkyBoxTexture(const std::string& skyBoxTexture);
		void setWireFrame(bool b);


	private:

		std::vector<IComponent*> m_componets;


		PlaneComponent* m_pPlaneComponent{ nullptr };
		SkyBoxComponent* m_pSkyBoxComponent{ nullptr };
		CameraController* m_pCameraController{ nullptr };

	};
}