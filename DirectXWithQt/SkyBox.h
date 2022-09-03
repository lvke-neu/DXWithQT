/************************************************************************
Author: lvke
Date:2022/8/21 11:21
Description:
天空盒，继承自GameObject,重写setTexture函数与draw函数
************************************************************************/

#pragma once
#include "GameObject.h"

class SkyBox : public GameObject 
{
public:
	SkyBox() = default;
	SkyBox(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	void setTexture(const std::wstring& cubemapFilename, bool generateMips = false);
	void setTexture(const std::vector<std::wstring>& cubemapFilenames, bool generateMips = false);
	void draw(Camera& camera);

	/*
		获取天空盒的贴图ShaderResourceView，给物体反射使用
		(静态天空盒)
	*/

	ComPtr<ID3D11ShaderResourceView> getSkyBoxSRV();

	/*
	获取天空盒的贴图ShaderResourceView，给物体反射使用
	(动态天空盒)
	*/

	ComPtr<ID3D11ShaderResourceView> getDynamicSkyBoxSRV();




	ComPtr<ID3D11RenderTargetView>		m_pCacheRTV;		       
	ComPtr<ID3D11DepthStencilView>		m_pCacheDSV;		       
	Camera								m_camera;				   
	ComPtr<ID3D11DepthStencilView>		m_pDynamicCubeMapDSV;		
	ComPtr<ID3D11ShaderResourceView>	m_pDynamicCubeMapSRV;		
	ComPtr<ID3D11RenderTargetView>		m_pDynamicCubeMapRTVs[6];	


	void Cache();
	void BeginCapture(const XMFLOAT3& pos, D3D11_TEXTURECUBE_FACE face, float nearZ = 1e-3f, float farZ = 1e3f);
	void Restore(Camera& camera);
};