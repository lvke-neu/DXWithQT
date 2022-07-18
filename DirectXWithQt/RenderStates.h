#pragma once

#include <d3d11.h>
#include <wrl/client.h>

/*

渲染状态分类
1、光栅化状态（ID3D11RasterizerState）--->m_pd3dImmediateContext->RSSetState();
2、采样状态（ID3D11SamplerState）--->m_pd3dImmediateContext->PSSetSamplers();
3、混合状态（ID3D11BlendState）--->m_pd3dImmediateContext->OMSetBlendState();
*/

template <class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;
class RenderStates
{
public:

	static ComPtr<ID3D11SamplerState> SSLinearWrap;
	static ComPtr<ID3D11SamplerState> SSAnisotropicWrap;

	static ComPtr<ID3D11RasterizerState> RSWireframe;	
	static ComPtr<ID3D11RasterizerState> RSNoCull;

public:
	static void Init(ComPtr<ID3D11Device> pd3dDevice);
};