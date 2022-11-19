#include "CylinderComponent.h"
#include "Common/VertexType.h"
#include "Common/RenderStates.h"
#include "../../Core/serialization/Reflection.h"



namespace LkEngine
{
	CylinderComponent::CylinderComponent(void** parameter) : IComponent(parameter)
	{
		setComponetType("CylinderComponent");

		buildMesh();

		setVsShader("builtin\\Shader\\BasicPrimitiveVS.cso");
		setPsShader("builtin\\Shader\\BasicPrimitivePS.cso");
		setTexture("builtin\\Texture\\grass.dds");
		setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f)
		));

		setUseTexOrColor(true);
	}

	CylinderComponent::CylinderComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext) : IComponent(pd3dDevice, pd3dImmediateContext)
	{
		setComponetType("CylinderComponent");

		buildMesh();

		setVsShader("builtin\\Shader\\BasicPrimitiveVS.cso");
		setPsShader("builtin\\Shader\\BasicPrimitivePS.cso");
		setTexture("builtin\\Texture\\grass.dds");
		setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f)
		));

		setUseTexOrColor(true);
	}

	void CylinderComponent::buildMesh()
	{
		m_pVertexBuffer.Reset();
		m_pIndexBuffer.Reset();

		const uint32_t c_radiusSegments = 20;
		const UINT vertexCount = (c_radiusSegments + 1) * 2 + (c_radiusSegments + 2) * 2;
		VertexPosNormalTex vertices[vertexCount];

		for (uint16_t i = 0; i < 2; i++)
		{
			uint16_t posStart = 0;
			if (i == 0)
			{
				posStart = 2 * (c_radiusSegments + 1);
				vertices[posStart].normal = XMFLOAT3(0, -1, 0);
			}
			else
			{
				posStart = 2 * (c_radiusSegments + 1) + (c_radiusSegments + 2);
				vertices[posStart].normal = XMFLOAT3(0, 1, 0);
			}
			float y = i;
			vertices[posStart].position = XMFLOAT3(0, y, 0);
			vertices[posStart].texcoord = XMFLOAT2(0.5, (float)i);

			
			float dTheta = static_cast<float>(2.0f * XM_PI / c_radiusSegments);
			for (UINT j = 0; j <= c_radiusSegments; ++j)
			{
				float c = cosf(j*dTheta);
				float s = sinf(j*dTheta);
				float r = 0.5;

				vertices[posStart + 1 + j].position = XMFLOAT3(r*c, y, r*s);
				vertices[posStart + 1 + j].normal = vertices[posStart].normal;
				vertices[posStart + 1 + j].texcoord = vertices[posStart].texcoord;

				vertices[i*(c_radiusSegments + 1) + j].position = XMFLOAT3(r*c, y, r*s);
				vertices[i*(c_radiusSegments + 1) + j].normal = XMFLOAT3(c, 0, s);
				vertices[i*(c_radiusSegments + 1) + j].texcoord = XMFLOAT2((float)j / c_radiusSegments, 1.0f - (float)i);
			}
		}


		const uint16_t c_indexCount = c_radiusSegments * 2 * 2 * 3;
		
		DWORD indices[c_indexCount]; 
		for (uint16_t j = 0; j < c_radiusSegments; ++j)
		{
			//侧面
			indices[0 + 12*j] = j;
			indices[1 + 12*j] = c_radiusSegments + j + 1;
			indices[2 + 12*j] = c_radiusSegments + j + 2;
			indices[3 + 12*j] = j;
			indices[4 + 12*j] = c_radiusSegments + j + 2;
			indices[5 + 12*j] = 1 + j;

			indices[6 + 12*j] = 2 * (c_radiusSegments + 1);
			indices[7 + 12*j] = indices[6 + 12 * j] + 1 + j;
			indices[8 + 12*j] = 1 + indices[7 + 12 * j];
			indices[9 + 12*j] = 2 * (c_radiusSegments + 1) + (c_radiusSegments + 2);
			indices[10 + 12 * j] = indices[9 + 12 * j] + 2 + j;
			indices[11 + 12 * j] = indices[10 + 12 * j] - 1;
		}
		m_indexCount = c_indexCount;

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
		XMFLOAT3 vMin(-0.5f, 0.0f, -0.5f);
		XMFLOAT3 vMax(0.5f, 1.0f, 0.5f);
		BoundingBox aabb;
		BoundingBox::CreateFromPoints(aabb, XMLoadFloat3(&vMin), XMLoadFloat3(&vMax));
		setBoundingBox(aabb);
	}

	void CylinderComponent::createVertexLayout(const ComPtr<ID3DBlob>& blob)
	{
		m_pd3dDevice->CreateInputLayout(VertexPosNormalTex::inputLayout, 3, blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout.GetAddressOf());
	}

	void CylinderComponent::bindPipeState()
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

	void CylinderComponent::draw()
	{
		bindPipeState();
		m_pd3dImmediateContext->DrawIndexed(m_indexCount, 0, 0);
	}

	void CylinderComponent::drawShadowMap()
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
