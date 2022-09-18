#include "TestComponent.h"
#include <d3dcompiler.h>
#include "../Core/base/Utility.h"
#include "../Asset/AssetManager.h"

const D3D11_INPUT_ELEMENT_DESC TestComponent::VertexPosColor::inputLayout[2] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};



void TestComponent::initialize(Microsoft::WRL::ComPtr<ID3D11Device> pd3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
{
	m_pd3dDevice = pd3dDevice;
	m_pd3dImmediateContext = pd3dImmediateContext;

	ComPtr<ID3DBlob> blob;

	std::string inVsShaderPath("builtin\\Shader\\Triangle_VS.cso");
	std::string inPsShaderPath("builtin\\Shader\\Triangle_PS.cso");

	m_pVertexShader = AssetManager::getInstance().loadVsShaderAsset(inVsShaderPath, blob);
	m_pd3dDevice->CreateInputLayout(VertexPosColor::inputLayout, ARRAYSIZE(VertexPosColor::inputLayout),
		blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout.GetAddressOf());
	m_pPixelShader = AssetManager::getInstance().loadPsShaderAsset(inPsShaderPath);

	//blob.Reset();

	VertexPosColor vertices[] =
	{
		{ XMFLOAT3(0.0f, 0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) }
	};
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof vertices;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	m_pd3dDevice->CreateBuffer(&vbd, &InitData, m_pVertexBuffer.GetAddressOf());

	UINT stride = sizeof(VertexPosColor);
	UINT offset = 0;
	m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
	m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());
	m_pd3dImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
	m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);
}

void TestComponent::updateScene(float deltaTime)
{
}

void TestComponent::drawScene()
{
	m_pd3dImmediateContext->Draw(3, 0);
}