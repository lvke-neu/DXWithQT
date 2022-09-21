#include "CameraController.h"
#include "CameraManager.h"

namespace LkEngine
{

	void CameraController::onKeyPress(const Keys& key)
	{
		if(!m_isKeyDown[key])
			m_isKeyDown[key] = true;
	}

	void CameraController::onKeyRelease(const Keys& key)
	{
		if (m_isKeyDown[key])
			m_isKeyDown[key] = false;
	}

	void CameraController::onMousePress(const MouseState& mouseState)
	{
		m_whichMousePress = mouseState.mouseType;
		m_oldMousePos = mouseState.mousePos;
	}


	void CameraController::onMouseRelease(const MouseState& mouseState)
	{
		if (m_whichMousePress == RightButton)
		{
			m_whichMousePress = NoButton;
		}
	}

	void CameraController::onMouseMove(const MouseState& mouseState) 
	{
		if (m_whichMousePress == RightButton)
		{
			m_mouseDeltaX = float(m_oldMousePos.x - mouseState.mousePos.x);
			m_mouseDeltaY = float(m_oldMousePos.y - mouseState.mousePos.y);
			m_oldMousePos = mouseState.mousePos;
		}
	}

	void CameraController::onMouseWheelEvent(const MouseState& mouseState) 
	{

	}

	void CameraController::onFrameMove(float deltaTime)
	{
		if (m_isKeyDown[Keys::Key_W])
			CameraManager::getInstance().moveZAxis(deltaTime * 20);
		if (m_isKeyDown[Keys::Key_S])
			CameraManager::getInstance().moveZAxis(-deltaTime * 20);
		if (m_isKeyDown[Keys::Key_A])
			CameraManager::getInstance().moveXAxis(-deltaTime * 20);
		if (m_isKeyDown[Keys::Key_D])
			CameraManager::getInstance().moveXAxis(deltaTime * 20);

		if (m_isKeyDown[Keys::Key_Up])
			CameraManager::getInstance().rotXAxis(-deltaTime);
		if (m_isKeyDown[Keys::Key_Down])
			CameraManager::getInstance().rotXAxis(deltaTime);
		if (m_isKeyDown[Keys::Key_Left])
			CameraManager::getInstance().rotYAxis(-deltaTime);
		if (m_isKeyDown[Keys::Key_Right])
			CameraManager::getInstance().rotYAxis(deltaTime);

		if (m_whichMousePress == RightButton)
		{
			XMFLOAT3 rot = CameraManager::getInstance().getRotation();
			rot.y -= m_mouseDeltaX * deltaTime * 2;
			rot.x -= m_mouseDeltaY * deltaTime * 2;
			CameraManager::getInstance().setRotation(rot);
		}
	}
}
