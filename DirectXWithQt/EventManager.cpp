#include "EventManager.h"




void EventManager::registerCameraMoveEvent(CameraMoveEvent* cameraMoveEvent)
{
	m_cameraMoveEvents.push_back(cameraMoveEvent);
}

void EventManager::onCameraMove(const std::string& msg)
{
	for (auto& cameraMoveEvent : m_cameraMoveEvents)
	{
		cameraMoveEvent->onCameraMove(msg);
	}
}

void EventManager::unregisterCameraMoveEvent(CameraMoveEvent* cameraMoveEvent)
{
	for (auto it = m_cameraMoveEvents.begin(); it != m_cameraMoveEvents.end(); it++)
	{
		if (*it == cameraMoveEvent)
		{
			it = m_cameraMoveEvents.erase(it);
		}
	}
}

void EventManager::messaegeBox(const std::string& msg)
{
	//for (auto& chapDockWidget : m_chapDockWidgets)
	//{
	//	chapDockWidget->messaegeBox(msg);
	//}
}

void EventManager::stopTimer()
{
	//for (auto& chapDockWidget : m_chapDockWidgets)
	//{
	//	chapDockWidget->stopTimer();
	//}
}

void EventManager::startTimer()
{
	//for (auto& chapDockWidget : m_chapDockWidgets)
	//{
	//	chapDockWidget->startTimer();
	//}
}
