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

	class AddComponentEvent
	{
	public:
		virtual void onAddComponent(IComponent* component) = 0;
	};

	class DeleteComponentEvent
	{
	public:
		virtual void onDeleteComponent(IComponent* component) = 0;
	};

	class PickEventManager : public ISingleton<PickEventManager>
	{
	public:
		void registerPickEvent(PickEvent* pickEvent);
		void unRegisterPickEvent(PickEvent* pickEvent);
		void onPickComponent(IComponent* component);

		void registerAddComponentEvent(AddComponentEvent* addComponentEvent);
		void unRegisterAddComponentEvent(AddComponentEvent* addComponentEvent);
		void onAddComponent(IComponent* component);

		void registerDeleteComponentEvent(DeleteComponentEvent* deleteComponentEvent);
		void unRegisterDeleteComponentEvent(DeleteComponentEvent* deleteComponentEvent);
		void onDeleteComponent(IComponent* component);
	private:
		std::vector<PickEvent*> m_pickEvents;
		std::vector<AddComponentEvent*> m_addComponentEvents;
		std::vector<DeleteComponentEvent*> m_deleteComponentEvents;
	};
}