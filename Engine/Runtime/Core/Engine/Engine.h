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
	enum WindowType
	{
		NativeWindow,
		Qt
	};

	class Engine
	{
		FRIEND_SINGLETON(Engine);
	public:
		void Initialize(WindowType windowType = Qt);
		void Tick();
		float GetFps();
		void Pause();
		void Start();
		float GetDeltaTime();

		bool IsShutDown();
		void ShutDown();
	private:
		Engine() = default;
		virtual ~Engine() = default;
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
	private:
		GameTimer m_timer;
		bool m_bPause = false;
		bool m_bShutDown = false;
		WindowType m_windowType{ Qt };
	};
}