#include "SceneManager.h"
#include "ECS/GameObject/BasicGeometryGameObject.h"
#include "ECS/Component/TransformComponent.h"
#include "ECS/Component/MeshComponent.h"
#include "Runtime/Utility/Utility.h"
#include "Runtime/Platform/Windows/PerspectiveCamera.h"
#include "Camera/CameraController.h"

namespace Twinkle
{
	SceneManager::SceneManager()
	{
		Singleton<PerspectiveCamera>::GetInstance().SetPosition(0.0f, 0.0f, -10.0f);
		m_cameraController = new CameraController();

		m_cube = new BasicGeometryGameObject(Cube);
		m_plane = new BasicGeometryGameObject(Cube);
		
		TransformComponent* planeTransformComponent = dynamic_cast<TransformComponent*>(dynamic_cast<BasicGeometryGameObject*>(m_plane)->getTransformComponent());
		planeTransformComponent->setPosition(0.0f, -5.0f, 0.0f);
		planeTransformComponent->setScale(200.0f, 0.1f, 200.0f);

		MeshComponent* planeMeshComponent = dynamic_cast<MeshComponent*>(dynamic_cast<BasicGeometryGameObject*>(m_plane)->getMeshComponent());
		planeMeshComponent->setTexture("\\builtin\\Texture\\grass.dds");
	}

	SceneManager::~SceneManager()
	{
		SAFE_DELETE_SETNULL(m_cube);
		SAFE_DELETE_SETNULL(m_plane);
		SAFE_DELETE_SETNULL(m_cameraController);
	}

	void SceneManager::Tick(float deltaTime)
	{
		m_cube->tick(deltaTime);
		m_plane->tick(deltaTime);
	}
}