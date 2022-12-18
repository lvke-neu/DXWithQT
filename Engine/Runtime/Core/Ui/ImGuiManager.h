/***************************************************************************************
Author: lvke
Date:2022/12/18 14:47
Description:
ImGui Manager
****************************************************************************************/
#pragma once
#include "Runtime/Interface/SingletonInterface.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include <Windows.h>

namespace Twinkle
{
	class ImGuiManager
	{
		FRIEND_SINGLETON(ImGuiManager);
		PRIVATE_CONSTRUCTOR(ImGuiManager);
	public:
		void Initialize(void* hwnd);
		void Destroy();
		void Tick();
		IMGUI_IMPL_API LRESULT WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}