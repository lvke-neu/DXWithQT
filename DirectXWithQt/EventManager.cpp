#include "EventManager.h"
#include "GameObject.h"



void EventManager::registerCameraMoveEvent(CameraMoveEvent* cameraMoveEvent)
{
	m_cameraMoveEvents.push_back(cameraMoveEvent);
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

void EventManager::onCameraMove(const std::string& msg)
{
	for (auto& cameraMoveEvent : m_cameraMoveEvents)
	{
		cameraMoveEvent->onCameraMove(msg);
	}
}

void EventManager::registerPickEveent(PickEvent* pickEvent)
{
	m_pickEvents.push_back(pickEvent);
}

void EventManager::unregisterPickEveent(PickEvent* pickEvent)
{
	for (auto it = m_pickEvents.begin(); it != m_pickEvents.end(); it++)
	{
		if (*it == pickEvent)
		{
			it = m_pickEvents.erase(it);
		}
	}
}

void EventManager::onMouseLocateGo(const std::string& msg)
{
	for (auto& pickEvent : m_pickEvents)
	{
		pickEvent->onMouseLocateGo(msg);
	}
}

void EventManager::onPickGameObject(GameObject& go)
{
	for (auto& pickEvent : m_pickEvents)
	{
		pickEvent->onPickGameObject(go);
	}
}