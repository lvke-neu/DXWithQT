#include "SceneManager.h"
#include "Camera/CameraController.h"
#include "ECS/GameObject/BasicGeometryGameObject.h"
#include "Runtime/Utility/Utility.h"
#include "Runtime/Core/Log/LogManager.h"
#include "Runtime/Core/Ui/ImGuiManager.h"
#include "Runtime/Platform/Windows/PerspectiveCamera.h"
#include "Runtime/Platform/Windows/RenderSystem.h"

namespace Twinkle
{
	IBindable* dssNoDepthTest;
	SceneManager::SceneManager()
	{
		Singleton<PerspectiveCamera>::GetInstance().SetPosition(0.0f, 0.0f, -10.0f);
		Singleton<CameraController>::GetInstance();

		IGameObject* cube = new BasicGeometryGameObject(Cube);
		IGameObject* cylinder = new BasicGeometryGameObject(Cylinder);
		IGameObject* plane = new BasicGeometryGameObject(Plane);
		IGameObject* m_light = new BasicGeometryGameObject(Sphere);
		m_light->getTransformComponent()->setScale(0.5f, 0.5f, 0.5f);
		m_light->getTransformComponent()->setPosition(0.0f, 3.0f, 0.0f);
		m_light->getMeshComponent()->setPsShader("\\builtin\\BinShader\\LightSpherePixelShader.cso");

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

	}

	void SceneManager::Tick(float deltaTime)
	{
		static float y = 0.0f;
		y += deltaTime;
		m_sceneGameObjects[0]->getTransformComponent()->setRotation(0.0f, y, 0.0f);


		for (auto& go : m_sceneGameObjects)
		{
			go->tick(deltaTime);
		}
	}
}