#include "PlaneComponent.h"
#include "Common/VertexType.h"
#include "Common/RenderStates.h"

namespace LkEngine
{
	PlaneComponent::PlaneComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext) :IComponent(pd3dDevice, pd3dImmediateContext) 
	{ 
		buildMesh(); 
		setVsShader("builtin\\Shader\\BasicPrimitiveVS.cso");
		setPsShader("builtin\\Shader\\BasicPrimitivePS.cso");
		setTexture("builtin\\Texture\\floor.dds");
		setTransform(Transform(
			XMFLOAT3(200.0f, 200.0f, 1.0f),
			XMFLOAT3(XM_PI / 2, 0.0f, 0.0f),
			XMFLOAT3(0.0f, -5.0f, 5.0f)
		));

		setUseTexOrColor(true);
		setMaterial(Basic_HAS_AMBIENT_MAT);
	}

	void PlaneComponent::buildMesh()
	{
		m_pVertexBuffer.Reset();
		m_pIndexBuffer.Reset();

		const UINT vertexCount = 4;
		VertexPosNormalTex vertices[vertexCount];

		vertices[0].position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
		vertices[1].position = XMFLOAT3(1.0f, 1.0f, 0.0f);
		vertices[2].position = XMFLOAT3(1.0f, -1.0f, 0.0f);
		vertices[3].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);

		for (UINT i = 0; i < 4; ++i)
		{
			vertices[i].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		}

		vertices[0].texcoord = XMFLOAT2(0.0f, 0.0f);
		vertices[1].texcoord = XMFLOAT2(0.0f, 5.0f);
		vertices[2].texcoord = XMFLOAT2(5.0f, 5.0f);
		vertices[3].texcoord = XMFLOAT2(5.0f, 0.0f);

		DWORD indices[] = {
			0, 1, 3,
			1, 2, 3
		};
		m_indexCount = 6;

		// VertexBuffer
		D3D11_BUFFER_DESC vbd;
		ZeroMemory(&vbd, sizeof(vbd));
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(vertices);
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = vertices;
		m_pd3dDevice->CreateBuffer(&vbd, &InitData, m_pVertexBuffer.GetAddressOf());


		//IndexBuffer
		D3D11_BUFFER_DESC ibd;
		ZeroMemory(&ibd, sizeof(ibd));
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = sizeof(indices);
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		InitData.pSysMem = indices;
		m_pd3dDevice->CreateBuffer(&ibd, &InitData, m_pIndexBuffer.GetAddressOf());

		//BoundingBox
		XMFLOAT3 vMin(-1.0f, 1.0f, 0.5f);
		XMFLOAT3 vMax(-1.0f, -1.0f, -0.5f);
		BoundingBox aabb;
		BoundingBox::CreateFromPoints(aabb, XMLoadFloat3(&vMin), XMLoadFloat3(&vMax));
		setBoundingBox(aabb);
	}

	void PlaneComponent::createVertexLayout(const ComPtr<ID3DBlob>& blob)
	{
		m_pd3dDevice->CreateInputLayout(VertexPosNormalTex::inputLayout, 3, blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout.GetAddressOf());
	}

	void PlaneComponent::bindPipeState()
	{
		UINT stride = sizeof(VertexPosNormalTex);
		UINT offset = 0;
		m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
		m_pd3dImmediateContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());
		m_pd3dImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
		m_pd3dImmediateContext->GSSetShader(m_pGeometryShader.Get(), nullptr, 0);
		m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);

		m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pTexture.GetAddressOf());
		m_pd3dImmediateContext->PSSetSamplers(0, 1, RenderStates::SSLinearWrap.GetAddressOf());

		m_pd3dImmediateContext->VSSetConstantBuffers(3, 1, m_pWorldMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(3, 1, m_pWorldMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->VSSetConstantBuffers(4, 1, m_pMaterialCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(4, 1, m_pMaterialCB.GetAddressOf());
		m_pd3dImmediateContext->VSSetConstantBuffers(5, 1, m_pUseColorCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(5, 1, m_pUseColorCB.GetAddressOf());

	}

	void PlaneComponent::draw()
	{
		bindPipeState();
		m_pd3dImmediateContext->DrawIndexed(m_indexCount, 0, 0);
	}
}
