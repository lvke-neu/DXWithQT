#include "Engine.h"
#include "../Utility/Utility.h"
#include "../Log/LogManager.h"

namespace Twinkle
{
	void Engine::initialize(HWND hwndWindow, UINT width, UINT height)
	{
		//create device and deviceContent
		const D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0
		};
		UINT numFeatureLevels = ARRAYSIZE(featureLevels);
		D3D_FEATURE_LEVEL featureLevel;
		D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &m_pDevice, &featureLevel, &m_pDeviceContent);

		//create swapchain
		UINT _4xMsaaQuality;
		m_pDevice->CheckMultisampleQualityLevels(
			DXGI_FORMAT_R8G8B8A8_UNORM, 4, &_4xMsaaQuality);

		IDXGIDevice* dxgiDevice = nullptr;
		IDXGIAdapter* dxgiAdapter = nullptr;
		IDXGIFactory1* dxgiFactory1 = nullptr;

		m_pDevice->QueryInterface(&dxgiDevice);
		dxgiDevice->GetAdapter(&dxgiAdapter);
		dxgiAdapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory1));

		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferDesc.Width = width;
		sd.BufferDesc.Height = height;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = _4xMsaaQuality - 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.OutputWindow = hwndWindow;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = 0;

		dxgiFactory1->CreateSwapChain(m_pDevice, &sd, &m_pSwapChain);
		dxgiFactory1->MakeWindowAssociation(hwndWindow, DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_WINDOW_CHANGES);

		onResize(width, height);

		m_timer.Reset();
		m_timer.Start();

		LOG_INFO("Engine Initialization is complete");
	}

	void Engine::onResize(UINT width, UINT height)
	{
		LOG_INFO("onResize: width = " + std::to_string(width) + " height = " + std::to_string(height));

		//rebuild RenderTargetView
		SAFE_RELEASE(m_pRenderTargetView);

		ID3D11Texture2D* pBackBuffer{ nullptr };
		m_pSwapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
		m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
		m_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);
		SAFE_RELEASE(pBackBuffer);

		m_pDeviceContent->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);

		D3D11_VIEWPORT vp;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		vp.Width = static_cast<float>(width);
		vp.Height = static_cast<float>(height);
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		m_pDeviceContent->RSSetViewports(1, &vp);
	}

	Engine::~Engine()
	{
		SAFE_RELEASE(m_pDevice);
		SAFE_RELEASE(m_pDeviceContent);
		SAFE_RELEASE(m_pSwapChain);
		SAFE_RELEASE(m_pRenderTargetView);
	}

	void Engine::update()
	{
		m_timer.Tick();
		draw();
	}

	void Engine::draw()
	{
		
		static float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		if(m_pDeviceContent)
			m_pDeviceContent->ClearRenderTargetView(m_pRenderTargetView, color);


		//vertexbuffer
		struct Vertex
		{
			float x;
			float y;
		};
		const Vertex vertices[]
		{
			{0.0f, 0.5f},
			{0.5f, -0.5f},
			{-0.5f, -0.5f}
		};

		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0u;
		bd.MiscFlags = 0u;
		bd.ByteWidth = sizeof(vertices);
		bd.StructureByteStride = sizeof(Vertex); 
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vertices;

		ID3D11Buffer* m_pVertexBuffer{ nullptr };

		m_pDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer);
		const UINT stride = sizeof(Vertex);
		const UINT offset = 0u;

		//vertexshader
		ID3D11VertexShader* m_pVertexShader{ nullptr };
		ID3DBlob* pBlob{ nullptr };
		D3DReadFileToBlob(L"E:\\C++Project\\Twinkle\\bin\\builtin\\BinShader\\VertexShader.cso", &pBlob);
		m_pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &m_pVertexShader);
		
		//inputlayout
		ID3D11InputLayout* m_inputLayout{ nullptr };
		const D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};
		m_pDevice->CreateInputLayout(ied, 1, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &m_inputLayout);
		
		//pixelshader
		ID3D11PixelShader* m_pPixelShader{ nullptr };
		ID3DBlob* pBlob2{ nullptr };
		D3DReadFileToBlob(L"E:\\C++Project\\Twinkle\\bin\\builtin\\BinShader\\PixelShader.cso", &pBlob2);
		m_pDevice->CreatePixelShader(pBlob2->GetBufferPointer(), pBlob2->GetBufferSize(), nullptr, &m_pPixelShader);



		m_pDeviceContent->IASetVertexBuffers(0u, 1u, &m_pVertexBuffer, &stride, &offset);
		m_pDeviceContent->IASetInputLayout(m_inputLayout);
		m_pDeviceContent->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_pDeviceContent->VSSetShader(m_pVertexShader, nullptr, 0u);
		m_pDeviceContent->PSSetShader(m_pPixelShader, nullptr, 0u);


		m_pDeviceContent->Draw(3u, 0u);

		if (m_pSwapChain)
			m_pSwapChain->Present(0u, 0u);

		SAFE_RELEASE(m_pVertexBuffer);
		SAFE_RELEASE(m_pVertexShader);
		SAFE_RELEASE(m_pPixelShader);
		SAFE_RELEASE(m_inputLayout);
		SAFE_RELEASE(pBlob);
		SAFE_RELEASE(pBlob2);
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
}