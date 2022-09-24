/***************************************************************************************
Author: lvke
Date:
Description:
Camera event manager
****************************************************************************************/
#pragma once

#include "../base/SingletonInterface.h"
#include <vector>

namespace LkEngine
{
	class CameraMoveEvent
	{
	public:
		virtual void onCameraMove() = 0;
	};

	class CameraFrustumChangedEvent
	{
	public:
		virtual void onCameraFrustumChanged() = 0;
	};

	class CameraChangedManager : public ISingleton<CameraChangedManager>
	{
	public:
		void registerCameraMoveEvent(CameraMoveEvent* cameraMoveEvent);
		void unRegisterCameraMoveEvent(CameraMoveEvent* cameraMoveEvent);
		void onCameraMove();

		void registerCameraFrustumChangedEvent(CameraFrustumChangedEvent* cameraFrustumChangedEvent);
		void unRegisterCameraFrustumChangedEvent(CameraFrustumChangedEvent* cameraFrustumChangedEvent);
		void onCameraFrustumChanged();
	private:
		std::vector<CameraMoveEvent*> m_cameraMoveEvents;
		std::vector<CameraFrustumChangedEvent*> m_cameraFrustumChangedEvent;
	};

}