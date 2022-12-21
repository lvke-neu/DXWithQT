#include "SceneManager.h"
#include "ECS/GameObject/BasicGeometryGameObject.h"
#include "Runtime/Utility/Utility.h"
#include "Runtime/Core/Log/LogManager.h"
#include "Runtime/Core/Ui/ImGuiManager.h"
#include "Runtime/Platform/Windows/PerspectiveCamera.h"
#include "Runtime/Platform/Windows/RenderSystem.h"

#include "Camera/CameraController.h"


namespace Twinkle
{
	IBindable* dssNoDepthTest;
	SceneManager::SceneManager()
	{
		Singleton<PerspectiveCamera>::GetInstance().SetPosition(0.0f, 0.0f, -10.0f);
		m_cameraController = new CameraController();

		IGameObject* cube = new BasicGeometryGameObject(Cube);
		IGameObject* cylinder = new BasicGeometryGameObject(Cylinder);
		IGameObject* plane = new BasicGeometryGameObject(Plane);
		IGameObject* m_light = new BasicGeometryGameObject(Sphere);

		m_sceneGameObjects.push_back(cube);
		m_sceneGameObjects.push_back(cylinder);
		m_sceneGameObjects.push_back(plane);
		m_sceneGameObjects.push_back(m_light);

		if (cylinder->getTransformComponent())
		{
			cylinder->getTransformComponent()->setPosition(0.0f, 0.0f, 5.0f);
		}
		
		if (plane->getTransformComponent())
		{
			plane->getTransformComponent()->setPosition(0.0f, -5.0f, 0.0f);
		}

		if (plane->getMeshComponent())
		{
			plane->getMeshComponent()->setTexture("\\builtin\\Texture\\grass.dds");
		}


		Singleton<ImGuiManager>::GetInstance().setSceneGameObjects(m_sceneGameObjects);
	}

	SceneManager::~SceneManager()
	{
		for (auto& go : m_sceneGameObjects)
		{
			SAFE_DELETE_SETNULL(go);
		}

		SAFE_DELETE_SETNULL(m_cameraController);
	}

	void SceneManager::Tick(float deltaTime)
	{
		for (auto& go : m_sceneGameObjects)
		{
			go->tick(deltaTime);
		}
	}
}