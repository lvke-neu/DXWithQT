#include "PickEventManager.h"

namespace LkEngine
{
	void PickEventManager::registerPickEvent(PickEvent* pickEvent)
	{
		unRegisterPickEvent(pickEvent);
		m_pickEvents.push_back(pickEvent);
	}

	void PickEventManager::unRegisterPickEvent(PickEvent* pickEvent)
	{
		for (auto it = m_pickEvents.begin(); it != m_pickEvents.end(); it++)
		{
			if (*it == pickEvent)
			{
				it = m_pickEvents.erase(it);
				if (it == m_pickEvents.end())
					break;
			}
		}
	}

	void PickEventManager::onPickComponent(IComponent* component)
	{
		for (auto& pickEvent : m_pickEvents)
		{
			pickEvent->onPickComponent(component);
		}
	}
}