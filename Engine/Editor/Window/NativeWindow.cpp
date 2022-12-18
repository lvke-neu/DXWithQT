#include "NativeWindow.h"
#include "Runtime/Core/Engine/Engine.h"
#include "Runtime/Core/Event/InputEventManager.h"
#include "Runtime/Core/Event/TickEventManager.h"
#include "Runtime/Core/Ui/ImGuiManager.h"

#include "Runtime/Core/Log/LogManager.h"

namespace Twinkle
{
	LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (Singleton<ImGuiManager>::GetInstance().WndProcHandler(hwnd, msg, wParam, lParam))
			return true;

		switch (msg)
		{
		case WM_SIZE:
			static UINT width = LOWORD(lParam);
			static UINT height = HIWORD(lParam);
			Singleton<RenderSystem>::GetInstance().OnResize(LOWORD(lParam), HIWORD(lParam));
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_MENUCHAR:
			// Don't beep when we alt-enter.
			return MAKELRESULT(0, MNC_CLOSE);
			// Catch this message so to prevent the window from becoming too small.
		case WM_GETMINMAXINFO:
			((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
			((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
			return 0;

		
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
			return 0;


		case WM_KEYDOWN:
			Singleton<InputEventManager>::GetInstance().NotifyKeyPress((KeyBoard)wParam);
			return 0;
		case WM_KEYUP:
			Singleton<InputEventManager>::GetInstance().NotifyKeyRelease((KeyBoard)wParam);
			return 0;

		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		{
			MouseState mouseState;
			mouseState.mouseButton = RightButton;
			mouseState.x = LOWORD(lParam);
			mouseState.y = HIWORD(lParam);
			if (msg == WM_RBUTTONDOWN)
				Singleton<InputEventManager>::GetInstance().NotifyMousePress(mouseState);
			if (msg == WM_RBUTTONUP)
				Singleton<InputEventManager>::GetInstance().NotifyMouseRelease(mouseState);
		}
			return 0;
		case WM_MOUSEMOVE:
		{
			MouseState mouseState;
			mouseState.mouseButton = (MouseButton)wParam;
			mouseState.x = LOWORD(lParam);
			mouseState.y = HIWORD(lParam);
			Singleton<InputEventManager>::GetInstance().NotifyMouseMove(mouseState);
		}
			return 0;
		case WM_MOUSEWHEEL:
		{
			MouseState mouseState;
			mouseState.x = LOWORD(lParam);
			mouseState.y = HIWORD(lParam);
			mouseState.delta = GET_WHEEL_DELTA_WPARAM(wParam);
			Singleton<InputEventManager>::GetInstance().NotifyMouseWheel(mouseState);
		}
			return 0;
		}

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	NativeWindow::NativeWindow(HINSTANCE hInstance)
	{
		WNDCLASS wc;
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = MainWndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(0, IDI_APPLICATION);
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
		wc.lpszMenuName = 0;
		wc.lpszClassName = "D3DWndClassName";

		if (!RegisterClass(&wc))
		{
			MessageBox(0, "RegisterClass Failed.", 0, 0);
			return ;
		}

		// Compute window rectangle dimensions based on requested client area dimensions.
		RECT R = { 0, 0, 1280, 720 };
		AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
		int width = R.right - R.left;
		int height = R.bottom - R.top;

		m_hwnd = CreateWindow("D3DWndClassName", "Twinkle-v0.002 ",
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, hInstance, 0);
		if (!m_hwnd)
		{
			MessageBox(0, "CreateWindow Failed.", 0, 0);
			return ;
		}

		ShowWindow(m_hwnd, SW_SHOW);
		UpdateWindow(m_hwnd);

		LOG_INFO(std::to_string(width) + "," + std::to_string(height));
		Singleton<RenderSystem>::GetInstance().Initialize(m_hwnd, 1280, 720);
		Singleton<Engine>::GetInstance().Initialize(WindowType::NativeWindow);
		Singleton<ImGuiManager>::GetInstance().Initialize(m_hwnd);
	}

	NativeWindow::~NativeWindow()
	{
		Singleton<ImGuiManager>::GetInstance().Destroy();
	}

	int NativeWindow::Run()
	{
		MSG msg = { 0 };

		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				//SetWindowText(m_hwnd, ("Twinkle-v0.002 " + std::to_string(Singleton<Engine>::GetInstance().GetFps())).c_str());


				

				Singleton<Engine>::GetInstance().Tick();
				Singleton<TickEventManager>::GetInstance().NotifyTick(Singleton<Engine>::GetInstance().GetDeltaTime());
			}
		}

		return (int)msg.wParam;
	}

	HWND NativeWindow::hwnd()
	{
		return m_hwnd;
	}
}