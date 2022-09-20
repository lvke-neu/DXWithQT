/***************************************************************************************
Author: lvke
Date:
Description:
Camera controller
****************************************************************************************/
#pragma once

#include "../../../Core/Event/InputEventManager.h"
#include "../../../Core/Event/FrameMoveEventManager.h"
#include <map>

namespace LkEngine
{
	class Cameracontroller : public InputEvent, public FrameMoveEvent
	{
	public:
		Cameracontroller()
		{
			for (uint16_t i = 0; i <= 254; i++)
			{
				m_isKeyDown[(Keys)i] = false;
			}
			InputEventManager::getInstance().registerInputEvent(this);
			FrameMoveEventManager::getInstance().registerFrameMoveEvent(this);
		}
		~Cameracontroller()
		{
			InputEventManager::getInstance().unRegisterInputEvent(this);
			FrameMoveEventManager::getInstance().unRegisterFrameMoveEvent(this);
		}
	public:
		virtual void onKeyPress(const Keys& key) override;
		virtual void onKeyRelease(const Keys& key) override;
		virtual void onMousePress(const MouseState& mouseState) override;
		virtual void onMouseRelease(const MouseState& mouseState) override;
		virtual void onMouseMove(const MouseState& mouseState) override;
		virtual void onMouseWheelEvent(const MouseState& mouseState) override;

		virtual void onFrameMove(float deltaTime) override;
	
	private:
		std::map<Keys, bool> m_isKeyDown;
	};
}

