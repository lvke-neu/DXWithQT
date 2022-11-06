#include "FrameMoveEventManager.h"

namespace LkEngine
{
	void FrameMoveEventManager::registerFrameMoveEvent(FrameMoveEvent* frameMoveEvent)
	{
		unRegisterFrameMoveEvent(frameMoveEvent);
		m_frameMoveEvents.push_back(frameMoveEvent);
	}

	void FrameMoveEventManager::unRegisterFrameMoveEvent(FrameMoveEvent* frameMoveEvent)
	{
		for (auto it = m_frameMoveEvents.begin(); it != m_frameMoveEvents.end(); ++it)
		{
			if (*it == frameMoveEvent)
			{
				it = m_frameMoveEvents.erase(it);
				if (it == m_frameMoveEvents.end())
					break;
			}
		}
	}

	void FrameMoveEventManager::onFrameMove(float deltaTime)
	{
		for (auto& frameMoveEvent : m_frameMoveEvents)
		{
			frameMoveEvent->onFrameMove(deltaTime);
		}
	}
}