#include "Engine.h"
#include "Runtime/Core/Log/LogManager.h"
#include "Runtime/Scene/SceneManager.h"
#include "Runtime/Scene/Component/PerspectiveCamera.h"

namespace Twinkle
{
	void Engine::Initialize(HWND hwndWindow, UINT width, UINT height)
	{
		Singleton<RenderSystem>::GetInstance().Initialize(hwndWindow, width, height);
		Singleton<PerspectiveCamera>::GetInstance().Initialize();

		m_timer.Reset();
		m_timer.Start();

		LOG_INFO("Engine Initialization is complete");
	}

	void Engine::OnResize(UINT width, UINT height)
	{
		LOG_INFO("onResize: width = " + std::to_string(width) + " height = " + std::to_string(height));

		Singleton<RenderSystem>::GetInstance().OnResize(width, height);

		Frustum frustum;
		frustum.FovAngleY = XM_PI / 3.0f;
		frustum.AspectRatio = static_cast<float>(width) / height;
		frustum.FovAngleY = 1.0f;
		frustum.FovAngleY = 1000.0f;
		Singleton<PerspectiveCamera>::GetInstance().SetFrustum(frustum);
	}

	void Engine::Update()
	{
		m_timer.Tick();
		if (m_bPause)
			return;
		
		static float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		Singleton<RenderSystem>::GetInstance().GetDeviceContent()->ClearRenderTargetView(Singleton<RenderSystem>::GetInstance().GetRenderTargetView(), color);
		Singleton<RenderSystem>::GetInstance().GetDeviceContent()->ClearDepthStencilView(Singleton<RenderSystem>::GetInstance().GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		Singleton<SceneManager>::GetInstance().Update(m_timer.DeltaTime());
		Singleton<SceneManager>::GetInstance().Draw();

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
}