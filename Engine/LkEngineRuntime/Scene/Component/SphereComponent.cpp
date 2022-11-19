#include "SphereComponent.h"
#include "Common/VertexType.h"
#include "Common/RenderStates.h"
#include "../../Core/serialization/Reflection.h"


namespace LkEngine
{
	SphereComponent::SphereComponent(void** parameter) : IComponent(parameter)
	{
		setComponetType("SphereComponent");

		buildMesh();

		setVsShader("builtin\\Shader\\BasicPrimitiveVS.cso");
		setPsShader("builtin\\Shader\\BasicPrimitivePS.cso");
		setTexture("builtin\\Texture\\stone.dds");
		setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f)
		));

		setUseTexOrColor(true);
	}

	SphereComponent::SphereComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext) : IComponent(pd3dDevice, pd3dImmediateContext)
	{
		setComponetType("SphereComponent");

		buildMesh();

		setVsShader("builtin\\Shader\\BasicPrimitiveVS.cso");
		setPsShader("builtin\\Shader\\BasicPrimitivePS.cso");
		setTexture("builtin\\Texture\\stone.dds");
		setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f)
		));

		setUseTexOrColor(true);
	}

	void SphereComponent::buildMesh()
	{
		m_pVertexBuffer.Reset();
		m_pIndexBuffer.Reset();


		const float radius = 1.0f;
		const UINT levels = 20;
		const UINT slices = 20;

		const UINT vertexCount = 2 + (levels - 1) * (slices + 1);
		VertexPosNormalTex vertices[vertexCount];

		DWORD vIndex = 0, iIndex = 0;

		float phi = 0.0f, theta = 0.0f;
		float per_phi = XM_PI / levels;
		float per_theta = XM_2PI / slices;
		float x, y, z;

		vertices[vIndex++] = VertexPosNormalTex({ XMFLOAT3(0.0f, radius, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) });

		for (UINT i = 1; i < levels; ++i)
		{
			phi = per_phi * i;

			for (UINT j = 0; j <= slices; ++j)
			{
				theta = per_theta * j;
				x = radius * sinf(phi) * cosf(theta);
				y = radius * cosf(phi);
				z = radius * sinf(phi) * sinf(theta);

				XMFLOAT3 pos = XMFLOAT3(x, y, z), normal;
				XMStoreFloat3(&normal, XMVector3Normalize(XMLoadFloat3(&pos)));

				vertices[vIndex++] = VertexPosNormalTex({ pos, normal, XMFLOAT2(theta / XM_2PI, phi / XM_PI) });
			}
		}
		vertices[vIndex++] = VertexPosNormalTex({ XMFLOAT3(0.0f, -radius, 0.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) });

		DWORD indices[6 * (levels - 1) * slices];
		m_indexCount = 6 * (levels - 1) * slices;

		if (levels > 1)
		{
			for (UINT j = 1; j <= slices; ++j)
			{
				indices[iIndex++] = 0;
				indices[iIndex++] = j % (slices + 1) + 1;
				indices[iIndex++] = j;
			}
		}

		for (UINT i = 1; i < levels - 1; ++i)
		{
			for (UINT j = 1; j <= slices; ++j)
			{
				indices[iIndex++] = (i - 1) * (slices + 1) + j;
				indices[iIndex++] = (i - 1) * (slices + 1) + j % (slices + 1) + 1;
				indices[iIndex++] = i * (slices + 1) + j % (slices + 1) + 1;

				indices[iIndex++] = i * (slices + 1) + j % (slices + 1) + 1;
				indices[iIndex++] = i * (slices + 1) + j;
				indices[iIndex++] = (i - 1) * (slices + 1) + j;
			}
		}


		if (levels > 1)
		{
			for (UINT j = 1; j <= slices; ++j)
			{
				indices[iIndex++] = (levels - 2) * (slices + 1) + j;
				indices[iIndex++] = (levels - 2) * (slices + 1) + j % (slices + 1) + 1;
				indices[iIndex++] = (levels - 1) * (slices + 1) + 1;
			}
		}

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
		XMFLOAT3 vMin(-1.0f, -1.0f, -1.0f);
		XMFLOAT3 vMax(1.0f, 1.0f, 1.0f);
		BoundingBox aabb;
		BoundingBox::CreateFromPoints(aabb, XMLoadFloat3(&vMin), XMLoadFloat3(&vMax));
		setBoundingBox(aabb);
	}

	void SphereComponent::createVertexLayout(const ComPtr<ID3DBlob>& blob)
	{
		m_pd3dDevice->CreateInputLayout(VertexPosNormalTex::inputLayout, 3, blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout.GetAddressOf());
	}

	void SphereComponent::bindPipeState()
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
		m_pd3dImmediateContext->PSSetShaderResources(1, 1, m_pShadowMapTexture.GetAddressOf());
		m_pd3dImmediateContext->PSSetSamplers(1, 1, RenderStates::SSShadow.GetAddressOf());

		m_pd3dImmediateContext->VSSetConstantBuffers(3, 1, m_pWorldMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(3, 1, m_pWorldMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->VSSetConstantBuffers(4, 1, m_pMaterialCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(4, 1, m_pMaterialCB.GetAddressOf());
		m_pd3dImmediateContext->VSSetConstantBuffers(5, 1, m_pUseColorCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(5, 1, m_pUseColorCB.GetAddressOf());
	}

	void SphereComponent::draw()
	{
		bindPipeState();
		m_pd3dImmediateContext->DrawIndexed(m_indexCount, 0, 0);
	}

	void SphereComponent::drawShadowMap()
	{
		UINT stride = sizeof(VertexPosNormalTex);
		UINT offset = 0;
		m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
		m_pd3dImmediateContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pTexture.GetAddressOf());
		m_pd3dImmediateContext->PSSetSamplers(0, 1, RenderStates::SSLinearWrap.GetAddressOf());

		m_pd3dImmediateContext->VSSetConstantBuffers(3, 1, m_pWorldMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(3, 1, m_pWorldMatrixCB.GetAddressOf());

		m_pd3dImmediateContext->DrawIndexed(m_indexCount, 0, 0);
	}
}
