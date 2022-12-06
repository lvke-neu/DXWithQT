/***************************************************************************************
Author: lvke
Date:2022/11/30 19:41
Description:
Twinkle Engine
****************************************************************************************/
#pragma once

#include "Runtime/Platform/Windows/RenderSystem.h"
#include "../Timer/GameTimer.h"

namespace Twinkle
{
	class Engine
	{
		FRIEND_SINGLETON(Engine);
	public:
		void Initialize();
		void Tick();
		float GetFps();
		void Pause();
		void Start();
	private:
		Engine() = default;
		virtual ~Engine() = default;
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
	private:
		GameTimer m_timer;
		bool m_bPause = false;
	};
}