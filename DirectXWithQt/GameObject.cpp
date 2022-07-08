#include "GameObject.h"
#include "d3dUtil.h"
#include "DDSTextureLoader.h"


std::vector<std::vector<const wchar_t*>> GameObject::shaderPath =
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


Mesh& GameObject::getMesh() 
{
	return m_mesh; 
}

void GameObject::setMesh(Mesh mesh) 
{ 
	m_mesh = mesh; 

	// VertexBuffer
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = (UINT)m_mesh.vertexBuffer.size() * sizeof(VertexPosNormalTex);
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = m_mesh.vertexBuffer.data();
	m_pd3dDevice->CreateBuffer(&vbd, &InitData, m_pVertexBuffer.GetAddressOf());

	//IndexBuffer
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = m_mesh.indexBuffer.size() * sizeof(DWORD);
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	InitData.pSysMem = m_mesh.indexBuffer.data();
	m_pd3dDevice->CreateBuffer(&ibd, &InitData, m_pIndexBuffer.GetAddressOf());
}

uint32_t& GameObject::getShader() 
{ 
	return m_shader; 
}

void GameObject::setShader(const uint32_t& shader) 
{ 
	m_shader = shader; 

	ComPtr<ID3DBlob> blob;

	CreateShaderFromFile(shaderPath[shader - 1][0], shaderPath[shader - 1][1], "VS", "vs_5_0", blob.ReleaseAndGetAddressOf());
	m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf());

	m_pd3dDevice->CreateInputLayout(VertexPosNormalTex::inputLayout, ARRAYSIZE(VertexPosNormalTex::inputLayout),
		blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout.GetAddressOf());

	CreateShaderFromFile(shaderPath[shader - 1][2], shaderPath[shader - 1][3], "PS", "ps_5_0", blob.ReleaseAndGetAddressOf());
	m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pPixelShader.GetAddressOf());
}

const wchar_t* GameObject::getTexturePath() 
{ 
	return m_texturePath;
}

void GameObject::setTexturePath(const wchar_t* texturePath) 
{ 
	m_texturePath = texturePath; 

	CreateDDSTextureFromFile(m_pd3dDevice.Get(), m_texturePath, nullptr, m_pTexture.GetAddressOf());
}

Material& GameObject::getMaterial() 
{ 
	return m_material; 
}

void GameObject::setMaterial(Material material) 
{ 
	m_material = material; 
}

Transform& GameObject::getTransform() 
{
	changeWorldMatrixCB();
	return m_transform;
}

void GameObject::setTransform(Transform transform) 
{
	m_transform = transform; 

	changeWorldMatrixCB();
	
}

void GameObject::changeWorldMatrixCB()
{
	WorldMatrix worldMatrix;
	worldMatrix.g_world = XMMatrixTranspose(m_transform.getWorldMatrix());


	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.ByteWidth = sizeof(worldMatrix);
	m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pWorldMatrixCB.GetAddressOf());

	D3D11_MAPPED_SUBRESOURCE mappedData;
	m_pd3dImmediateContext->Map(m_pWorldMatrixCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
	memcpy_s(mappedData.pData, sizeof(WorldMatrix), &worldMatrix, sizeof(WorldMatrix));
	m_pd3dImmediateContext->Unmap(m_pWorldMatrixCB.Get(), 0);
}

void GameObject::draw()
{
	UINT stride = sizeof(VertexPosNormalTex);
	UINT offset = 0;
	m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
	m_pd3dImmediateContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());
	m_pd3dImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
	m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);

	m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pTexture.GetAddressOf());

	m_pd3dImmediateContext->VSSetConstantBuffers(0, 1, m_pWorldMatrixCB.GetAddressOf());

	m_pd3dImmediateContext->DrawIndexed(m_mesh.indexBuffer.size(), 0, 0);
}