/************************************************************************
Author: lvke
Date:2022/11/07 20:40
Description:
pick system, process the pick in the scene
************************************************************************/

#pragma once
#include "../../Core/base/SingletonInterface.h"
#include "../../Core/base/ManagerInterface.h"
#include "../../Core/Event/InputEventManager.h"

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
	public:
		virtual void init() override;
		virtual void onMousePress(const MouseState& mouseState) override;
		virtual void onMouseMove(const MouseState& mouseState) override;
		virtual void onMouseRelease(const MouseState& mouseState) override;

	private:
		bool m_bIsPickAxis{ false };
		std::string m_pickAxis;
		MouseType m_mouseType{ MouseType::NoButton };
		MousePos m_oldMousePos;

		AxisComponent* m_axisComponent{ nullptr };
	};
}

