#include "SceneManager.h"
#include "ECS/GameObject/BasicGeometryGameObject.h"
#include "Runtime/Utility/Utility.h"
#include "Runtime/Platform/Windows/PerspectiveCamera.h"
#include "Camera/CameraController.h"
#include "Runtime/Platform/Windows/RenderSystem.h"
#include "Runtime/Core/Log/LogManager.h"


#include "Runtime/Core/Serialization/SerializationManager.h"


namespace Twinkle
{
	IBindable* dssNoDepthTest;
	SceneManager::SceneManager()
	{
		Singleton<PerspectiveCamera>::GetInstance().SetPosition(0.0f, 0.0f, -10.0f);
		m_cameraController = new CameraController();

		m_cube = new BasicGeometryGameObject(Cube);
		m_plane = new BasicGeometryGameObject(Plane);
		m_cylinder = new BasicGeometryGameObject(Cylinder);

		if (m_cylinder->getTransformComponent())
		{
			m_cylinder->getTransformComponent()->setPosition(0.0f, 0.0f, 5.0f);
		}
		
		if (m_plane->getTransformComponent())
		{
			m_plane->getTransformComponent()->setPosition(0.0f, -5.0f, 0.0f);
		}

		if (m_plane->getMeshComponent())
		{
			m_plane->getMeshComponent()->setTexture("\\builtin\\Texture\\grass.dds");
		}

		//rttr test
		rttr::type t = rttr::type::get_by_name("Son");
		size_t sizeee = t.get_properties().size();
		
		LOG_INFO("******************************************************************");

		for (auto& prop : t.get_properties())
		{
			LOG_INFO(prop.get_name().to_string() + ", " + prop.get_type().get_name().to_string());
		}
		


		std::string jsonStr{ "" };
		Son sn;
		sn.setAge(250);
		sn.setName("lvke");
		sn.setSex(123);
		Singleton<SerializationManager>::GetInstance().Serialize(sn, jsonStr);


		
		

		rttr::variant var = rttr::type::get_by_name("Son").create();
		Singleton<SerializationManager>::GetInstance().UnSerialize(jsonStr, var);

		Son* s2 = var.get_value<Son*>();


		int i = 0;
		i++;

	}

	SceneManager::~SceneManager()
	{
		SAFE_DELETE_SETNULL(m_cube);
		SAFE_DELETE_SETNULL(m_cylinder);
		SAFE_DELETE_SETNULL(m_plane);
		SAFE_DELETE_SETNULL(m_cameraController);
	}

	void SceneManager::Tick(float deltaTime)
	{
		m_cube->tick(deltaTime);
		m_cylinder->tick(deltaTime);
		m_plane->tick(deltaTime);
	}
}