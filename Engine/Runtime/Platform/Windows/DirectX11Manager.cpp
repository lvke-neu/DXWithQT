#include "DirectX11Manager.h"
#include "TextureLoader/DDSTextureLoader.h"
#include "TextureLoader/WICTextureLoader.h"

namespace Twinkle
{
	void DirectX11Manager::Initialize(HWND hwndWindow, UINT width, UINT height)
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

		OnResize(width, height);
	}

	void DirectX11Manager::OnResize(UINT width, UINT height)
	{
		m_AspectRatio = static_cast<float>(width) / height;
		//rebuild RenderTargetView
		SAFE_RELEASE(m_pRenderTargetView);
		SAFE_RELEASE(m_pDepthStencilBuffer);
		SAFE_RELEASE(m_pDepthStencilView);

		ID3D11Texture2D* pBackBuffer{ nullptr };
		m_pSwapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
		m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
		m_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);
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
	}

	float DirectX11Manager::GetAspectRatio()
	{
		return m_AspectRatio;
	}

	DirectX11Manager::~DirectX11Manager()
	{
		SAFE_RELEASE(m_pDevice);
		SAFE_RELEASE(m_pDeviceContent);
		SAFE_RELEASE(m_pSwapChain);
		SAFE_RELEASE(m_pRenderTargetView);
		SAFE_RELEASE(m_pDepthStencilBuffer);
		SAFE_RELEASE(m_pDepthStencilView);
	}

	ID3DBlob * DirectX11Manager::ReadFileToBlob(const std::string & relativeFilePath)
	{
		ID3DBlob* blob{ nullptr };
		std::string absoluteFilePath;

		RelativePath2AbsolutePath(relativeFilePath, absoluteFilePath);

		D3DReadFileToBlob(multiByteToWideChar(absoluteFilePath), &blob);

		return blob;
	}

	ID3D11ShaderResourceView * DirectX11Manager::LoadTexture(const std::string & relativeFilePath)
	{
		std::string absoluteFilePath;
		ID3D11ShaderResourceView* pTextureSRV;

		RelativePath2AbsolutePath(relativeFilePath, absoluteFilePath);

		if (absoluteFilePath.substr(absoluteFilePath.size() - 3) == "dds")
		{
			DirectX::CreateDDSTextureFromFile(m_pDevice, multiByteToWideChar(absoluteFilePath), nullptr, &pTextureSRV);
		}
		else
		{
			DirectX::CreateWICTextureFromFile(m_pDevice, multiByteToWideChar(absoluteFilePath), nullptr, &pTextureSRV);
		}

		return pTextureSRV;
	}

	ID3D11Device* DirectX11Manager::GetDevice()
	{
		return m_pDevice;
	}

	ID3D11DeviceContext* DirectX11Manager::GetDeviceContent()
	{
		return m_pDeviceContent;
	}

	IDXGISwapChain* DirectX11Manager::GetSwapChain()
	{
		return m_pSwapChain;
	}

	ID3D11RenderTargetView * DirectX11Manager::GetRenderTargetView()
	{
		return m_pRenderTargetView;
	}

	ID3D11Texture2D * DirectX11Manager::GetDepthStencilBuffer()
	{
		return m_pDepthStencilBuffer;
	}

	ID3D11DepthStencilView * DirectX11Manager::GetDepthStencilView()
	{
		return m_pDepthStencilView;
	}
}