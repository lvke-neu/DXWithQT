/***************************************************************************************
Author: lvke
Date:2022/11/19 9:25
Description:
ShadowMap Manager
****************************************************************************************/
#pragma once
#include "../../Core/base/SingletonInterface.h"
#include "../../Core/base/ManagerInterface.h"
#include <DirectXMath.h>

namespace LkEngine
{
	using namespace DirectX;
	class ShadowMapManager : public ISingleton<ShadowMapManager>, public IManager
	{
		
	private:
		struct ViewMatrix
		{
			XMMATRIX g_view;
		};

		struct ProjMatrix
		{
			XMMATRIX g_orthographiProj;
		};
		
		struct ShadowTransform
		{
			XMMATRIX g_ShadowTransform;
		};
	public:
		virtual ~ShadowMapManager();
		void begin(const FLOAT backgroundColor[4]);
		void end();
		ID3D11ShaderResourceView* GetOutputTexture() { return m_pOutputTextureSRV.Get(); }
		void setViewMatrix(const XMFLOAT3& lightDir);
	private:
		virtual void init() override;
		void initResource(int texWidth, int texHeight, bool shadowMap = false, bool generateMips = false);
		void initShaderAndInputLayout();
		void initViewAndProjMatrix();
		
		void setProjMatrix();
		void bindPipeState();
	private:
		ComPtr<ID3D11ShaderResourceView>	m_pOutputTextureSRV;	
		ComPtr<ID3D11RenderTargetView>		m_pOutputTextureRTV;	
		ComPtr<ID3D11DepthStencilView>		m_pOutputTextureDSV;	
		D3D11_VIEWPORT						m_OutputViewPort = {};	

		ComPtr<ID3D11RenderTargetView>		m_pCacheRTV;		    
		ComPtr<ID3D11DepthStencilView>		m_pCacheDSV;		    
		D3D11_VIEWPORT						m_CacheViewPort = {};	

		bool								m_GenerateMips = false;	
		bool								m_ShadowMap = false;	
	private:
		ComPtr<ID3D11VertexShader> m_pVertexShader{ nullptr };
		ComPtr<ID3D11InputLayout>  m_pVertexLayout{ nullptr };
		ComPtr<ID3D11PixelShader>  m_pPixelShader{ nullptr };
		ComPtr<ID3D11Buffer> m_pViewMatrixCB{ nullptr };
		ComPtr<ID3D11Buffer> m_pProjMatrixCB{ nullptr };
		ComPtr<ID3D11Buffer> m_pShadowTransformCB{ nullptr };
	};
}