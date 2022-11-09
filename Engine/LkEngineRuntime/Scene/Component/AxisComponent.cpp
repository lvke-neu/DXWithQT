#include "AxisComponent.h"
#include "../../../LkEngineRuntime/Core/base/Utility.h"
#include "../Pick/PickDetection.h"
#include "CylinderComponent.h"
#include "ConeComponent.h"
#include "BoxComponent.h"
#include "SphereComponent.h"

namespace LkEngine
{
	float thickness = 2.0f;
	float scaleCoefficient = 2.5;

	AxisComponent::AxisComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext) : m_pd3dDevice(pd3dDevice), m_pd3dImmediateContext(pd3dImmediateContext)
	{
		initAxis();
		initArrow();
		initCube();
		initSphere();

		FrameMoveEventManager::getInstance().registerFrameMoveEvent(this);
	}

	AxisComponent::~AxisComponent()
	{
		FrameMoveEventManager::getInstance().unRegisterFrameMoveEvent(this);
		SAFE_DELETE_SET_NULL(icUp)
		SAFE_DELETE_SET_NULL(icUpArrow)
		SAFE_DELETE_SET_NULL(icRight)
		SAFE_DELETE_SET_NULL(icRightArrow)
		SAFE_DELETE_SET_NULL(icForward)
		SAFE_DELETE_SET_NULL(icForwardArrow)
		SAFE_DELETE_SET_NULL(icUpCube)
		SAFE_DELETE_SET_NULL(icUpSphere)
		SAFE_DELETE_SET_NULL(icRightCube)
		SAFE_DELETE_SET_NULL(icRightSphere)
		SAFE_DELETE_SET_NULL(icForwardCube)
		SAFE_DELETE_SET_NULL(icForwardSphere)
	}

	void AxisComponent::onFrameMove(float deltaTime)
	{
		if (m_bShow && m_bindComponent)
		{
			auto pos = m_bindComponent->getPosition();
			if (pos.x != m_position.x || pos.y != m_position.y || pos.z != m_position.z)
			{
				m_position = pos;
				moveAll(pos);
			}
		}
	}

	void AxisComponent::bindComponent(IComponent * bindComponent)
	{
		m_bindComponent = bindComponent;
		if(bindComponent)
			moveAll(bindComponent->getPosition());
	}

	void AxisComponent::draw(DragType dragType)
	{
		if (m_bShow)
		{
			if (icUp)
				icUp->draw();
			if (icRight)
				icRight->draw();
			if (icForward)
				icForward->draw();

			switch (dragType)
			{
			case LkEngine::SCALE:
			{
				if (icUpCube)
					icUpCube->draw();
				if (icRightCube)
					icRightCube->draw();
				if (icForwardCube)
					icForwardCube->draw();
			}
			break;
			case LkEngine::ROTATION:
			{
				if (icUpSphere)
					icUpSphere->draw();
				if (icRightSphere)
					icRightSphere->draw();
				if (icForwardSphere)
					icForwardSphere->draw();
			}
			break;
			case LkEngine::TRANSITION:
			{
				if (icUpArrow)
					icUpArrow->draw();
				if (icRightArrow)
					icRightArrow->draw();
				if (icForwardArrow)
					icForwardArrow->draw();
			}
			break;
			}
		}
	}

	std::string AxisComponent::pickDetection(uint16_t mouseX, uint16_t mouseY, DragType dragType)
	{
		std::string res;
		switch (dragType)
		{
		case LkEngine::SCALE:
			res = PickDetection::getInstance().pickDetect(mouseX, mouseY, m_cubeComponets);
			break;
		case LkEngine::ROTATION:
			res = PickDetection::getInstance().pickDetect(mouseX, mouseY, m_sphereComponets);
			break;
		case LkEngine::TRANSITION:
			res = PickDetection::getInstance().pickDetect(mouseX, mouseY, m_arrowComponets);
			break;
		}
		if (res != "-1")
			return m_UuidWithName[res];
		return res;
	}

	void AxisComponent::setAxisLength(float length)
	{
		m_length = length;

		icUp->setScale(thickness, m_length, thickness);
		icRight->setScale(thickness, m_length, thickness);
		icForward->setScale(thickness, m_length, thickness);

		//icUpArrow->setScale(thickness * 3.0f, m_length * 0.2f, thickness * 3.0f);
		//icRightArrow->setScale(thickness * 3.0f, m_length * 0.2f, thickness * 3.0f);
		//icForwardArrow->setScale(thickness * 3.0f, m_length * 0.2f, thickness * 3.0f);

		if (m_bindComponent)
			moveAll(m_bindComponent->getPosition());
	}


	void AxisComponent::initAxis()
	{
		icUp = new CylinderComponent(m_pd3dDevice, m_pd3dImmediateContext);
		icUp->setScale(thickness, m_length, thickness);
		icUp->setUseTexOrColor(false, XMFLOAT4(0.0f, 1.0f, 0.0f, 0.3f));

		icRight = new CylinderComponent(m_pd3dDevice, m_pd3dImmediateContext);
		icRight->setScale(thickness, m_length, thickness);
		icRight->setRotation(0.0f, 0.0f, -XM_PI / 2);
		icRight->setUseTexOrColor(false, XMFLOAT4(1.0f, 0.0f, 0.0f, 0.3f));

		icForward = new CylinderComponent(m_pd3dDevice, m_pd3dImmediateContext);
		icForward->setScale(thickness, m_length, thickness);
		icForward->setRotation(XM_PI / 2, 0.0f, 0.0f);
		icForward->setUseTexOrColor(false, XMFLOAT4(0.0f, 0.0f, 1.0f, 0.3f));

		m_arrowComponets.insert({ icUp->getUuId(), icUp });
		m_arrowComponets.insert({ icRight->getUuId(), icRight });
		m_arrowComponets.insert({ icForward->getUuId(), icForward });
		m_cubeComponets.insert({ icUp->getUuId(), icUp });
		m_cubeComponets.insert({ icRight->getUuId(), icRight });
		m_cubeComponets.insert({ icForward->getUuId(), icForward });
		m_sphereComponets.insert({ icUp->getUuId(), icUp });
		m_sphereComponets.insert({ icRight->getUuId(), icRight });
		m_sphereComponets.insert({ icForward->getUuId(), icForward });
		

		m_UuidWithName.insert({ icUp->getUuId(), "UpAxis" });
		m_UuidWithName.insert({ icRight->getUuId(), "RightAxis" });
		m_UuidWithName.insert({ icForward->getUuId(), "ForwardAxis" });
	}
	void AxisComponent::initArrow()
	{
		icUpArrow = new ConeComponent(m_pd3dDevice, m_pd3dImmediateContext);
		icUpArrow->setScale(thickness * 3.0f, m_length * 0.2f, thickness * 3.0f);
		icUpArrow->setUseTexOrColor(false, XMFLOAT4(0.0f, 1.0f, 1.0f, 0.3f));

		icRightArrow = new ConeComponent(m_pd3dDevice, m_pd3dImmediateContext);
		icRightArrow->setRotation(0.0f, 0.0f, -XM_PI / 2);
		icRightArrow->setScale(thickness * 3.0f, m_length * 0.2f, thickness * 3.0f);
		icRightArrow->setUseTexOrColor(false, XMFLOAT4(1.0f, 0.0f, 0.0f, 0.3f));

		icForwardArrow = new ConeComponent(m_pd3dDevice, m_pd3dImmediateContext);
		icForwardArrow->setRotation(XM_PI / 2, 0.0f, 0.0f);
		icForwardArrow->setScale(thickness * 3.0f, m_length * 0.2f, thickness * 3.0f);
		icForwardArrow->setUseTexOrColor(false, XMFLOAT4(0.0f, 0.0f, 1.0f, 0.3f));

		m_arrowComponets.insert({ icUpArrow->getUuId(), icUpArrow });
		m_arrowComponets.insert({ icRightArrow->getUuId(), icRightArrow });
		m_arrowComponets.insert({ icForwardArrow->getUuId(), icForwardArrow });

		m_UuidWithName.insert({ icUpArrow->getUuId(), "UpArrowAxis" });
		m_UuidWithName.insert({ icRightArrow->getUuId(), "RightArrowAxis" });
		m_UuidWithName.insert({ icForwardArrow->getUuId(), "ForwardArrowAxis" });
	}
	void AxisComponent::initCube()
	{
		icUpCube = new BoxComponent(m_pd3dDevice, m_pd3dImmediateContext);
		icUpCube->setScale(scaleCoefficient, scaleCoefficient, scaleCoefficient);
		icUpCube->setUseTexOrColor(false, XMFLOAT4(0.0f, 1.0f, 1.0f, 0.3f));

		icRightCube = new BoxComponent(m_pd3dDevice, m_pd3dImmediateContext);
		icRightCube->setScale(scaleCoefficient, scaleCoefficient, scaleCoefficient);
		icRightCube->setRotation(0.0f, 0.0f, -XM_PI / 2);
		icRightCube->setUseTexOrColor(false, XMFLOAT4(1.0f, 0.0f, 0.0f, 0.3f));

		icForwardCube = new BoxComponent(m_pd3dDevice, m_pd3dImmediateContext);
		icForwardCube->setScale(scaleCoefficient, scaleCoefficient, scaleCoefficient);
		icForwardCube->setRotation(XM_PI / 2, 0.0f, 0.0f);
		icForwardCube->setUseTexOrColor(false, XMFLOAT4(0.0f, 0.0f, 1.0f, 0.3f));

		m_cubeComponets.insert({ icUpCube->getUuId(), icUpCube });
		m_cubeComponets.insert({ icRightCube->getUuId(), icRightCube });
		m_cubeComponets.insert({ icForwardCube->getUuId(), icForwardCube });

		m_UuidWithName.insert({ icUpCube->getUuId(), "UpCubeAxis" });
		m_UuidWithName.insert({ icRightCube->getUuId(), "RightCubeAxis" });
		m_UuidWithName.insert({ icForwardCube->getUuId(), "ForwardCubeAxis" });
	}
	void AxisComponent::initSphere()
	{
		icUpSphere = new SphereComponent(m_pd3dDevice, m_pd3dImmediateContext);
		icUpSphere->setScale(scaleCoefficient, scaleCoefficient, scaleCoefficient);
		icUpSphere->setUseTexOrColor(false, XMFLOAT4(0.0f, 1.0f, 1.0f, 0.3f));

		icRightSphere = new SphereComponent(m_pd3dDevice, m_pd3dImmediateContext);
		icRightSphere->setScale(scaleCoefficient, scaleCoefficient, scaleCoefficient);
		icRightSphere->setRotation(0.0f, 0.0f, -XM_PI / 2);
		icRightSphere->setUseTexOrColor(false, XMFLOAT4(1.0f, 0.0f, 0.0f, 0.3f));

		icForwardSphere = new SphereComponent(m_pd3dDevice, m_pd3dImmediateContext);
		icForwardSphere->setScale(scaleCoefficient, scaleCoefficient, scaleCoefficient);
		icForwardSphere->setRotation(XM_PI / 2, 0.0f, 0.0f);
		icForwardSphere->setUseTexOrColor(false, XMFLOAT4(0.0f, 0.0f, 1.0f, 0.3f));

		m_sphereComponets.insert({ icUpSphere->getUuId(), icUpSphere });
		m_sphereComponets.insert({ icRightSphere->getUuId(), icRightSphere });
		m_sphereComponets.insert({ icForwardSphere->getUuId(), icForwardSphere });

		m_UuidWithName.insert({ icUpSphere->getUuId(), "UpSphereAxis" });
		m_UuidWithName.insert({ icRightSphere->getUuId(), "RightSphereAxis" });
		m_UuidWithName.insert({ icForwardSphere->getUuId(), "ForwardSphereAxis" });
	}
	void AxisComponent::moveAll(const XMFLOAT3 & pos)
	{
		if (icUp)
		{
			icUp->setPosition(pos);
			auto tmpPos = pos;
			tmpPos.y += m_length;
			if (icUpArrow)
				icUpArrow->setPosition(tmpPos);
			if (icUpCube)
				icUpCube->setPosition(tmpPos);
			if (icUpSphere)
				icUpSphere->setPosition(tmpPos);
		}

		if (icRight)
		{
			icRight->setPosition(pos);
			auto tmpPos = pos;
			tmpPos.x += m_length;
			if (icRightArrow)
				icRightArrow->setPosition(tmpPos);
			if (icRightCube)
				icRightCube->setPosition(tmpPos);
			if (icRightSphere)
				icRightSphere->setPosition(tmpPos);

		}

		if (icForward)
		{
			icForward->setPosition(pos);
			auto tmpPos = pos;
			tmpPos.z += m_length;
			if (icForwardArrow)
				icForwardArrow->setPosition(tmpPos);
			if (icForwardCube)
				icForwardCube->setPosition(tmpPos);
			if (icForwardSphere)
				icForwardSphere->setPosition(tmpPos);
		}
	}
}



