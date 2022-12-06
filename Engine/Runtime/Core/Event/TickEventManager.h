/***************************************************************************************
Author: lvke
Date:
Description:
TickEvent Manager
****************************************************************************************/
#pragma once
#include "Interface/EventManagerInterface.h"

namespace Twinkle
{
   
    class TickEvent : public virtual IEvent
    {
    public:
        virtual void tick(float deltaTime) = 0;
    };

    class TickEventManager : public IEventManager
    {
        FRIEND_SINGLETON(TickEventManager);
        PRIVATE_CONSTRUCTOR(TickEventManager);
    public:
        void NotifyTick(float deltaTime);
    };
}