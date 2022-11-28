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
#include <map>
#include <string>

using namespace DirectX;
namespace LkEngine
{
	class IComponent;
	class PlaneComponent;

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
		void changeOrthographicProjMat(float viewWidth, float viewHeight, float nearZ, float farZ, float lightDiscoefficient);
		void enableShadowRange(bool flag) { m_enableShadowRange = flag; }
		void buildAndApplyShadowMap(PlaneComponent* planeComponent, const std::map<std::string, IComponent*>& componets);
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
	private:
		float m_viewWidth = 400.0f;
		float m_viewHeight = 400.0f;
		float m_nearZ = 20.0f;
		float m_farZ = 6000.0f;
		float m_lightDiscoefficient = 200.0f;

		bool m_enableShadowRange = false;
	};
}