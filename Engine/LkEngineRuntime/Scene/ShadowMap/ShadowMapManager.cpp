#include "ShadowMapManager.h"
#include "../../Core/base/Utility.h"
#include "../../Asset/AssetManager.h"
#include "../Component/Common/VertexType.h"
#include "../Light/LightManager.h"

namespace LkEngine
{
	ShadowMapManager::~ShadowMapManager()
	{
		m_pOutputTextureSRV.Reset();
		m_pOutputTextureRTV.Reset();
		m_pOutputTextureDSV.Reset();
		m_pCacheRTV.Reset();
		m_pCacheDSV.Reset();

		m_pVertexShader.Reset();
		m_pVertexLayout.Reset();
		m_pPixelShader.Reset();
	}

	void ShadowMapManager::begin(const FLOAT backgroundColor[4])
	{
		
		m_pd3dImmediateContext->OMGetRenderTargets(1, m_pCacheRTV.GetAddressOf(), m_pCacheDSV.GetAddressOf());

		UINT num_Viewports = 1;
		m_pd3dImmediateContext->RSGetViewports(&num_Viewports, &m_CacheViewPort);


		if (!m_ShadowMap)
		{
			m_pd3dImmediateContext->ClearRenderTargetView(m_pOutputTextureRTV.Get(), backgroundColor);

		}
		m_pd3dImmediateContext->ClearDepthStencilView(m_pOutputTextureDSV.Get(), D3D11_CLEAR_DEPTH | (m_ShadowMap ? 0 : D3D11_CLEAR_STENCIL), 1.0f, 0);


		m_pd3dImmediateContext->OMSetRenderTargets((m_ShadowMap ? 0 : 1),
			(m_ShadowMap ? nullptr : m_pOutputTextureRTV.GetAddressOf()),
			m_pOutputTextureDSV.Get());
	
		m_pd3dImmediateContext->RSSetViewports(1, &m_OutputViewPort);

		bindPipeState();
	}

	void ShadowMapManager::bindPipeState()
	{
		m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());
		m_pd3dImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
		m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);

		m_pd3dImmediateContext->VSSetConstantBuffers(10, 1, m_pViewMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(10, 1, m_pViewMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->VSSetConstantBuffers(11, 1, m_pProjMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(11, 1, m_pProjMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->VSSetConstantBuffers(12, 1, m_pShadowTransformCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(12, 1, m_pShadowTransformCB.GetAddressOf());
	}

	void ShadowMapManager::end()
	{

		m_pd3dImmediateContext->RSSetViewports(1, &m_CacheViewPort);
		m_pd3dImmediateContext->OMSetRenderTargets(1, m_pCacheRTV.GetAddressOf(), m_pCacheDSV.Get());

		if (m_GenerateMips)
		{
			m_pd3dImmediateContext->GenerateMips(m_pOutputTextureSRV.Get());
		}


		m_pCacheDSV.Reset();
		m_pCacheRTV.Reset();
	}

	void ShadowMapManager::init()
	{
		initResource(2048, 2048, true);
		LOG_INFO("ShadowMapManager initialization is complete")
	}

	void ShadowMapManager::initResource(int texWidth, int texHeight, bool shadowMap, bool generateMips)
	{
		m_pOutputTextureSRV.Reset();
		m_pOutputTextureRTV.Reset();
		m_pOutputTextureDSV.Reset();
		m_pCacheRTV.Reset();
		m_pCacheDSV.Reset();

		m_ShadowMap = shadowMap;
		m_GenerateMips = false;

		if (!m_ShadowMap)
		{
			m_GenerateMips = generateMips;


			ComPtr<ID3D11Texture2D> texture;
			CD3D11_TEXTURE2D_DESC texDesc(DXGI_FORMAT_R8G8B8A8_UNORM, texWidth, texHeight, 1,
				(m_GenerateMips ? 0 : 1), D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE,
				D3D11_USAGE_DEFAULT, 0, 1, 0, (m_GenerateMips ? D3D11_RESOURCE_MISC_GENERATE_MIPS : 0));

			m_pd3dDevice->CreateTexture2D(&texDesc, nullptr, texture.GetAddressOf());

			CD3D11_RENDER_TARGET_VIEW_DESC rtvDesc(texture.Get(), D3D11_RTV_DIMENSION_TEXTURE2D);

			m_pd3dDevice->CreateRenderTargetView(texture.Get(), &rtvDesc, m_pOutputTextureRTV.GetAddressOf());

			CD3D11_SHADER_RESOURCE_VIEW_DESC srvDesc(texture.Get(), D3D11_SRV_DIMENSION_TEXTURE2D);

			m_pd3dDevice->CreateShaderResourceView(texture.Get(), &srvDesc,
				m_pOutputTextureSRV.GetAddressOf());

		}

		CD3D11_TEXTURE2D_DESC texDesc((m_ShadowMap ? DXGI_FORMAT_R24G8_TYPELESS : DXGI_FORMAT_D24_UNORM_S8_UINT),
			texWidth, texHeight, 1, 1,
			D3D11_BIND_DEPTH_STENCIL | (m_ShadowMap ? D3D11_BIND_SHADER_RESOURCE : 0));

		ComPtr<ID3D11Texture2D> depthTex;
		m_pd3dDevice->CreateTexture2D(&texDesc, nullptr, depthTex.GetAddressOf());

		CD3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc(depthTex.Get(), D3D11_DSV_DIMENSION_TEXTURE2D, DXGI_FORMAT_D24_UNORM_S8_UINT);

		m_pd3dDevice->CreateDepthStencilView(depthTex.Get(), &dsvDesc,
			m_pOutputTextureDSV.GetAddressOf());


		if (m_ShadowMap)
		{
			CD3D11_SHADER_RESOURCE_VIEW_DESC srvDesc(depthTex.Get(), D3D11_SRV_DIMENSION_TEXTURE2D, DXGI_FORMAT_R24_UNORM_X8_TYPELESS);

			m_pd3dDevice->CreateShaderResourceView(depthTex.Get(), &srvDesc,
				m_pOutputTextureSRV.GetAddressOf());
		}

		m_OutputViewPort.TopLeftX = 0.0f;
		m_OutputViewPort.TopLeftY = 0.0f;
		m_OutputViewPort.Width = static_cast<float>(texWidth);
		m_OutputViewPort.Height = static_cast<float>(texHeight);
		m_OutputViewPort.MinDepth = 0.0f;
		m_OutputViewPort.MaxDepth = 1.0f;
		
		initShaderAndInputLayout();
		initViewAndProjMatrix();
	}

	void ShadowMapManager::initShaderAndInputLayout()
	{
		m_pVertexShader.Reset();
		m_pVertexLayout.Reset();
		m_pPixelShader.Reset();

		ComPtr<ID3DBlob> blob;

		m_pVertexShader = AssetManager::getInstance().loadVsShaderAsset("builtin\\Shader\\ShadowMapVS.cso", blob);
		m_pd3dDevice->CreateInputLayout(VertexPosNormalTex::inputLayout, 3, blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout.GetAddressOf());
		m_pPixelShader = AssetManager::getInstance().loadPsShaderAsset("builtin\\Shader\\ShadowMapPS.cso");
	}

	void ShadowMapManager::initViewAndProjMatrix()
	{
		m_pViewMatrixCB.Reset();
		m_pProjMatrixCB.Reset();

		D3D11_BUFFER_DESC cbd;
		ZeroMemory(&cbd, sizeof(cbd));
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.ByteWidth = sizeof(ViewMatrix);
		m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pViewMatrixCB.GetAddressOf());

		D3D11_BUFFER_DESC cbd2;
		ZeroMemory(&cbd2, sizeof(cbd2));
		cbd2.Usage = D3D11_USAGE_DYNAMIC;
		cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd2.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd2.ByteWidth = sizeof(ProjMatrix);
		m_pd3dDevice->CreateBuffer(&cbd2, nullptr, m_pProjMatrixCB.GetAddressOf());


		D3D11_BUFFER_DESC cbd3;
		ZeroMemory(&cbd3, sizeof(cbd3));
		cbd3.Usage = D3D11_USAGE_DYNAMIC;
		cbd3.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd3.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd3.ByteWidth = sizeof(ShadowTransform);
		m_pd3dDevice->CreateBuffer(&cbd3, nullptr, m_pShadowTransformCB.GetAddressOf());


		setViewMatrix(LightManager::getInstance().getNormalizedLightDirection());
		setProjMatrix();
	}

	void ShadowMapManager::setViewMatrix(const XMFLOAT3& lightDir)
	{
		if (m_pd3dImmediateContext)
		{
			XMVECTOR dirVec = XMLoadFloat3(&lightDir);
			XMMATRIX LightView = XMMatrixLookAtLH(dirVec * 20.0f * (-2.0f), g_XMZero, g_XMIdentityR1);

			ViewMatrix viewMatrix;
			viewMatrix.g_view = XMMatrixTranspose(LightView);

			D3D11_MAPPED_SUBRESOURCE mappedData;
			m_pd3dImmediateContext->Map(m_pViewMatrixCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
			memcpy_s(mappedData.pData, sizeof(ViewMatrix), &viewMatrix, sizeof(ViewMatrix));
			m_pd3dImmediateContext->Unmap(m_pViewMatrixCB.Get(), 0);



			static XMMATRIX T(
				0.5f, 0.0f, 0.0f, 0.0f,
				0.0f, -0.5f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.5f, 0.5f, 0.0f, 1.0f);
			ShadowTransform shadowTransform;
			shadowTransform.g_ShadowTransform = XMMatrixTranspose(LightView * XMMatrixOrthographicLH(40.0f, 40.0f, 20.0f, 60.0f) * T);
			m_pd3dImmediateContext->Map(m_pShadowTransformCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
			memcpy_s(mappedData.pData, sizeof(ShadowTransform), &shadowTransform, sizeof(ShadowTransform));
			m_pd3dImmediateContext->Unmap(m_pShadowTransformCB.Get(), 0);
		}

	}

	void ShadowMapManager::setProjMatrix()
	{
		ProjMatrix projMatrix;
		projMatrix.g_orthographiProj = XMMatrixTranspose(XMMatrixOrthographicLH(40.0f, 40.0f, 20.0f, 60.0f));

		D3D11_MAPPED_SUBRESOURCE mappedData;
		m_pd3dImmediateContext->Map(m_pProjMatrixCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
		memcpy_s(mappedData.pData, sizeof(ProjMatrix), &projMatrix, sizeof(ProjMatrix));
		m_pd3dImmediateContext->Unmap(m_pProjMatrixCB.Get(), 0);
	}


}


