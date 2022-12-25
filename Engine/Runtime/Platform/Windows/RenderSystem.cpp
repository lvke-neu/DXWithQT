#include "RenderSystem.h"
#include "Bindable/VertexShader.h"
#include "Bindable/InputLayout.h"
#include "Bindable/PixelShader.h"
#include "Bindable/Texture.h"
#include "Bindable/SamplerState.h"
#include "Bindable/RasterizerState.h"
#include "Bindable/BlendState.h"
#include "Bindable/DepthStencilState.h"
#include "Runtime/Utility/Utility.h"
#include "Runtime/Core/Log/LogManager.h"
#include "PerspectiveCamera.h"

namespace Twinkle
{
	void RenderSystem::Initialize(HWND hwndWindow, UINT width, UINT height)
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

		Singleton<PerspectiveCamera>::GetInstance().Initialize();

		StateDesc::init();


		OnResize(width, height);
		LOG_INFO("RenderSystem Initialization is complete");
	}

	void RenderSystem::OnResize(UINT width, UINT height)
	{
		if (!m_pSwapChain || !m_pDevice || !m_pDeviceContent)
			return;

		LOG_INFO("Resize window : width = " + std::to_string(width) + ", height = " + std::to_string(height));

		//rebuild RenderTargetView
		SAFE_RELEASE(m_pRenderTargetView);
		SAFE_RELEASE(m_pDepthStencilBuffer);
		SAFE_RELEASE(m_pDepthStencilView);
		SAFE_RELEASE(m_pBackBufferSRV);

		ID3D11Texture2D* pBackBuffer{ nullptr };
		m_pSwapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
		m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
		m_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);

		//CD3D11_SHADER_RESOURCE_VIEW_DESC srvDesc(pBackBuffer, D3D11_SRV_DIMENSION_TEXTURE2D);
		HRESULT hr = m_pDevice->CreateShaderResourceView(pBackBuffer, nullptr, &m_pBackBufferSRV);

		SAFE_RELEASE(pBackBuffer);

		//rebuild DepthStencilView
		UINT _4xMsaaQuality;
		m_pDevice->CheckMultisampleQualityLevels(
			DXGI_FORMAT_R8G8B8A8_UNORM, 4, &_4xMsaaQuality);

		D3D11_TEXTURE2D_DESC depthStencilDesc;
		depthStencilDesc.Width = width;
		depthStencilDesc.Height = height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = _4xMsaaQuality - 1;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;
		m_pDevice->CreateTexture2D(&depthStencilDesc, nullptr, &m_pDepthStencilBuffer);
		m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, nullptr, &m_pDepthStencilView);

		//bind RenderTargetView and DepthStencilView
		m_pDeviceContent->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

		D3D11_VIEWPORT vp;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		vp.Width = static_cast<float>(width);
		vp.Height = static_cast<float>(height);
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		m_pDeviceContent->RSSetViewports(1, &vp);

		Singleton<PerspectiveCamera>::GetInstance().SetFrustum(XM_PI / 3.0f, static_cast<float>(width) / height, 1.0f, 1000.0f);
	}

	RenderSystem::~RenderSystem()
	{
		SAFE_RELEASE(m_pDevice);
		SAFE_RELEASE(m_pDeviceContent);
		SAFE_RELEASE(m_pSwapChain);
		SAFE_RELEASE(m_pRenderTargetView);
		SAFE_RELEASE(m_pDepthStencilBuffer);
		SAFE_RELEASE(m_pDepthStencilView);
	}

	ID3D11Device* RenderSystem::GetDevice()
	{
		return m_pDevice;
	}

	ID3D11DeviceContext* RenderSystem::GetDeviceContent()
	{
		return m_pDeviceContent;
	}

	IDXGISwapChain* RenderSystem::GetSwapChain()
	{
		return m_pSwapChain;
	}

	ID3D11RenderTargetView * RenderSystem::GetRenderTargetView()
	{
		return m_pRenderTargetView;
	}

	ID3D11Texture2D * RenderSystem::GetDepthStencilBuffer()
	{
		return m_pDepthStencilBuffer;
	}

	ID3D11DepthStencilView * RenderSystem::GetDepthStencilView()
	{
		return m_pDepthStencilView;
	}

	ID3D11ShaderResourceView * RenderSystem::GetBackBufferSRV()
	{
		return m_pBackBufferSRV;
	}


	/*******************************************Bindabel Manager*********************************************************/
	std::vector<IBindable*> RenderSystem::defaultConstantBuffers;

	IBindable* RenderSystem::CreateVertexShader(const std::string& relativeFilePath)
	{
		return new VertexShader(m_pDevice, m_pDeviceContent, relativeFilePath);
	}

	IBindable* RenderSystem::CreateInputLayout(const std::string& relativeFilePath, const std::vector<D3D11_INPUT_ELEMENT_DESC>& ied)
	{
		return new InputLayout(m_pDevice, m_pDeviceContent, relativeFilePath, ied);
	}

	IBindable* RenderSystem::CreatePixelShader(const std::string& relativeFilePath)
	{
		return new PixelShader(m_pDevice, m_pDeviceContent, relativeFilePath);
	}

	IBindable * RenderSystem::CreateTexture(UINT startSlot, const std::string & relativeFilePath)
	{
		return new Texture(m_pDevice, m_pDeviceContent, startSlot, relativeFilePath);
	}

	IBindable * RenderSystem::CreateSamplerState(UINT startSlot, SamplerStateType samplerStateType)
	{
		return new SamplerState(m_pDevice, m_pDeviceContent, startSlot, samplerStateType);
	}

	IBindable * RenderSystem::CreateRasterizerState(RasterizerStateType rasterizerStateType)
	{
		return new RasterizerState(m_pDevice, m_pDeviceContent, rasterizerStateType);
	}

	void RenderSystem::SetRasterizerState(IBindable * rasterizerState)
	{
		if (rasterizerState)
		{
			rasterizerState->bind();
		}
	}

	IBindable * RenderSystem::CreateBlendState(BlendStateType blendStateType)
	{
		return new BlendState(m_pDevice, m_pDeviceContent, blendStateType);
	}

	void RenderSystem::SetBlendState(IBindable * blendState)
	{
		if (blendState)
		{
			blendState->bind();
		}
	}

	IBindable * RenderSystem::CreateDepthStencilState(DepthStencilStateType depthStencilStateType, UINT StencilRef)
	{
		return new DepthStencilState(m_pDevice, m_pDeviceContent, depthStencilStateType, StencilRef);
	}

	void RenderSystem::SetDepthStencilState(IBindable * depthStencilState)
	{
		if (depthStencilState)
		{
			depthStencilState->bind();
		}
	}

	void RenderSystem::Release(IBindable*& bindable)
	{
		SAFE_DELETE_SETNULL(bindable);
	}

	void RenderSystem::Release(std::vector<IBindable*>& constantBuffers)
	{
		for (auto& constantBuffer : constantBuffers)
		{
			Release(constantBuffer);
		}
	}
}