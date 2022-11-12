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
#include "Light/LightManager.h"

namespace LkEngine
{
	class PlaneComponent;
	class SkyBoxComponent;
	class CameraController;
	class PickSystem;

	class SceneManager : public ISingleton<SceneManager>, public IManager
	{
		friend PickSystem;
	public:
		virtual ~SceneManager();
	public:
		virtual void init() override;
		void updateScene(float deltaTime);
		void drawScene();
	public:
		std::string getSkyBoxTexture();
		void setSkyBoxTexture(const std::string& skyBoxTexture);
		void setWireFrame(bool b);
		void addComponent(const std::string& componentType, const std::string& modelPath = "");
		void deleteComponent(const std::string& uuid);
		void deleteAllComponent();
		void openSolution(const std::string& filePath);
		void saveSolution(const std::string& filePath);
		void setCameraMoveSpeed(float moveSpeed);
		UINT getTriangleCount();
		void setAxisLength(float length);
		void setMoveScaleCoefficient(float scaleCoefficient);
		DirectionLight getDirLight() { return LightManager::getInstance().getDirLight(); }
		void setDirLight(const DirectionLight& dirLight) {LightManager::getInstance().setDirLight(dirLight);}
	private:
		PlaneComponent* m_pPlaneComponent{ nullptr };
		SkyBoxComponent* m_pSkyBoxComponent{ nullptr };
		CameraController* m_pCameraController{ nullptr };

		std::map<std::string, IComponent*> m_componets;
	};
}