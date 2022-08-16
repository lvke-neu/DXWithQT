/************************************************************************
Author: lvke
Date:2022/8/13 22:22
Description:
天空盒效果
************************************************************************/

#pragma once
#include "GameObject.h"
#include <string>

template <class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

class SkyBox : public GameObject
{
public:
	SkyBox() = default;
	SkyBox(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);

	void setSkyBoxTexture(const std::wstring& cubemapFilename, bool generateMips = false);

};