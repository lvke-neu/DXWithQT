#include "GameObject.h"
#include "d3dUtil.h"
#include "RenderStates.h"




GameObject::GameObject(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext) :
	m_pd3dDevice(pd3dDevice), m_pd3dImmediateContext(pd3dImmediateContext)
{
	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.ByteWidth = sizeof(WorldMatrix);
	m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pWorldMatrixCB.GetAddressOf());


	cbd.ByteWidth = sizeof(Material);
	m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pMaterialCB.GetAddressOf());
}

GameObject::~GameObject() 
{
	m_pWorldMatrixCB.Reset();
	m_pVertexBuffer.Reset();
	m_pIndexBuffer.Reset();
	m_pVertexShader.Reset();
	m_pPixelShader.Reset();
	m_pVertexLayout.Reset();
	m_pTexture.Reset();
	m_pTexture2.Reset();
	m_pMaterialCB.Reset();
	m_pNormalMapTexture.Reset();
}

Mesh GameObject::getMesh() 
{
	return m_mesh; 
}

void GameObject::setMesh(Mesh mesh) 
{ 

	m_pVertexBuffer.Reset();
	m_pIndexBuffer.Reset();

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


	//set boundingbox
	BoundingBox aabb;
	BoundingBox::CreateFromPoints(aabb, XMLoadFloat3(&m_mesh.vMin), XMLoadFloat3(&m_mesh.vMax));
	setBoundingBox(aabb);
}



void GameObject::setMesh2(Mesh2 mesh2)
{

	m_pVertexBuffer.Reset();
	m_pIndexBuffer.Reset();

	m_mesh2 = mesh2;

	// VertexBuffer
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = (UINT)m_mesh2.vertexBuffer.size() * sizeof(VertexPosNormalTangentTex);
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = m_mesh2.vertexBuffer.data();
	m_pd3dDevice->CreateBuffer(&vbd, &InitData, m_pVertexBuffer.GetAddressOf());


	//IndexBuffer
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = m_mesh2.indexBuffer.size() * sizeof(DWORD);
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	InitData.pSysMem = m_mesh2.indexBuffer.data();
	m_pd3dDevice->CreateBuffer(&ibd, &InitData, m_pIndexBuffer.GetAddressOf());



}

std::vector<std::wstring> GameObject::getShader()
{ 
	return m_shader; 
}

void GameObject::setShader(std::vector<std::wstring> shader, D3D11_INPUT_ELEMENT_DESC* inputLayout, UINT NumElements)
{
	m_pVertexLayout.Reset();
	m_pPixelShader.Reset();

	m_shader = shader; 

	ComPtr<ID3DBlob> blob;

	std::wstring vsHlsl, vsCso, psHlsl, psCso;
	vsHlsl = shader[0];
	psHlsl = shader[1];
	processShader(vsCso, psCso, vsHlsl, psHlsl);

	CreateShaderFromFile(vsCso.c_str(), vsHlsl.c_str(), "VS", "vs_5_0", blob.ReleaseAndGetAddressOf());
	m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf());

	m_pd3dDevice->CreateInputLayout(inputLayout, NumElements,
		blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout.GetAddressOf());

	CreateShaderFromFile(psCso.c_str(), psHlsl.c_str(), "PS", "ps_5_0", blob.ReleaseAndGetAddressOf());
	m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pPixelShader.GetAddressOf());
}


std::wstring GameObject::getTexture()
{ 
	return m_texture;
}

void GameObject::setTexture(const std::wstring& texture)
{ 
	m_pTexture.Reset();
	m_pTexture2.Reset();

	m_texture = texture; 

	if (m_texture.substr(m_texture.size() - 3) == L"dds")
	{
		CreateDDSTextureFromFile(m_pd3dDevice.Get(), m_texture.c_str(), nullptr, m_pTexture.GetAddressOf());
		CreateDDSTextureFromFile(m_pd3dDevice.Get(), L"Texture\\flarealpha.dds", nullptr, m_pTexture2.GetAddressOf());
	}
	else
	{
		CreateWICTextureFromFile(m_pd3dDevice.Get(), m_texture.c_str(), nullptr, m_pTexture.GetAddressOf());
	}


}


void GameObject::setNormalTexture(const std::wstring& texture)
{
	m_pNormalMapTexture.Reset();

	if (texture.substr(texture.size() - 3) == L"dds")
	{
		CreateDDSTextureFromFile(m_pd3dDevice.Get(), texture.c_str(), nullptr, m_pNormalMapTexture.GetAddressOf());
	}
	else
	{
		CreateWICTextureFromFile(m_pd3dDevice.Get(), texture.c_str(), nullptr, m_pNormalMapTexture.GetAddressOf());
	}
}

Material GameObject::getMaterial() 
{ 
	return m_material; 
}

void GameObject::setMaterial(Material material) 
{ 
	m_material = material; 

	D3D11_MAPPED_SUBRESOURCE mappedData;
	m_pd3dImmediateContext->Map(m_pMaterialCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
	memcpy_s(mappedData.pData, sizeof(Material), &m_material, sizeof(Material));
	m_pd3dImmediateContext->Unmap(m_pMaterialCB.Get(), 0);
}

Transform GameObject::getTransform() 
{
	changeWorldMatrixCB();
	return m_transform;
}

void GameObject::setTransform(Transform transform) 
{
	m_transform = transform; 

	changeWorldMatrixCB();
	
}

XMMATRIX XM_CALLCONV InverseTranspose(DirectX::FXMMATRIX M)
{
	using namespace DirectX;

	XMMATRIX A = M;
	A.r[3] = g_XMIdentityR3;

	return XMMatrixTranspose(XMMatrixInverse(nullptr, A));
}


void GameObject::changeWorldMatrixCB()
{
	WorldMatrix worldMatrix;
	worldMatrix.g_world = XMMatrixTranspose(m_transform.getWorldMatrix());
	worldMatrix.g_worldInvTranspose = XMMatrixTranspose(InverseTranspose(m_transform.getWorldMatrix()));


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
	
	//设置贴图资源
	m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pTexture.GetAddressOf());
	m_pd3dImmediateContext->PSSetShaderResources(1, 1, m_pNormalMapTexture.GetAddressOf());
	m_pd3dImmediateContext->PSSetShaderResources(2, 1, m_pTexture2.GetAddressOf());
	m_pd3dImmediateContext->PSSetShaderResources(3, 1, m_pReflectTexture.GetAddressOf());

	//设置采样方式
	m_pd3dImmediateContext->PSSetSamplers(0, 1, RenderStates::SSLinearWrap.GetAddressOf());

	m_pd3dImmediateContext->VSSetConstantBuffers(0, 1, m_pWorldMatrixCB.GetAddressOf());
	m_pd3dImmediateContext->PSSetConstantBuffers(3, 1, m_pMaterialCB.GetAddressOf());

	m_pd3dImmediateContext->DrawIndexed(m_mesh.indexBuffer.size(), 0, 0);
}

void GameObject::draw2()
{
	UINT stride = sizeof(VertexPosNormalTangentTex);
	UINT offset = 0;
	m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
	m_pd3dImmediateContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());
	m_pd3dImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
	m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);

	//设置贴图资源
	m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pTexture.GetAddressOf());
	m_pd3dImmediateContext->PSSetShaderResources(1, 1, m_pNormalMapTexture.GetAddressOf());
	m_pd3dImmediateContext->PSSetShaderResources(2, 1, m_pTexture2.GetAddressOf());
	m_pd3dImmediateContext->PSSetShaderResources(3, 1, m_pReflectTexture.GetAddressOf());

	//设置采样方式
	m_pd3dImmediateContext->PSSetSamplers(0, 1, RenderStates::SSLinearWrap.GetAddressOf());

	m_pd3dImmediateContext->VSSetConstantBuffers(0, 1, m_pWorldMatrixCB.GetAddressOf());
	m_pd3dImmediateContext->PSSetConstantBuffers(3, 1, m_pMaterialCB.GetAddressOf());

	m_pd3dImmediateContext->DrawIndexed(m_mesh2.indexBuffer.size(), 0, 0);
}


void GameObject::draw(UINT IndexCount, UINT StartIndexLocation)
{
	UINT stride = sizeof(VertexPosNormalTex);
	UINT offset = 0;
	m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
	m_pd3dImmediateContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());
	m_pd3dImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
	m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);

	//设置贴图资源
	//m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pTexture.GetAddressOf());
	//m_pd3dImmediateContext->PSSetShaderResources(2, 1, m_pTexture2.GetAddressOf());

	//设置采样方式
	m_pd3dImmediateContext->PSSetSamplers(0, 1, RenderStates::SSLinearWrap.GetAddressOf());

	m_pd3dImmediateContext->VSSetConstantBuffers(0, 1, m_pWorldMatrixCB.GetAddressOf());
	m_pd3dImmediateContext->PSSetConstantBuffers(3, 1, m_pMaterialCB.GetAddressOf());

	m_pd3dImmediateContext->DrawIndexed(IndexCount, StartIndexLocation, 0);
}

void GameObject::draw2d()
{
	UINT stride = sizeof(VertexPosNormalTex);
	UINT offset = 0;
	m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
	m_pd3dImmediateContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());
	m_pd3dImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
	m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);

	//设置采样方式
	m_pd3dImmediateContext->PSSetSamplers(0, 1, RenderStates::SSLinearWrap.GetAddressOf());

	m_pd3dImmediateContext->DrawIndexed(m_mesh.indexBuffer.size(), 0, 0);
}

void GameObject::processShader(std::wstring& vsCso, std::wstring& psCso, std::wstring vsHlsl, std::wstring psHlsl)
{
	auto iter = vsHlsl.find(L"hlsl");
	vsCso = vsHlsl.replace(iter, 4, L"cso");
	iter = psHlsl.find(L"hlsl");
	psCso = psHlsl.replace(iter, 4, L"cso");
}