#include "PipeLine.h"
#include "d3dUtil.h"

#include "DXTrace.h"


void PipeLine::init(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
{
	m_pd3dDevice = pd3dDevice;
	m_pd3dImmediateContext = pd3dImmediateContext;
}

void PipeLine::bindGoToPipeLine(GameObject go)
{

	//*************************** vertexBuffer &  indexBuffer *******************************************
	if (go.getMesh().vertexBuffer.size() != 0 && go.getMesh().indexBuffer.size() != 0)
	{
		ComPtr<ID3D11Buffer> vertexBuffer;
		ComPtr<ID3D11Buffer> indexBuffer;


		// VertexBuffer
		D3D11_BUFFER_DESC vbd;
		ZeroMemory(&vbd, sizeof(vbd));
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = (UINT)go.getMesh().vertexBuffer.size() * sizeof(VertexPosNormalTex);
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = go.getMesh().vertexBuffer.data();
		m_pd3dDevice->CreateBuffer(&vbd, &InitData, vertexBuffer.GetAddressOf());

		//IndexBuffer
		D3D11_BUFFER_DESC ibd;
		ZeroMemory(&ibd, sizeof(ibd));
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = go.getMesh().indexBuffer.size() * sizeof(DWORD);
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		InitData.pSysMem = go.getMesh().indexBuffer.data();
		m_pd3dDevice->CreateBuffer(&ibd, &InitData, indexBuffer.GetAddressOf());



		UINT stride = sizeof(VertexPosNormalTex);
		UINT offset = 0;
		m_pd3dImmediateContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
		m_pd3dImmediateContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	//*************************** vertexShader &  pixelShader & vertexLayout ******************************
	if (go.getShader() > 0)
	{
		ComPtr<ID3D11VertexShader> vertexShader;
		ComPtr<ID3D11PixelShader> pixelShader;
		ComPtr<ID3D11InputLayout> vertexLayout;


		ComPtr<ID3DBlob> blob;
		CreateShaderFromFile(m_shaderPath[go.getShader() - 1][0], m_shaderPath[go.getShader() - 1][1], "VS", "vs_5_0", blob.ReleaseAndGetAddressOf());
		m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, vertexShader.GetAddressOf());

		m_pd3dDevice->CreateInputLayout(VertexPosNormalTex::inputLayout, ARRAYSIZE(VertexPosNormalTex::inputLayout),
			blob->GetBufferPointer(), blob->GetBufferSize(), vertexLayout.GetAddressOf());


		CreateShaderFromFile(m_shaderPath[go.getShader() - 1][2], m_shaderPath[go.getShader() - 1][3], "PS", "ps_5_0", blob.ReleaseAndGetAddressOf());
		m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, pixelShader.GetAddressOf());

		m_pd3dImmediateContext->IASetInputLayout(vertexLayout.Get());
		m_pd3dImmediateContext->VSSetShader(vertexShader.Get(), nullptr, 0);
		m_pd3dImmediateContext->PSSetShader(pixelShader.Get(), nullptr, 0);
	}

	//*************************** texture *******************************************************************
	if (go.getTexturePath()[0] != L'\0')
	{
		ComPtr<ID3D11ShaderResourceView> texture;
		CreateDDSTextureFromFile(m_pd3dDevice.Get(), go.getTexturePath(), nullptr, texture.GetAddressOf());

		m_pd3dImmediateContext->PSSetShaderResources(0, 1, texture.GetAddressOf());
	}
}


