#include "CameraController.h"
#include "Runtime/Platform/Windows/PerspectiveCamera.h"

namespace Twinkle
{
	CameraController::CameraController()
	{
		Singleton<InputEventManager>::GetInstance().RegisterEvent(this);
		Singleton<TickEventManager>::GetInstance().RegisterEvent(this);
	}

	CameraController::~CameraController()
	{
		Singleton<InputEventManager>::GetInstance().UnRegisterEvent(this);
		Singleton<TickEventManager>::GetInstance().UnRegisterEvent(this);
	}

	void CameraController::onMousePress(MouseState mouseState)
	{
		if (mouseState.mouseButton == RightButton)
		{
			m_oldMousePosX = mouseState.x;
			m_oldMousePosY = mouseState.y;
		}		
	}

	void CameraController::onMouseRelease(MouseState mouseState)
	{
		if (mouseState.mouseButton == RightButton)
		{
			m_deltaMousePosX = 0;
			m_deltaMousePosY = 0;
		}	
	}

	void CameraController::onMouseMove(MouseState mouseState)
	{
		if (mouseState.mouseButton == RightButton)
		{
			m_deltaMousePosX = mouseState.x - m_oldMousePosX;
			m_deltaMousePosY = mouseState.y - m_oldMousePosY;

			Singleton<PerspectiveCamera>::GetInstance().rotateXY(-m_deltaMousePosY * 0.01f, -m_deltaMousePosX * 0.01f);
			
			m_oldMousePosX = mouseState.x;
			m_oldMousePosY = mouseState.y;
		}
	}

	void CameraController::onMouseWheel(MouseState mouseState)
	{
		Singleton<PerspectiveCamera>::GetInstance().moveZAxis(mouseState.delta * m_moveSpeed * 0.001f);
	}

	void CameraController::tick(float deltaTime)
	{
		if (Singleton<InputEventManager>::GetInstance().IsKeyPress(Key_W))
		{
			Singleton<PerspectiveCamera>::GetInstance().moveZAxis(deltaTime * m_moveSpeed);
		}

		if (Singleton<InputEventManager>::GetInstance().IsKeyPress(Key_S))
		{
			Singleton<PerspectiveCamera>::GetInstance().moveZAxis(-deltaTime * m_moveSpeed);
		}

		if (Singleton<InputEventManager>::GetInstance().IsKeyPress(Key_A))
		{
			Singleton<PerspectiveCamera>::GetInstance().moveXAxis(-deltaTime * m_moveSpeed);
		}

		if (Singleton<InputEventManager>::GetInstance().IsKeyPress(Key_D))
		{
			Singleton<PerspectiveCamera>::GetInstance().moveXAxis(deltaTime * m_moveSpeed);
		}
	}

	void CameraController::setMoveSpeed(float speed)
	{
		m_moveSpeed = speed;
	}

	float CameraController::getMoveSpeed()
	{
		return m_moveSpeed;
	}
}