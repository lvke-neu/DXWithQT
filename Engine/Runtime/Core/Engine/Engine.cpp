#include "Engine.h"
#include "../Utility/Utility.h"
#include "../Log/LogManager.h"

namespace Twinkle
{
	bool Engine::initialize(HWND hwndWindow)
	{
		HRESULT hr = S_OK;

		DXGI_SWAP_CHAIN_DESC sd = {};
		sd.BufferDesc.Width = 0;
		sd.BufferDesc.Height = 0;
		sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 0;
		sd.BufferDesc.RefreshRate.Denominator = 0;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.OutputWindow = hwndWindow;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = 0;

		hr = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			0,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&sd,
			&m_pSwapChain,
			&m_pDevice,
			nullptr,
			&m_pDeviceContent
		);

		if (hr < 0)
		{
			LOG_ERROR("D3D11CreateDeviceAndSwapChain Failed");
			return false;
		}


		m_timer.Start();
		m_timer.Reset();
		LOG_INFO("Engine initialize success");
		return true;
	}

	void Engine::update()
	{
		m_timer.Tick();
	}

	float Engine::getFps()
	{
		return m_timer.getFps();
	}

	ID3D11Device* Engine::getDevice()
	{
		return m_pDevice;
	}

	ID3D11DeviceContext* Engine::getDeviceContent()
	{
		return m_pDeviceContent;
	}

	IDXGISwapChain* Engine::getSwapChain()
	{
		return m_pSwapChain;
	}

	Engine::~Engine()
	{
		SAFE_RELEASE(m_pDevice);
		SAFE_RELEASE(m_pDeviceContent);
		SAFE_RELEASE(m_pSwapChain);
	}
}