/***************************************************************************************
Author: lvke
Date:2022/12/18 12:44
Description:
Windows native window
****************************************************************************************/
#pragma once
#include <Windows.h>

namespace Twinkle
{
	class NativeWindow
	{
	public:
		NativeWindow(HINSTANCE hInstance);
		~NativeWindow();
		static int Run();
		HWND hwnd();
	private:
		HWND m_hwnd{ nullptr };
		HINSTANCE m_hInstance;
	};
}