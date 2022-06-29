#pragma once

#include <wrl/client.h>
#include <d3d11.h>
#include "Geometry.h"

template <class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;
class PipeLine
{
public:
	void init(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	void create_VtxIdx_Buffer(const Mesh& mesh, ComPtr<ID3D11Buffer>& vertexBuffer, ComPtr<ID3D11Buffer> indexBuffer);
	void create_VtxIdx_Shader_InputLayout(const wchar_t* m_shaderPath, ComPtr<ID3D11VertexShader> vertexShader, ComPtr<ID3D11PixelShader> pixelShader, ComPtr<ID3D11InputLayout> vertexLayout);
private:
	ComPtr<ID3D11Device> m_pd3dDevice{nullptr};
	ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext{nullptr};


public:
	static PipeLine* getInstance() { return pipeline; }
private:
	static PipeLine* pipeline;
};