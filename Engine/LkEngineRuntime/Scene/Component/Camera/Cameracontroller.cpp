#include "Cameracontroller.h"
#include "CameraManager.h"

namespace LkEngine
{

	void Cameracontroller::onKeyPress(const Keys& key)
	{
		if(!m_isKeyDown[key])
			m_isKeyDown[key] = true;
	}

	void Cameracontroller::onKeyRelease(const Keys& key)
	{
		if (m_isKeyDown[key])
			m_isKeyDown[key] = false;
	}

	void Cameracontroller::onMousePress(const MouseState& mouseState)
	{

	}

	void Cameracontroller::onMouseRelease(const MouseState& mouseState)
	{

	}

	void Cameracontroller::onMouseMove(const MouseState& mouseState) 
	{

	}

	void Cameracontroller::onMouseWheelEvent(const MouseState& mouseState) 
	{

	}

	void Cameracontroller::onFrameMove(float deltaTime)
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

	}
}
