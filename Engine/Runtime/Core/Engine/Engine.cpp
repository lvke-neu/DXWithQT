#include "Engine.h"
#include "../Utility/Utility.h"
#include "../Log/LogManager.h"
#include "../Bindable/VertexBuffer.h"
#include "../Bindable/IndexBuffer.h"
#include "../Bindable/VertexShader.h"
#include "../Bindable/InputLayout.h"
#include "../Bindable/PixelShader.h"

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
			float r;
			float g;
			float b;
		};
		std::vector<Vertex> vertices{

			{0.0f, 0.5f, 1.0f, 0.0f, 0.0f},
			{0.5f, 0.0f, 0.0f, 1.0f, 0.0f},
			{-0.5f, 0.0f, 0.0f, 0.0f, 1.0f},
			{0.0f, -0.5f, 1.0f, 0.0f, 0.0f}
		};
		VertexBuffer<Vertex> vertexBuffer(m_pDevice, m_pDeviceContent, vertices);

		//indexbuffer
		std::vector<UINT32> indices{ 0,1,2,2,1,3 };
		IndexBuffer<UINT32> indexBuffer(m_pDevice, m_pDeviceContent, indices, DXGI_FORMAT_R32_UINT);
	

		//vertexshader
		ID3DBlob* pBlob{ nullptr };
		D3DReadFileToBlob(L"E:\\C++Project\\Twinkle\\bin\\builtin\\BinShader\\VertexShader.cso", &pBlob);
		VertexShader vertexShader(m_pDevice, m_pDeviceContent, pBlob);
		
		//inputlayout
		std::vector<D3D11_INPUT_ELEMENT_DESC> ied
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		InputLayout inputLayout(m_pDevice, m_pDeviceContent, pBlob, ied);

		
		//pixelshader

		ID3DBlob* pBlob2{ nullptr };
		D3DReadFileToBlob(L"E:\\C++Project\\Twinkle\\bin\\builtin\\BinShader\\PixelShader.cso", &pBlob2);
		PixelShader pixelShader(m_pDevice, m_pDeviceContent, pBlob2);




		vertexBuffer.bind();
		indexBuffer.bind();
		vertexShader.bind();
		inputLayout.bind();
		pixelShader.bind();
		m_pDeviceContent->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	
		m_pDeviceContent->DrawIndexed((UINT)indices.size(), 0u, 0u);
		

		if (m_pSwapChain)
			m_pSwapChain->Present(0u, 0u);


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