#include "InputEventManager.h"

namespace Twinkle
{
	void InputEventManager::NotifyKeyPress(KeyBoard key)
	{
		m_keyPressMap[key] = true;
		for (auto& event : m_events)
		{
			if (dynamic_cast<InputEvent*>(event))
			{
				dynamic_cast<InputEvent*>(event)->onKeyPress(key);
			}
		}
	}

	void InputEventManager::NotifyKeyRelease(KeyBoard key)
	{
		m_keyPressMap[key] = false;
		for (auto& event : m_events)
		{
			if (dynamic_cast<InputEvent*>(event))
			{
				dynamic_cast<InputEvent*>(event)->onKeyRelease(key);
			}
		}
	}

	bool InputEventManager::IsKeyPress(KeyBoard key)
	{
		if (m_keyPressMap.find(key) != m_keyPressMap.end())
			return m_keyPressMap[key];
		return false;
	}
}