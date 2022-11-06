#include "SceneManager.h"
#include "../Core/base/Utility.h"
#include "Component/Common/RenderStates.h"
#include "Component/Camera/CameraManager.h"
#include "../Core/serialization/Reflection.h"
#include "../Core/engine/Engine.h"
#include "../Core/collision/Ray.h"
#include "../Core/Event/PickEventManager.h"
#include "Pick/PickDetection.h"


#include "Component/SphereComponent.h"
#include "Component/SpatialImageComponent.h"
#include "Component/ModelComponent.h"
#include "Component/CylinderComponent.h"

#include "../../LkEngineRuntime/Core/serialization/SerializationManager.h"
#include "../../LkEngineRuntime/Core/Network Request/HttpRequestManager.h"


namespace LkEngine
{
	void SceneManager::init()
	{
		REGISTER_CLASS(Reference, "BoxComponent", BoxComponent);
		REGISTER_CLASS(Reference, "SphereComponent", SphereComponent);
		REGISTER_CLASS(Reference, "SpatialImageComponent", SpatialImageComponent);
		REGISTER_CLASS(Reference, "ModelComponent", ModelComponent);
		REGISTER_CLASS(Reference, "CylinderComponent", CylinderComponent);

		RenderStates::Init(m_pd3dDevice);

		CameraManager::getInstance().setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.330000f, 1.170000f, 0.0f),
			XMFLOAT3(-139.830292f, 70.397552f, -83.729988f)
		));

		m_pPlaneComponent = new PlaneComponent(m_pd3dDevice, m_pd3dImmediateContext);
		m_pSkyBoxComponent = new SkyBoxComponent(m_pd3dDevice, m_pd3dImmediateContext);
		m_pCameraController = new CameraController;
		m_axisComponent = new AxisComponent(m_pd3dDevice, m_pd3dImmediateContext);

		InputEventManager::getInstance().registerInputEvent(this);
		LOG_INFO("SceneManager initialization is complete");

	}
	SceneManager::~SceneManager()
	{
		InputEventManager::getInstance().unRegisterInputEvent(this);

		for (auto iter = m_componets.begin(); iter!=m_componets.end(); iter++)
			SAFE_DELETE_SET_NULL(iter->second);

		SAFE_DELETE_SET_NULL(m_pPlaneComponent);
		SAFE_DELETE_SET_NULL(m_pSkyBoxComponent);
		SAFE_DELETE_SET_NULL(m_pCameraController);
		SAFE_DELETE_SET_NULL(m_axisComponent);
	}

	void SceneManager::onMousePress(const MouseState & mouseState)
	{
		if (mouseState.mouseType == MouseType::LeftButton)
		{
			m_mouseType = MouseType::LeftButton;
			m_oldMousePos = mouseState.mousePos;
			std::string pickUuid = PickDetection::getInstance().pickDetect(mouseState.mousePos.x, mouseState.mousePos.y, m_componets);
			if (pickUuid != "-1")
			{
				LOG_INFO("pick: " + pickUuid)
				m_bIsPickAxis = false;
				PickEventManager::getInstance().onPickComponent(m_componets[pickUuid]);
				if (m_axisComponent)
				{
					m_axisComponent->bindComponent(m_componets[pickUuid]);
					m_axisComponent->enableShow(true);
				}
			}
			else
			{
				pickUuid = m_axisComponent->pickDetection(mouseState.mousePos.x, mouseState.mousePos.y);

				if (pickUuid != "-1")
				{
					LOG_INFO("axis pick: " + pickUuid)
					m_bIsPickAxis = true;
					m_pickAxis = pickUuid;
				}
				else
				{
					LOG_INFO("pick: null")
					m_bIsPickAxis = false;
					if (m_axisComponent)
						m_axisComponent->enableShow(false);
				}
			}		
		}
	}

	void SceneManager::onMouseMove(const MouseState & mouseState)
	{


		if (m_mouseType == MouseType::LeftButton && m_bIsPickAxis)
		{
			XMFLOAT3 worldStartPt;
			XMFLOAT3 worldEndPt;
			Ray::ScreenPointToWorld(worldStartPt, m_oldMousePos.x, m_oldMousePos.y);
			Ray::ScreenPointToWorld(worldEndPt, mouseState.mousePos.x, mouseState.mousePos.y);
			float moveDis = sqrt(pow(worldStartPt.x - worldEndPt.x, 2) + pow(worldStartPt.y - worldEndPt.y, 2) + pow(worldStartPt.z - worldEndPt.z, 2));


			XMVECTOR worldStartPtVec;
			XMVECTOR worldEndPtVec;
			worldStartPtVec = XMLoadFloat3(&worldStartPt);
			worldEndPtVec = XMLoadFloat3(&worldEndPt);

	
			XMFLOAT3 moveDir;
			XMStoreFloat3(&moveDir, XMVector3Normalize(XMVectorSubtract(worldEndPtVec, worldStartPtVec)));
			
			if (m_pickAxis == "RightAxis")
			{
				auto pos = m_axisComponent->getBindedComponent()->getPosition();
				if (moveDir.x <= 0.0f)
					m_axisComponent->getBindedComponent()->setPosition(pos.x - moveDis * 200.0f, pos.y, pos.z);
				else
					m_axisComponent->getBindedComponent()->setPosition(pos.x + moveDis * 200.0f, pos.y, pos.z);
			}
			if (m_pickAxis == "ForwardAxis")
			{
				auto pos = m_axisComponent->getBindedComponent()->getPosition();
				if(moveDir.z >= 0.0f)
					m_axisComponent->getBindedComponent()->setPosition(pos.x, pos.y, pos.z + moveDis * 200.0f);
				else
					m_axisComponent->getBindedComponent()->setPosition(pos.x, pos.y, pos.z - moveDis * 200.0f);
			}
			if (m_pickAxis == "UpAxis")
			{
				auto pos = m_axisComponent->getBindedComponent()->getPosition();
				if (moveDir.y >= 0.0f)
					m_axisComponent->getBindedComponent()->setPosition(pos.x, pos.y + moveDis * 200.0f, pos.z);
				else
					m_axisComponent->getBindedComponent()->setPosition(pos.x, pos.y - moveDis * 200.0f, pos.z);
			}
			m_oldMousePos = mouseState.mousePos;

			PickEventManager::getInstance().onPickComponent(m_axisComponent->getBindedComponent());
		}
	}

	void SceneManager::onMouseRelease(const MouseState & mouseState)
	{
		m_mouseType = MouseType::NoButton;
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

		m_pd3dImmediateContext->OMSetBlendState(RenderStates::BSTransparent.Get(), nullptr, 0xFFFFFFFF);
		m_axisComponent->draw();
		m_pd3dImmediateContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);

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
			PickEventManager::getInstance().onDeleteComponent(iter->second);
			LOG_INFO("Delete Component: " + iter->second->getComponetType() + "-" + iter->second->getUuId());
			if (iter->second == m_axisComponent->getBindedComponent())
			{
				m_axisComponent->bindComponent(nullptr);
				m_axisComponent->enableShow(false);
			}
				
			SAFE_DELETE_SET_NULL(iter->second);
			m_componets.erase(iter);
		}
			
	}

	void SceneManager::deleteAllComponent()
	{
		for (auto it = m_componets.begin(); it != m_componets.end();)
		{
			if (it->second == m_axisComponent->getBindedComponent())
			{
				m_axisComponent->bindComponent(nullptr);
				m_axisComponent->enableShow(false);
			}

			PickEventManager::getInstance().onDeleteComponent(it->second);
			SAFE_DELETE_SET_NULL(it->second);
			it = m_componets.erase(it);
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
}

