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
	*/

	ComPtr<ID3D11ShaderResourceView> getSkyBoxSRV();
};