#include "AxisComponent.h"
#include "../../../LkEngineRuntime/Core/base/Utility.h"
#include "../Pick/PickDetection.h"
#include "CylinderComponent.h"
#include "ConeComponent.h"

namespace LkEngine
{
	float thickness = 2.0f;
	float length = 50.0f;

	AxisComponent::AxisComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
	{
		icUp = new CylinderComponent(pd3dDevice, pd3dImmediateContext);
		icUp->setScale(thickness, length, thickness);
		icUp->setUseTexOrColor(false, XMFLOAT4(0.0f, 1.0f, 0.0f, 0.3f));
		icUpArrow = new ConeComponent(pd3dDevice, pd3dImmediateContext);
		auto tmpPos = m_position;
		tmpPos.y += length;
		icUpArrow->setPosition(tmpPos);
		icUpArrow->setScale(thickness * 3.0f, length * 0.2f, thickness * 3.0f);
		icUpArrow->setUseTexOrColor(false, XMFLOAT4(0.0f, 1.0f, 1.0f, 0.3f));

		icRight = new CylinderComponent(pd3dDevice, pd3dImmediateContext);
		icRight->setScale(thickness, length, thickness);
		icRight->setRotation(0.0f, 0.0f, -XM_PI / 2);
		icRight->setUseTexOrColor(false, XMFLOAT4(1.0f, 0.0f, 0.0f, 0.3f));
		icRightArrow = new ConeComponent(pd3dDevice, pd3dImmediateContext);
		auto tmpPos2 = m_position;
		tmpPos2.x += length;
		icRightArrow->setPosition(tmpPos2);
		icRightArrow->setRotation(0.0f, 0.0f, -XM_PI / 2);
		icRightArrow->setScale(thickness * 3.0f, length * 0.2f, thickness * 3.0f);
		icRightArrow->setUseTexOrColor(false, XMFLOAT4(1.0f, 0.0f, 0.0f, 0.3f));
		
		icForward = new CylinderComponent(pd3dDevice, pd3dImmediateContext);
		icForward->setScale(thickness, length, thickness);
		icForward->setRotation(XM_PI / 2, 0.0f, 0.0f);
		icForward->setUseTexOrColor(false, XMFLOAT4(0.0f, 0.0f, 1.0f, 0.3f));
		icForwardArrow = new ConeComponent(pd3dDevice, pd3dImmediateContext);
		auto tmpPos3 = m_position;
		tmpPos3.z += length;
		icForwardArrow->setPosition(tmpPos3);
		icForwardArrow->setRotation(XM_PI / 2, 0.0f, 0.0f);
		icForwardArrow->setScale(thickness * 3.0f, length * 0.2f, thickness * 3.0f);
		icForwardArrow->setUseTexOrColor(false, XMFLOAT4(0.0f, 0.0f, 1.0f, 0.3f));

		m_componets.insert({ icUp->getUuId(), icUp});
		m_componets.insert({ icUpArrow->getUuId(), icUpArrow });
		m_componets.insert({ icRight->getUuId(), icRight });
		m_componets.insert({ icRightArrow->getUuId(), icRightArrow });
		m_componets.insert({ icForward->getUuId(), icForward });
		m_componets.insert({ icForwardArrow->getUuId(), icForwardArrow });

		m_UuidWithName.insert({ icUp->getUuId(), "UpAxis" });
		m_UuidWithName.insert({ icUpArrow->getUuId(), "UpArrowAxis" });
		m_UuidWithName.insert({ icRight->getUuId(), "RightAxis" });
		m_UuidWithName.insert({ icRightArrow->getUuId(), "RightArrowAxis" });
		m_UuidWithName.insert({ icForward->getUuId(), "ForwardAxis" });
		m_UuidWithName.insert({ icForwardArrow->getUuId(), "ForwardArrowAxis" });


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
	}

	void AxisComponent::onFrameMove(float deltaTime)
	{
		if (m_bShow && m_bindComponent)
		{
			auto pos = m_bindComponent->getPosition();
			if (pos.x != m_position.x || pos.y != m_position.y || pos.z != m_position.z)
			{
				m_position = pos;
				if (icUp)
				{
					icUp->setPosition(pos);

					if (icUpArrow)
					{
						auto tmpPos = pos;
						tmpPos.y += length;
						icUpArrow->setPosition(tmpPos);

					}
				}
					
				if (icRight)
				{
					icRight->setPosition(pos);
					if (icRightArrow)
					{
						auto tmpPos = pos;
						tmpPos.x += length;
						icRightArrow->setPosition(tmpPos);

					}
				}
					
				if (icForward)
				{
					icForward->setPosition(pos);
					if (icForwardArrow)
					{
						auto tmpPos = pos;
						tmpPos.z += length;
						icForwardArrow->setPosition(tmpPos);
					}
				}
					
			}
		}
	}

	void AxisComponent::bindComponent(IComponent * bindComponent)
	{
		m_bindComponent = bindComponent;
	}

	void AxisComponent::draw()
	{
		if (m_bShow)
		{
			if (icUp)
				icUp->draw();
			if (icUpArrow)
				icUpArrow->draw();
			if (icRight)
				icRight->draw();
			if (icRightArrow)
				icRightArrow->draw();
			if (icForward)
				icForward->draw();
			if (icForwardArrow)
				icForwardArrow->draw();
		}
	}

	std::string AxisComponent::pickDetection(uint16_t mouseX, uint16_t mouseY)
	{
		std::string res = PickDetection::getInstance().pickDetect(mouseX, mouseY, m_componets);
		if (res != "-1")
			return m_UuidWithName[res];
		return res;
	}
}



