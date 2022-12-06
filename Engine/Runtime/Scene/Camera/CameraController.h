/***************************************************************************************
Author: lvke
Date:
Description:
Camera Controller
****************************************************************************************/
#pragma once

#include "Runtime/Core/Event/InputEventManager.h"
#include "Runtime/Core/Event/TickEventManager.h"

namespace Twinkle
{
	class CameraController : TickEvent
	{
	public:
		CameraController();
		~CameraController();

		virtual void tick(float deltaTime) override;
	};
}