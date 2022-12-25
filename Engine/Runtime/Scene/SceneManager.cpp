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
	SceneManager::SceneManager()
	{
		Singleton<PerspectiveCamera>::GetInstance().SetPosition(0.0f, 0.0f, -10.0f);
		Singleton<CameraController>::GetInstance();

		IGameObject* cube = new BasicGeometryGameObject(Cube);
		IGameObject* cylinder = new BasicGeometryGameObject(Cylinder);
		//IGameObject* plane = new BasicGeometryGameObject(Plane);
	
		m_sceneGameObjects.push_back(cube);
		m_sceneGameObjects.push_back(cylinder);
		//m_sceneGameObjects.push_back(plane);

		if (cylinder->getTransformComponent())
		{
			cylinder->getTransformComponent()->setPosition(0.0f, 0.0f, 5.0f);
		}
		
		//if (plane->getTransformComponent())
		//{
		//	plane->getTransformComponent()->setPosition(0.0f, -5.0f, 0.0f);
		//}

		//if (plane->getMeshComponent())
		//{
		//	plane->getMeshComponent()->setTexture("\\builtin\\Texture\\grass.dds");
		//}


		Singleton<ImGuiManager>::GetInstance().setSceneGameObjects(m_sceneGameObjects);

		m_dssWrtie = Singleton<RenderSystem>::GetInstance().CreateDepthStencilState(DSSWrite, 0xFF);
		m_dssMask = Singleton<RenderSystem>::GetInstance().CreateDepthStencilState(DSSMask, 0xFF);
	
	}

	SceneManager::~SceneManager()
	{
		for (auto& go : m_sceneGameObjects)
		{
			SAFE_DELETE_SETNULL(go);
		}
	}

	void SceneManager::setOutLineGO(IGameObject* outLineGO)
	{
		m_outLineGO = outLineGO;
	}

	void SceneManager::Tick(float deltaTime)
	{
		if (m_outLineGO)
		{
			Singleton<RenderSystem>::GetInstance().SetDepthStencilState(m_dssMask);

			XMFLOAT3 tmpScale = m_outLineGO->getTransformComponent()->getScale();
			std::string tmpPsShader = m_outLineGO->getMeshComponent()->getPsShader();

			m_outLineGO->getMeshComponent()->setPsShader("\\builtin\\BinShader\\LightSpherePixelShader.cso");
			m_outLineGO->getTransformComponent()->setScale(tmpScale.x + 0.05f, tmpScale.y + 0.05f, tmpScale.z + 0.05f);

			m_outLineGO->tick(deltaTime);

			m_outLineGO->getMeshComponent()->setPsShader(tmpPsShader);
			m_outLineGO->getTransformComponent()->setScale(tmpScale);
		}
			
		
		//outlineCube->getTransformComponent()->setScale(1.05, 1.05, 1.05);
		//outlineCube->getMeshComponent()->setPsShader("\\builtin\\BinShader\\LightSpherePixelShader.cso");
		//outlineCube->tick(deltaTime);
		//outlineCylinder->getTransformComponent()->setScale(1.05, 1.05, 1.05);
		//outlineCylinder->getMeshComponent()->setPsShader("\\builtin\\BinShader\\LightSpherePixelShader.cso");
		//outlineCylinder->tick(deltaTime);
		


		Singleton<RenderSystem>::GetInstance().SetDepthStencilState(m_dssWrtie);
		for (auto& go : m_sceneGameObjects)
		{
			go->tick(deltaTime);
		}

	}
}