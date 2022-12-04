#include "Engine.h"
#include "Runtime/Core/Log/LogManager.h"
#include "Runtime/Scene/SceneManager.h"

namespace Twinkle
{
	void Engine::Initialize(HWND hwndWindow, UINT width, UINT height)
	{
		Singleton<DirectX11Manager>::GetInstance().Initialize(hwndWindow, width, height);

		m_timer.Reset();
		m_timer.Start();

		LOG_INFO("Engine Initialization is complete");
	}

	void Engine::OnResize(UINT width, UINT height)
	{
		LOG_INFO("onResize: width = " + std::to_string(width) + " height = " + std::to_string(height));

		Singleton<DirectX11Manager>::GetInstance().OnResize(width, height);
	}

	void Engine::Update()
	{
		m_timer.Tick();
		if (m_bPause)
			return;
		
		static float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		Singleton<DirectX11Manager>::GetInstance().GetDeviceContent()->ClearRenderTargetView(Singleton<DirectX11Manager>::GetInstance().GetRenderTargetView(), color);
		Singleton<DirectX11Manager>::GetInstance().GetDeviceContent()->ClearDepthStencilView(Singleton<DirectX11Manager>::GetInstance().GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		Singleton<SceneManager>::GetInstance().Update(m_timer.DeltaTime());
		Singleton<SceneManager>::GetInstance().Draw();

		Singleton<DirectX11Manager>::GetInstance().GetSwapChain()->Present(0u, 0u);
	}

	float Engine::GetFps()
	{
		return m_timer.getFps();
	}

	void Engine::Pause()
	{
		m_bPause = true;
	}

	void Engine::Start()
	{
		m_bPause = false;
	}
}