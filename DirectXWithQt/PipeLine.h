#pragma once

#include <wrl/client.h>
#include <d3d11.h>
#include "Geometry.h"
#include "GameObject.h"
#include "DDSTextureLoader.h"

template <class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;
class PipeLine
{
public:
	void init(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	void bindGoToPipeLine(GameObject go);
	virtual void bindCB2PipeLine() = 0;
public:
	ComPtr<ID3D11Device> m_pd3dDevice;
	ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext;
private:
	void create_VtxIdx_Buffer(const Mesh& mesh, ComPtr<ID3D11Buffer>& vertexBuffer, ComPtr<ID3D11Buffer>& indexBuffer);
	void create_VtxIdx_Shader_InputLayout(uint32_t shader, ComPtr<ID3D11VertexShader>& vertexShader, ComPtr<ID3D11PixelShader>& pixelShader, ComPtr<ID3D11InputLayout>& vertexLayout);
	
	std::vector<std::vector<const wchar_t*>> m_shaderPath =
	{
		{
			L"Shader\\Chapter 1\\VS.cso",
			L"Shader\\Chapter 1\\VS.hlsl",
			L"Shader\\Chapter 1\\PS.cso",
			L"Shader\\Chapter 1\\PS.hlsl"
		},
		{
			L"Shader\\Chapter 2\\VS.cso",
			L"Shader\\Chapter 2\\VS.hlsl",
			L"Shader\\Chapter 2\\PS.cso",
			L"Shader\\Chapter 2\\PS.hlsl"
		}
	};



};
