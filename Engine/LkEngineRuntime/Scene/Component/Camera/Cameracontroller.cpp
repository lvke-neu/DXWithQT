#include "CameraController.h"
#include "CameraManager.h"
#include "../../../Core/Event/CameraChangedManager.h"

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
		//if (m_whichMousePress == RightButton)
		//{
			m_oldMousePos = mouseState.mousePos;
		//}
	}


	void CameraController::onMouseRelease(const MouseState& mouseState)
	{
		//if (m_whichMousePress == RightButton)
		//{
			m_whichMousePress = NoButton;
		//}
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
		m_middleButtonDelta = mouseState.delta;
	}

	void CameraController::onFrameMove(float deltaTime)
	{
		bool bMove = false;
		if (m_isKeyDown[Keys::Key_W])
		{
			CameraManager::getInstance().moveZAxis(deltaTime * m_moveSpeed);
			bMove = true;
		}
			
		if (m_isKeyDown[Keys::Key_S])
		{
			CameraManager::getInstance().moveZAxis(-deltaTime * m_moveSpeed);
			bMove = true;
		}
			
		if (m_isKeyDown[Keys::Key_A])
		{
			CameraManager::getInstance().moveXAxis(-deltaTime * m_moveSpeed);
			bMove = true;
		}
			
		if (m_isKeyDown[Keys::Key_D])
		{
			CameraManager::getInstance().moveXAxis(deltaTime * m_moveSpeed);
			bMove = true;
		}

		//if (m_isKeyDown[Keys::Key_Up])
		//	CameraManager::getInstance().rotXAxis(-deltaTime);
		//if (m_isKeyDown[Keys::Key_Down])
		//	CameraManager::getInstance().rotXAxis(deltaTime);
		//if (m_isKeyDown[Keys::Key_Left])
		//	CameraManager::getInstance().rotYAxis(-deltaTime);
		//if (m_isKeyDown[Keys::Key_Right])
		//	CameraManager::getInstance().rotYAxis(deltaTime);

		if (m_middleButtonDelta != 0)
		{
			CameraManager::getInstance().moveZAxis(deltaTime * m_middleButtonDelta * m_moveSpeed);
			m_middleButtonDelta = 0;
		}

		if (m_whichMousePress == RightButton)
		{
			XMFLOAT3 rot = CameraManager::getInstance().getRotation();
			rot.y -= m_mouseDeltaX *  0.01f;
			rot.x -= m_mouseDeltaY *  0.01f;
			CameraManager::getInstance().setRotation(rot);
			bMove = true;
		}

		if (bMove)
			CameraChangedManager::getInstance().onCameraMove();
			
	}

	void CameraController::setCameraMoveSpeed(float moveSpeed)
	{
		m_moveSpeed = moveSpeed;
	}
}
