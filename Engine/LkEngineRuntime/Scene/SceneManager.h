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
#include "Component/SkyBoxComponent.h"
#include "Component/PlaneComponent.h"
#include "../Core/Event/InputEventManager.h"
#include "Component/AxisComponent.h"

namespace LkEngine
{
	class SceneManager : public ISingleton<SceneManager>, public IManager, public InputEvent
	{
	public:
		virtual void init() override;
		void updateScene(float deltaTime);
		void drawScene();

	public:
		virtual ~SceneManager();
	public:
		virtual void onMousePress(const MouseState& mouseState) override;
		virtual void onMouseMove(const MouseState& mouseState) override;
		virtual void onMouseRelease(const MouseState& mouseState) override;
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
	private:
		bool m_bIsPickAxis{ false };
		std::string m_pickAxis;
		MouseType m_mouseType{ MouseType::NoButton };
		MousePos m_oldMousePos;
	private:
		PlaneComponent* m_pPlaneComponent{ nullptr };
		SkyBoxComponent* m_pSkyBoxComponent{ nullptr };
		CameraController* m_pCameraController{ nullptr };
		AxisComponent* m_axisComponent{ nullptr };

		std::map<std::string, IComponent*> m_componets;
	};
}