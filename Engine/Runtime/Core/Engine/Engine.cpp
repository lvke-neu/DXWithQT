#include "Engine.h"
#include "../Log/LogManager.h"
#include "Runtime/Scene/SceneManager.h"
#include "../Ui/ImGuiManager.h"

namespace Twinkle
{
	void Engine::Initialize()
	{
		m_timer.Reset();
		m_timer.Start();

		LOG_INFO("Engine Initialization is complete");
	}

	void Engine::Tick()
	{
		m_timer.Tick();
		if (m_bPause)
			return;
		
		static float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		Singleton<RenderSystem>::GetInstance().GetDeviceContent()->ClearRenderTargetView(Singleton<RenderSystem>::GetInstance().GetRenderTargetView(), color);
		Singleton<RenderSystem>::GetInstance().GetDeviceContent()->ClearDepthStencilView(Singleton<RenderSystem>::GetInstance().GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		Singleton<SceneManager>::GetInstance().Tick(m_timer.DeltaTime());
	
		Singleton<ImGuiManager>::GetInstance().Tick();

		Singleton<RenderSystem>::GetInstance().GetSwapChain()->Present(0u, 0u);
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

	float Engine::GetDeltaTime()
	{
		return m_timer.DeltaTime();
	}
}