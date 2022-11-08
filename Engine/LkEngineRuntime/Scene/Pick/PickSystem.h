/************************************************************************
Author: lvke
Date:2022/11/07 20:40
Description:
pick system, process the pick in the scene
************************************************************************/

#pragma once
#include <DirectXMath.h>
#include <string>
#include "../../Core/base/SingletonInterface.h"
#include "../../Core/base/ManagerInterface.h"
#include "../../Core/Event/InputEventManager.h"
#include "../Component/AxisComponent.h"

namespace LkEngine
{
	class AxisComponent;
	class IComponent;

	class PickSystem : public ISingleton<PickSystem>, public IManager, public InputEvent
	{
	public:
		~PickSystem();
	public:
		void drawAxis();
		IComponent* getBindedComponent(); 
		void bindComponent(IComponent* bindComponent);
		void enableShow(bool flag);

		void setDragType(DragType dragType) { m_dragType = dragType; }
	public:
		virtual void init() override;
		virtual void onKeyPress(const Keys& key) override;
		virtual void onMousePress(const MouseState& mouseState) override;
		virtual void onMouseMove(const MouseState& mouseState) override;
		virtual void onMouseRelease(const MouseState& mouseState) override;

	private:
		void drag(const DirectX::XMFLOAT3& moveDir, float moveDis);
	private:
		bool m_bIsPickAxis{ false };
		std::string m_pickAxis;
		MouseType m_mouseType{ MouseType::NoButton };
		MousePos m_oldMousePos;

		AxisComponent* m_axisComponent{ nullptr };

		DragType m_dragType{ DragType::TRANSITION };
	};
}

