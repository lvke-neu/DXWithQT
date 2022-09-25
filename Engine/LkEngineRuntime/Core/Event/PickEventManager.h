/***************************************************************************************
Author: lvke
Date:
Description:
PickEventManager
****************************************************************************************/
#pragma once

#include "../base/SingletonInterface.h"
#include "../../Scene/Component/Interface/ComponentInterface.h"
#include <vector>

namespace LkEngine
{
	class PickEvent
	{
	public:
		virtual void onPickComponent(IComponent* component) = 0;
	};

	class PickEventManager : public ISingleton<PickEventManager>
	{
	public:
		void registerPickEvent(PickEvent* pickEvent);
		void unRegisterPickEvent(PickEvent* pickEvent);
		void onPickComponent(IComponent* component);
	private:
		std::vector<PickEvent*> m_pickEvents;
	};
}