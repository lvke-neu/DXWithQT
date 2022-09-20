/***************************************************************************************
Author: lvke
Date:
Description:
FrameMoveEventManager
****************************************************************************************/
#pragma once

#include "../base/SingletonInterface.h"
#include <vector>

namespace LkEngine
{
	class FrameMoveEvent
	{
	public:
		virtual void onFrameMove(float deltaTime) = 0;
	};

	class FrameMoveEventManager : public ISingleton<FrameMoveEventManager>
	{
	public:
		void registerFrameMoveEvent(FrameMoveEvent* frameMoveEvent);
		void unRegisterFrameMoveEvent(FrameMoveEvent* frameMoveEvent);
		void onFrameMove(float deltaTime);
	private:
		std::vector<FrameMoveEvent*> m_frameMoveEvents;
	};
}