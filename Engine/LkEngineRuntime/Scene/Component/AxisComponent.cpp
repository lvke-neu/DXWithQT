#include "AxisComponent.h"
#include "../../../LkEngineRuntime/Core/base/Utility.h"

namespace LkEngine
{
	AxisComponent::AxisComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
	{
		icUp = new CylinderComponent(pd3dDevice, pd3dImmediateContext);
		icUp->setScale(0.5f, 10.0f, 0.5f);
		icUp->setUseTexOrColor(false, XMFLOAT4(0.0f, 1.0f, 0.0f, 0.3f));

		icRight = new CylinderComponent(pd3dDevice, pd3dImmediateContext);
		icRight->setScale(0.5f, 10.0f, 0.5f);
		icRight->setRotation(0.0f, 0.0f, -XM_PI / 2);
		icRight->setUseTexOrColor(false, XMFLOAT4(1.0f, 0.0f, 0.0f, 0.3f));

		icForward = new CylinderComponent(pd3dDevice, pd3dImmediateContext);
		icForward->setScale(0.5f, 10.0f, 0.5f);
		icForward->setRotation(-XM_PI / 2, 0.0f, 0.0f);
		icForward->setUseTexOrColor(false, XMFLOAT4(0.0f, 0.0f, 1.0f, 0.3f));

		FrameMoveEventManager::getInstance().registerFrameMoveEvent(this);
	}

	AxisComponent::~AxisComponent()
	{
		FrameMoveEventManager::getInstance().unRegisterFrameMoveEvent(this);
		SAFE_DELETE_SET_NULL(icUp)
		SAFE_DELETE_SET_NULL(icRight)
		SAFE_DELETE_SET_NULL(icForward)
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
					icUp->setPosition(pos);
				if (icRight)
					icRight->setPosition(pos);
				if (icForward)
					icForward->setPosition(pos);
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
			if (icRight)
				icRight->draw();
			if (icForward)
				icForward->draw();
		}
	}

}



