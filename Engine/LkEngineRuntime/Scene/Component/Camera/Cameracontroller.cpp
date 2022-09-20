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
		if (m_isKeyDown[Keys::W])
			CameraManager::getInstance().moveZAxis(deltaTime * 20);
		if (m_isKeyDown[Keys::S])
			CameraManager::getInstance().moveZAxis(-deltaTime * 20);
		if (m_isKeyDown[Keys::A])
			CameraManager::getInstance().moveXAxis(-deltaTime * 20);
		if (m_isKeyDown[Keys::D])
			CameraManager::getInstance().moveXAxis(deltaTime * 20);
	}
}
