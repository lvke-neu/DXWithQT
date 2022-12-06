#include "TickEventManager.h"

namespace Twinkle
{
	void TickEventManager::NotifyTick(float deltaTime)
	{
		for (auto& event : m_events)
		{
			if (dynamic_cast<TickEvent*>(event))
			{
				dynamic_cast<TickEvent*>(event)->tick(deltaTime);
			}
		}
	}
}