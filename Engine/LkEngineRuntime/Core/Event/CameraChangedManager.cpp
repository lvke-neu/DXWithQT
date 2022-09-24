#include "CameraChangedManager.h"

namespace LkEngine
{

	void CameraChangedManager::registerCameraMoveEvent(CameraMoveEvent* cameraMoveEvent)
	{
		unRegisterCameraMoveEvent(cameraMoveEvent);
		m_cameraMoveEvents.push_back(cameraMoveEvent);
	}

	void CameraChangedManager::unRegisterCameraMoveEvent(CameraMoveEvent* cameraMoveEvent)
	{
		for (auto it = m_cameraMoveEvents.begin(); it != m_cameraMoveEvents.end(); it++)
		{
			if (*it == cameraMoveEvent)
			{
				it = m_cameraMoveEvents.erase(it);
				if (it == m_cameraMoveEvents.end())
					break;
			}
		}
	}

	void CameraChangedManager::onCameraMove()
	{
		for (auto& cameraMoveEvent : m_cameraMoveEvents)
		{
			cameraMoveEvent->onCameraMove();
		}
	}

	void CameraChangedManager::registerCameraFrustumChangedEvent(CameraFrustumChangedEvent* cameraFrustumChangedEvent)
	{
		unRegisterCameraFrustumChangedEvent(cameraFrustumChangedEvent);
		m_cameraFrustumChangedEvent.push_back(cameraFrustumChangedEvent);
	}


	void CameraChangedManager::unRegisterCameraFrustumChangedEvent(CameraFrustumChangedEvent* cameraFrustumChangedEvent)
	{
		for (auto it = m_cameraFrustumChangedEvent.begin(); it != m_cameraFrustumChangedEvent.end(); it++)
		{
			if (*it == cameraFrustumChangedEvent)
			{
				it = m_cameraFrustumChangedEvent.erase(it);
				if (it == m_cameraFrustumChangedEvent.end())
					break;
			}
		}
	}

	void CameraChangedManager::onCameraFrustumChanged()
	{
		for (auto& cameraFrustumChangedEvent : m_cameraFrustumChangedEvent)
		{
			cameraFrustumChangedEvent->onCameraFrustumChanged();
		}
	}
}