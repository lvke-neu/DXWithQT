#include "SceneManager.h"
#include "../Core/base/Utility.h"
#include "Component/Common/RenderStates.h"
#include "Component/Camera/CameraManager.h"
#include "../Core/base/Reflection.h"
#include "../Core/collision/Ray.h"
#include "../Core/engine/Engine.h"

namespace LkEngine
{
	void SceneManager::init()
	{
		RenderStates::Init(m_pd3dDevice);

		CameraManager::getInstance().setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, -20.0f)
		));

		m_pPlaneComponent = new PlaneComponent(m_pd3dDevice, m_pd3dImmediateContext);
		m_pSkyBoxComponent = new SkyBoxComponent(m_pd3dDevice, m_pd3dImmediateContext);
		m_pCameraController = new CameraController;

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
		static float rot = 0.0f;
		rot += deltaTime;
		processPick();
		modifyPickedComponetProperty(deltaTime);
	}

	void SceneManager::drawScene()
	{
		for (auto iter = m_componets.begin(); iter != m_componets.end(); iter++)
			iter->second->draw();

		m_pPlaneComponent->draw();
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

	void SceneManager::addComponent(const std::string& componentType)
	{
		void* parameter[2];
		parameter[0] = m_pd3dDevice.Get();
		parameter[1] = m_pd3dImmediateContext.Get();
		IComponent* ic = Reflection<IComponent>::getInstance().createObject("BoxComponent", parameter);

		m_componets.insert({ ic->getUuId(), ic });

		LOG_INFO("addComponent-" + componentType);
	}

	void SceneManager::processPick()
	{
		if (Engine::getInstance().isMousePress(LeftButton))
		{
			Ray ray_camera2pickPoint = Ray::ScreenToRay(Engine::getInstance().getCursorPos().x, Engine::getInstance().getCursorPos().y);
			for (auto iter = m_componets.begin(); iter != m_componets.end(); iter++)
			{
				float dis;
				BoundingBox aabb;
				//LocalBoundingBox to WorldBoudingBox
				iter->second->getBoundingBox().Transform(aabb, iter->second->getTransform().getWorldMatrix());
				if (ray_camera2pickPoint.hit(aabb, dis))
				{
					m_currentPick = iter->second->getUuId();
					LOG_INFO("hit: type = " + iter->second->getComponetType() + ", uuid = " + m_currentPick);
					
					Engine::getInstance().setMousePress(LeftButton, false);
				}
				else
				{
					m_currentPick = "";
					LOG_INFO("hit: null");
					Engine::getInstance().setMousePress(LeftButton, false);
				}

			}
		}
	}

	void SceneManager::modifyPickedComponetProperty(float deltaTime)
	{
		if (Engine::getInstance().isKeyPress(Keys::Key_Up))
		{
			XMFLOAT3 pos = m_componets[m_currentPick]->getPosition();
			pos.y += deltaTime * 10;
			m_componets[m_currentPick]->setPosition(pos);
		}
		if (Engine::getInstance().isKeyPress(Keys::Key_Down))
		{
			XMFLOAT3 pos = m_componets[m_currentPick]->getPosition();
			pos.y -= deltaTime * 10;
			m_componets[m_currentPick]->setPosition(pos);
		}
		//if (Engine::getInstance().isKeyPress(Keys::Key_Up))
		//{
		//	XMFLOAT3 pos = m_componets[m_currentPick]->getPosition();
		//	pos.y += deltaTime * 10;
		//	m_componets[m_currentPick]->setPosition(pos);
		//}

			
	}
}

