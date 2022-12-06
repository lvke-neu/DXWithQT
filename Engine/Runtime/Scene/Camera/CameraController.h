/***************************************************************************************
Author: lvke
Date:
Description:
Camera Controller
****************************************************************************************/
#pragma once

#include "Runtime/Core/Event/InputEventManager.h"
#include "Runtime/Core/Event/TickEventManager.h"

namespace Twinkle
{
	class CameraController : public InputEvent, public TickEvent
	{
	public:
		CameraController();
		~CameraController();
	public:
		virtual void onMousePress(MouseState mouseState) override;
		virtual void onMouseRelease(MouseState mouseState) override;
		virtual void onMouseMove(MouseState mouseState) override;
		virtual void onMouseWheel(MouseState mouseState) override;

		virtual void tick(float deltaTime) override;
	public:
		void setMoveSpeed(float speed);
	private:
		float m_moveSpeed = 10.0f;

		int m_oldMousePosX;
		int m_oldMousePosY;
		int m_deltaMousePosX = 0;
		int m_deltaMousePosY = 0;
	};
}