#include "PickSystem.h"
#include "PickDetection.h"
#include "../SceneManager.h"
#include "../../Core/Event/PickEventManager.h"
#include "../../Core/base/Utility.h"
#include "../../Core/collision/Ray.h"
#include "../Component/AxisComponent.h"
#include "../Component/Common/RenderStates.h"

namespace LkEngine
{
	void PickSystem::drawAxis()
	{
		if (m_axisComponent)
		{
			m_pd3dImmediateContext->OMSetBlendState(RenderStates::BSTransparent.Get(), nullptr, 0xFFFFFFFF);
			m_axisComponent->draw();
			m_pd3dImmediateContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
		}
	}

	IComponent * PickSystem::getBindedComponent()
	{
		return m_axisComponent->getBindedComponent();
	}

	void PickSystem::bindComponent(IComponent * bindComponent)
	{
		m_axisComponent->bindComponent(bindComponent);
	}

	void PickSystem::enableShow(bool flag)
	{
		m_axisComponent->enableShow(flag);
	}

	void PickSystem::init()
	{
		m_axisComponent = new AxisComponent(m_pd3dDevice, m_pd3dImmediateContext);
		InputEventManager::getInstance().registerInputEvent(this);

		LOG_INFO("PickSystem initialization is complete");
	}

	void PickSystem::onKeyPress(const Keys & key)
	{
		if (key == Keys::Key_1)
			m_dragType = DragType::SCALE;
		if (key == Keys::Key_2)
			m_dragType = DragType::ROTATION;
		if (key == Keys::Key_3)
			m_dragType = DragType::TRANSITION;
	}

	PickSystem::~PickSystem()
	{
		InputEventManager::getInstance().unRegisterInputEvent(this);
		if(m_axisComponent)
			SAFE_DELETE_SET_NULL(m_axisComponent)
	}

	void PickSystem::onMousePress(const MouseState & mouseState)
	{
		if (mouseState.mouseType == MouseType::LeftButton)
		{
			m_mouseType = MouseType::LeftButton;
			m_oldMousePos = mouseState.mousePos;
			std::string pickUuid = PickDetection::getInstance().pickDetect(mouseState.mousePos.x, mouseState.mousePos.y, SceneManager::getInstance().m_componets);
			if (pickUuid != "-1")
			{
				LOG_INFO("pick: " + pickUuid)
					m_bIsPickAxis = false;
				PickEventManager::getInstance().onPickComponent(SceneManager::getInstance().m_componets[pickUuid]);
				if (m_axisComponent)
				{
					m_axisComponent->bindComponent(SceneManager::getInstance().m_componets[pickUuid]);
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

	void PickSystem::onMouseMove(const MouseState & mouseState)
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

			drag(moveDir, moveDis);

			m_oldMousePos = mouseState.mousePos;
			PickEventManager::getInstance().onPickComponent(m_axisComponent->getBindedComponent());
		}
	}

	void PickSystem::onMouseRelease(const MouseState & mouseState)
	{
		m_mouseType = MouseType::NoButton;
	}

	void PickSystem::drag(const XMFLOAT3& moveDir, float moveDis)
	{
		if (m_dragType == DragType::TRANSITION)
		{
			auto pos = m_axisComponent->getBindedComponent()->getPosition();
			if (m_pickAxis == "RightAxis" || m_pickAxis == "RightArrowAxis")
			{
				m_axisComponent->getBindedComponent()->setPosition(moveDir.x > 0.0f ? pos.x + moveDis * 200.0f : pos.x - moveDis * 200.0f, pos.y, pos.z);
			}
			if (m_pickAxis == "ForwardAxis" || m_pickAxis == "ForwardArrowAxis")
			{
				m_axisComponent->getBindedComponent()->setPosition(pos.x, pos.y, moveDir.z < 0.0f ? pos.z - moveDis * 200.0f : pos.z + moveDis * 200.0f);
			}
			if (m_pickAxis == "UpAxis" || m_pickAxis == "UpArrowAxis")
			{
				m_axisComponent->getBindedComponent()->setPosition(pos.x, moveDir.y < 0.0f ? pos.y - moveDis * 200.0f : pos.y + moveDis * 200.0f, pos.z);
			}
		}

		if (m_dragType == DragType::SCALE)
		{
			auto scale = m_axisComponent->getBindedComponent()->getScale();
			if (m_pickAxis == "RightAxis" || m_pickAxis == "RightArrowAxis")
			{
				m_axisComponent->getBindedComponent()->setScale(moveDir.x > 0.0f ? scale.x + moveDis * 200.0f : scale.x - moveDis * 200.0f, scale.y, scale.z);
			}
			if (m_pickAxis == "ForwardAxis" || m_pickAxis == "ForwardArrowAxis")
			{
				m_axisComponent->getBindedComponent()->setScale(scale.x, scale.y, moveDir.z < 0.0f ? scale.z - moveDis * 200.0f : scale.z + moveDis * 200.0f);
			}
			if (m_pickAxis == "UpAxis" || m_pickAxis == "UpArrowAxis")
			{
				m_axisComponent->getBindedComponent()->setScale(scale.x, moveDir.y < 0.0f ? scale.y - moveDis * 200.0f : scale.y + moveDis * 200.0f, scale.z);
			}
		}

		if (m_dragType == DragType::ROTATION)
		{
			auto rot = m_axisComponent->getBindedComponent()->getRotation();
			if (m_pickAxis == "RightAxis" || m_pickAxis == "RightArrowAxis")
			{
				m_axisComponent->getBindedComponent()->setRotation(moveDir.x > 0.0f ? rot.x + moveDis * 200.0f : rot.x - moveDis * 200.0f, rot.y, rot.z);
			}
			if (m_pickAxis == "ForwardAxis" || m_pickAxis == "ForwardArrowAxis")
			{
				m_axisComponent->getBindedComponent()->setRotation(rot.x, rot.y, moveDir.z < 0.0f ? rot.z - moveDis * 200.0f : rot.z + moveDis * 200.0f);
			}
			if (m_pickAxis == "UpAxis" || m_pickAxis == "UpArrowAxis")
			{
				m_axisComponent->getBindedComponent()->setRotation(rot.x, moveDir.y < 0.0f ? rot.y - moveDis * 200.0f : rot.y + moveDis * 200.0f, rot.z);
			}
		}
	}

}

