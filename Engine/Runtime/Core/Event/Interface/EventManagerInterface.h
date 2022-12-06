/***************************************************************************************
Author: lvke
Date:
Description:
EventManager Interface
****************************************************************************************/
#pragma once
#include <vector>
#include "Runtime/Interface/SingletonInterface.h"

namespace Twinkle
{
	class IEvent
	{
	public:
		IEvent() = default;
		virtual ~IEvent() = default;
	};

	class IEventManager
	{
	public:
		void RegisterEvent(IEvent* event);
		void UnRegisterEvent(IEvent* event);
	protected:
		std::vector<IEvent*> m_events;
	};
}