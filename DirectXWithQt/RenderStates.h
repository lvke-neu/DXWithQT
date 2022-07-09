#pragma once

#include <d3d11.h>
#include <wrl/client.h>

template <class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;
class RenderStates
{
public:
	//线性过滤
	static ComPtr<ID3D11SamplerState> SSLinearWrap;
	
	//各项异性过滤
	static ComPtr<ID3D11SamplerState> SSAnisotropicWrap;
public:
	static void Init(ComPtr<ID3D11Device> pd3dDevice);
};