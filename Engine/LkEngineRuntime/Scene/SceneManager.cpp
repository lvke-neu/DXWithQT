#include "SceneManager.h"
#include "../Core/base/Utility.h"
#include "../Core/serialization/Reflection.h"
#include "../Core/engine/Engine.h"
#include "../Core/Event/PickEventManager.h"

#include "Component/Common/RenderStates.h"
#include "Component/Camera/CameraManager.h"
#include "Component/Camera/CameraController.h"
#include "Component/SkyBoxComponent.h"
#include "Component/PlaneComponent.h"
#include "Component/SphereComponent.h"
#include "Component/SpatialImageComponent.h"
#include "Component/ModelComponent.h"
#include "Component/CylinderComponent.h"
#include "Component/ConeComponent.h"

#include "Pick/PickSystem.h"


#include "../../LkEngineRuntime/Core/serialization/SerializationManager.h"
#include "../../LkEngineRuntime/Core/Network Request/HttpRequestManager.h"


namespace LkEngine
{
	void SceneManager::init()
	{
		RenderStates::Init(m_pd3dDevice);

		REGISTER_CLASS(Reference, "BoxComponent", BoxComponent);
		REGISTER_CLASS(Reference, "SphereComponent", SphereComponent);
		REGISTER_CLASS(Reference, "SpatialImageComponent", SpatialImageComponent);
		REGISTER_CLASS(Reference, "ModelComponent", ModelComponent);
		REGISTER_CLASS(Reference, "CylinderComponent", CylinderComponent);
		REGISTER_CLASS(Reference, "ConeComponent", ConeComponent);

		CameraManager::getInstance().setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.330000f, 1.170000f, 0.0f),
			XMFLOAT3(-139.830292f, 70.397552f, -83.729988f)
		));

		m_pPlaneComponent = new PlaneComponent(m_pd3dDevice, m_pd3dImmediateContext);
		m_pSkyBoxComponent = new SkyBoxComponent(m_pd3dDevice, m_pd3dImmediateContext);
		m_pCameraController = new CameraController;

		PickSystem::getInstance().initialize(m_pd3dDevice, m_pd3dImmediateContext);
		LightManager::getInstance().initialize(m_pd3dDevice, m_pd3dImmediateContext);
		LOG_INFO("SceneManager initialization is complete");
	}

	SceneManager::~SceneManager()
	{
		for (auto iter = m_componets.begin(); iter!=m_componets.end(); iter++)
			SAFE_DELETE_SET_NULL(iter->second);

		SAFE_DELETE_SET_NULL(m_pPlaneComponent);
		SAFE_DELETE_SET_NULL(m_pSkyBoxComponent);
		SAFE_DELETE_SET_NULL(m_pCameraController);
	}

	void SceneManager::updateScene(float deltaTime)
	{

	}

	void SceneManager::drawScene()
	{		
		m_pPlaneComponent->draw();

		for (auto iter = m_componets.begin(); iter != m_componets.end(); iter++)
			if(iter->second)
				iter->second->draw();

		PickSystem::getInstance().drawAxis();

		m_pSkyBoxComponent->draw();
	}
	 
	std::string SceneManager::getSkyBoxTexture()
	{
		return m_pSkyBoxComponent->getTexture();
	}

	void SceneManager::setSkyBoxTexture(const std::string& skyBoxTexture)
	{
		m_pSkyBoxComponent->setTexture(skyBoxTexture);
	}

	void SceneManager::setWireFrame(bool b)
	{
		m_pd3dImmediateContext->RSSetState(b ? RenderStates::RSWireframe.Get() : RenderStates::RSNoCull.Get());
	}

	void SceneManager::addComponent(const std::string& componentType, const std::string& modelPath)
	{
		void* parameter[2];
		parameter[0] = m_pd3dDevice.Get();
		parameter[1] = m_pd3dImmediateContext.Get();

		IComponent* ic = (IComponent*)Reflection<Reference>::getInstance().createObject(componentType, parameter);
		if (ic)
		{
			if(componentType == "ModelComponent")
			{
				((ModelComponent*)ic)->setModelPath(modelPath);
			}
			m_componets.insert({ ic->getUuId(), ic });
			PickEventManager::getInstance().onAddComponent(ic);
			LOG_INFO("Add Component: " + componentType + "-" + ic->getUuId());
		}
	}

	void SceneManager::deleteComponent(const std::string& uuid)
	{
		auto iter = m_componets.find(uuid);
		if (iter != m_componets.end())
		{
			if (iter->second == PickSystem::getInstance().getBindedComponent())
			{
				PickSystem::getInstance().bindComponent(nullptr);
				PickSystem::getInstance().enableShow(false);
			}

			auto itComTmp = iter->second;
			m_componets.erase(iter);
			PickEventManager::getInstance().onDeleteComponent(itComTmp);

			LOG_INFO("Delete Component: " + itComTmp->getComponetType() + "-" + itComTmp->getUuId());
			SAFE_DELETE_SET_NULL(itComTmp);
		}
			
	}

	void SceneManager::deleteAllComponent()
	{
		for (auto it = m_componets.begin(); it != m_componets.end();)
		{
			if (it->second == PickSystem::getInstance().getBindedComponent())
			{
				PickSystem::getInstance().bindComponent(nullptr);
				PickSystem::getInstance().enableShow(false);
			}
			auto  itComTmp = it->second;
			it = m_componets.erase(it);
			PickEventManager::getInstance().onDeleteComponent(itComTmp);
			LOG_INFO("Delete Component: " + itComTmp->getComponetType() + "-" + itComTmp->getUuId());
			SAFE_DELETE_SET_NULL(itComTmp);
			
			if (it == m_componets.end())
				break;
		}

		PickEventManager::getInstance().onPickComponent(nullptr);
	}

	void SceneManager::openSolution(const std::string& filePath)
	{
		//static int i = -1;
		//i++;
		//i = i % 3;
		//std::string str[3] = { {"scene1.lkproject"}, {"scene2.lkproject"}, {"scene3.lkproject"} };

		//std::string relativeFilePath = "assets/scene1Http.lkproject";
		//CURLcode res = HttpRequestManager::getInstance().download("http://192.168.127.128:9000/solution/"+str[i], relativeFilePath);
	
		//LOG_INFO("http code:" + std::to_string(res));


		//deleteAllComponent();

		//void* parameter[2];
		//parameter[0] = m_pd3dDevice.Get();
		//parameter[1] = m_pd3dImmediateContext.Get();
		//std::string inSerializationStr;
		//readRelativeFile(relativeFilePath, inSerializationStr);

		//rapidjson::Document docSolution;
		//if (!docSolution.Parse(inSerializationStr.c_str()).HasParseError())
		//{
		//	if (docSolution.HasMember("component"))
		//	{
		//		const rapidjson::Value& componentArr = docSolution["component"];
		//		unsigned int arrSize = componentArr.Size();
		//		for (unsigned int i = 0; i < arrSize; i++)
		//		{
		//			Reference* reference{ nullptr };

		//			rapidjson::StringBuffer buffer;
		//			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		//			componentArr[i].Accept(writer);

		//			SerializationManager::getInstance().unSerialize(reference, buffer.GetString(), parameter);

		//			if (reference)
		//			{
		//				m_componets.insert({ ((IComponent*)reference)->getUuId(), (IComponent*)reference });
		//				PickEventManager::getInstance().onAddComponent((IComponent*)reference);
		//				LOG_INFO(" Serialization addComponent-" + ((IComponent*)reference)->getComponetType() + "-" + ((IComponent*)reference)->getUuId());
		//			}
		//		}

		//	}
		//}





		deleteAllComponent();

		void* parameter[2];
		parameter[0] = m_pd3dDevice.Get();
		parameter[1] = m_pd3dImmediateContext.Get();
		std::string inSerializationStr;
		readAbsoluteFile(filePath, inSerializationStr);

		rapidjson::Document docSolution;
		if (!docSolution.Parse(inSerializationStr.c_str()).HasParseError())
		{
			if (docSolution.HasMember("component"))
			{
				const rapidjson::Value& componentArr = docSolution["component"];
				unsigned int arrSize = componentArr.Size();
				for (unsigned int i = 0; i < arrSize; i++)
				{
					Reference* reference{ nullptr };

					rapidjson::StringBuffer buffer;
					rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
					componentArr[i].Accept(writer);

					SerializationManager::getInstance().unSerialize(reference, buffer.GetString(), parameter);

					if (reference)
					{
						m_componets.insert({ ((IComponent*)reference)->getUuId(), (IComponent*)reference });
						PickEventManager::getInstance().onAddComponent((IComponent*)reference);
						LOG_INFO(" Serialization addComponent-" + ((IComponent*)reference)->getComponetType() + "-" + ((IComponent*)reference)->getUuId());
					}
				}

			}
		}

	}

	void SceneManager::saveSolution(const std::string& filePath)
	{
		rapidjson::Document docSolution;
		docSolution.SetObject();
		rapidjson::Document::AllocatorType& allocator = docSolution.GetAllocator();
		rapidjson::Value componentObjectArray(rapidjson::kArrayType);

		std::string outSerializationStr;
		rapidjson::Document docSerialization;
		for (auto iter = m_componets.begin(); iter != m_componets.end(); iter++)
		{
			SerializationManager::getInstance().serialize(iter->second, outSerializationStr);
			docSerialization.Parse(outSerializationStr.c_str());
	
			componentObjectArray.PushBack(docSerialization, allocator);
		}
		docSolution.AddMember("component", componentObjectArray, allocator);

		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		docSolution.Accept(writer);

		writeabsoluteFile(filePath, buffer.GetString());

		LOG_INFO(" Serialization success:" + filePath);
	}

	void SceneManager::setCameraMoveSpeed(float moveSpeed)
	{
		if (m_pCameraController)
		{
			m_pCameraController->setCameraMoveSpeed(moveSpeed);
		}
	}


	UINT SceneManager::getTriangleCount()
	{
		UINT triangleCount = 14;
		for (auto& component : m_componets)
		{
			triangleCount += component.second->getTriangleCount();
		}
		return triangleCount;
	}

	void SceneManager::setAxisLength(float length)
	{
		PickSystem::getInstance().setAxisLength(length);
	}

	void SceneManager::setMoveScaleCoefficient(float scaleCoefficient)
	{
		PickSystem::getInstance().setMoveScaleCoefficient(scaleCoefficient);
	}
}

