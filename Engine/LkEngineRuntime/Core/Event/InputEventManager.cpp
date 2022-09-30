#include "InputEventManager.h"

namespace LkEngine
{

	void InputEventManager::registerInputEvent(InputEvent* inputEvent)
	{
		unRegisterInputEvent(inputEvent);
		m_inputEvents.push_back(inputEvent);
	}

	void InputEventManager::unRegisterInputEvent(InputEvent* inputEvent) 
	{
		for (auto it = m_inputEvents.begin(); it != m_inputEvents.end();)
		{
			if (*it == inputEvent)
			{
				it = m_inputEvents.erase(it);
				if (it == m_inputEvents.end())
					break;
			}
		}
	}

	void InputEventManager::onKeyPress(const Keys& key)
	{
		for (auto& inputEvent : m_inputEvents)
		{
			inputEvent->onKeyPress(key);
		}
	}

	void InputEventManager::onKeyRelease(const Keys& key)
	{
		for (auto& inputEvent : m_inputEvents)
		{
			inputEvent->onKeyRelease(key);
		}
	}

	void InputEventManager::onMousePress(const MouseState& mouseState)
	{
		for (auto& inputEvent : m_inputEvents)
		{
			inputEvent->onMousePress(mouseState);
		}
	}

	void InputEventManager::onMouseRelease(const MouseState& mouseState)
	{
		for (auto& inputEvent : m_inputEvents)
		{
			inputEvent->onMouseRelease(mouseState);
		}
	}

	void InputEventManager::onMouseMove(const MouseState& mouseState)
	{
		for (auto& inputEvent : m_inputEvents)
		{
			inputEvent->onMouseMove(mouseState);
		}
	}

	void InputEventManager::onMouseWheelEvent(const MouseState& mouseState)
	{
		for (auto& inputEvent : m_inputEvents)
		{
			inputEvent->onMouseWheelEvent(mouseState);
		}
	}
}