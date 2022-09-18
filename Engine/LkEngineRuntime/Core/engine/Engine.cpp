#include "Engine.h"


namespace LkEngine
{

	Engine::Engine()
	{

	}

	Engine::~Engine()
	{
		if (m_pd3dImmediateContext)
			m_pd3dImmediateContext->ClearState();
	}

	void Engine::initialize(HWND hInstance, UINT windowWidth, UINT windowHeight)
	{
		m_hInstance = hInstance;
		m_windowWidth = windowWidth;
		m_windowHeight = windowHeight;

		HRESULT hr = S_OK;


		const D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0
		};
		UINT numFeatureLevels = ARRAYSIZE(featureLevels);
		D3D_FEATURE_LEVEL featureLevel;
		hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, m_pd3dDevice.GetAddressOf(), &featureLevel, m_pd3dImmediateContext.GetAddressOf());


		m_pd3dDevice->CheckMultisampleQualityLevels(
			DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_4xMsaaQuality);

		Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory1> dxgiFactory1 = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory2> dxgiFactory2 = nullptr;

		m_pd3dDevice.As(&dxgiDevice);
		dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf());
		dxgiAdapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(dxgiFactory1.GetAddressOf()));


		hr = dxgiFactory1.As(&dxgiFactory2);

		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferDesc.Width = m_windowWidth;
		sd.BufferDesc.Height = m_windowHeight;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;


		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = m_4xMsaaQuality - 1;

		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.OutputWindow = m_hInstance;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = 0;
		dxgiFactory1->CreateSwapChain(m_pd3dDevice.Get(), &sd, m_pSwapChain.GetAddressOf());

		dxgiFactory1->MakeWindowAssociation(m_hInstance, DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_WINDOW_CHANGES);

		onResize(m_windowWidth, m_windowHeight);
	}

	void Engine::updateScene(float deltaTime)
	{

	}

	void Engine::drawScene()
	{

	}

	void Engine::onResize(UINT windowWidth, UINT windowHeight)
	{
		m_windowWidth = windowWidth;
		m_windowHeight = windowHeight;


		m_pRenderTargetView.Reset();
		m_pDepthStencilView.Reset();
		m_pDepthStencilBuffer.Reset();


		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
		m_pSwapChain->ResizeBuffers(1, m_windowWidth, m_windowHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
		m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
		m_pd3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_pRenderTargetView.GetAddressOf());



		backBuffer.Reset();


		D3D11_TEXTURE2D_DESC depthStencilDesc;

		depthStencilDesc.Width = m_windowWidth;
		depthStencilDesc.Height = m_windowHeight;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;


		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = m_4xMsaaQuality - 1;

		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;


		m_pd3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, m_pDepthStencilBuffer.GetAddressOf());
		m_pd3dDevice->CreateDepthStencilView(m_pDepthStencilBuffer.Get(), nullptr, m_pDepthStencilView.GetAddressOf());



		m_pd3dImmediateContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get());

		m_ScreenViewport.TopLeftX = 0;
		m_ScreenViewport.TopLeftY = 0;
		m_ScreenViewport.Width = static_cast<float>(m_windowWidth);
		m_ScreenViewport.Height = static_cast<float>(m_windowHeight);
		m_ScreenViewport.MinDepth = 0.0f;
		m_ScreenViewport.MaxDepth = 1.0f;

		m_pd3dImmediateContext->RSSetViewports(1, &m_ScreenViewport);
	}
}

