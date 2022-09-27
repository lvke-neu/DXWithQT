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


	void PickEventManager::registerAddComponentEvent(AddComponentEvent* addComponentEvent)
	{
		unRegisterAddComponentEvent(addComponentEvent);
		m_addComponentEvents.push_back(addComponentEvent);
	}

	void PickEventManager::unRegisterAddComponentEvent(AddComponentEvent* addComponentEvent)
	{
		for (auto it = m_addComponentEvents.begin(); it != m_addComponentEvents.end(); it++)
		{
			if (*it == addComponentEvent)
			{
				it = m_addComponentEvents.erase(it);
				if (it == m_addComponentEvents.end())
					break;
			}
		}
	}

	void PickEventManager::onAddComponent(IComponent* component)
	{
		for (auto& addComponentEvent : m_addComponentEvents)
		{
			addComponentEvent->onAddComponent(component);
		}
	}


	void PickEventManager::registerDeleteComponentEvent(DeleteComponentEvent* deleteComponentEvent)
	{
		unRegisterDeleteComponentEvent(deleteComponentEvent);
		m_deleteComponentEvents.push_back(deleteComponentEvent);
	}

	void PickEventManager::unRegisterDeleteComponentEvent(DeleteComponentEvent* deleteComponentEvent)
	{
		for (auto it = m_deleteComponentEvents.begin(); it != m_deleteComponentEvents.end(); it++)
		{
			if (*it == deleteComponentEvent)
			{
				it = m_deleteComponentEvents.erase(it);
				if (it == m_deleteComponentEvents.end())
					break;
			}
		}
	}

	void PickEventManager::onDeleteComponent(IComponent* component)
	{
		for (auto& deleteComponentEvent : m_deleteComponentEvents)
		{
			deleteComponentEvent->onDeleteComponent(component);
		}
	}
}