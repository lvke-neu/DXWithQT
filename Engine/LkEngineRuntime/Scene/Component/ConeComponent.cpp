#include "ConeComponent.h"
#include "Common/VertexType.h"
#include "Common/RenderStates.h"
#include "../../Core/serialization/Reflection.h"



namespace LkEngine
{
	template<typename V, typename V1, typename V2>
	inline void Vector3Cross(V& vOut, const V1& v1, const V2& v2)
	{
		decltype(vOut.x) x = decltype(vOut.x)(v1.y * v2.z - v1.z * v2.y);
		decltype(vOut.y) y = decltype(vOut.y)(v1.z * v2.x - v1.x * v2.z);
		vOut.z = v1.x * v2.y - v1.y * v2.x;
		vOut.x = x;
		vOut.y = y;
	}

	template<typename V, typename V1>
	inline void Vector3Normalize(V& vOut, const V1& v)
	{
		decltype(vOut.x) len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
		if (0 != len)
		{
			decltype(vOut.x) rcpLen = decltype(vOut.x)(1) / len;
			vOut.x = v.x * rcpLen;
			vOut.y = v.y * rcpLen;
			vOut.z = v.z * rcpLen;
		}
	}

	ConeComponent::ConeComponent(void** parameter) : IComponent(parameter)
	{
		setComponetType("ConeComponent");

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

	ConeComponent::ConeComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext) : IComponent(pd3dDevice, pd3dImmediateContext)
	{
		setComponetType("ConeComponent");

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

	void ConeComponent::buildMesh()
	{
		m_pVertexBuffer.Reset();
		m_pIndexBuffer.Reset();

		const uint32_t c_radiusSegments = 20;
		const UINT vertexCount = 2 * (c_radiusSegments + 1) + (c_radiusSegments + 2);
		VertexPosNormalTex vertices[vertexCount];

		float dTheta = static_cast<float>(2.0f * XM_PI / c_radiusSegments);
		for (uint16_t i = 0; i <= c_radiusSegments; i++)
		{
			float c = cosf(i*dTheta);
			float s = sinf(i*dTheta);
			float r = 0.5f;
			float h = 1.0f;

			vertices[i].position = XMFLOAT3(r*c, 0.0f, r*s);
			XMFLOAT3 normal;
			Vector3Cross(normal, XMFLOAT3(s, 0, -c), XMFLOAT3( - r * c, h, - r * s));
			Vector3Normalize(vertices[i].normal, normal);
			vertices[i].texcoord = XMFLOAT2((float)i / c_radiusSegments, 1);

			vertices[c_radiusSegments + 1 + i].position = XMFLOAT3(0.0f, 1.0f, 0.0f);
			vertices[c_radiusSegments + 1 + i].normal = vertices[i].normal;
			vertices[c_radiusSegments + 1 + i].texcoord = XMFLOAT2((float)i / c_radiusSegments, 0);

			vertices[2 * c_radiusSegments + 2 + i].position = XMFLOAT3(r*c, 0.0f, r*s);
			vertices[2 * c_radiusSegments + 2 + i].normal = XMFLOAT3(0, -1, 0);
			vertices[2 * c_radiusSegments + 2 + i].texcoord = XMFLOAT2(0.5, 1);
		}
	
		vertices[3 * c_radiusSegments + 3].position = XMFLOAT3(0, 0, 0);
		vertices[3 * c_radiusSegments + 3].normal = XMFLOAT3(0, -1, 0);
		vertices[3 * c_radiusSegments + 3].texcoord = XMFLOAT2(0.5, 1);

		const uint32_t c_indexCount = c_radiusSegments * 2 * 3;
		DWORD indices[c_indexCount];

		for (uint16_t j = 0; j < c_radiusSegments; ++j)
		{
			indices[0 + 6 * j] = j;
			indices[1 + 6 * j] = c_radiusSegments + j + 1;
			indices[2 + 6 * j] = j + 1;

			indices[3 + 6 * j] = j + 1 + 2 * c_radiusSegments + 2;
			indices[4 + 6 * j] = 3 * c_radiusSegments + 3;
			indices[5 + 6 * j] = j + 2 * c_radiusSegments + 2;
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

	void ConeComponent::createVertexLayout(const ComPtr<ID3DBlob>& blob)
	{
		m_pd3dDevice->CreateInputLayout(VertexPosNormalTex::inputLayout, 3, blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout.GetAddressOf());
	}

	void ConeComponent::bindPipeState()
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

		m_pd3dImmediateContext->VSSetConstantBuffers(2, 1, m_pWorldMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(2, 1, m_pWorldMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->VSSetConstantBuffers(3, 1, m_pMaterialCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(3, 1, m_pMaterialCB.GetAddressOf());
		m_pd3dImmediateContext->VSSetConstantBuffers(4, 1, m_pUseColorCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(4, 1, m_pUseColorCB.GetAddressOf());
	}

	void ConeComponent::draw()
	{
		bindPipeState();
		m_pd3dImmediateContext->DrawIndexed(m_indexCount, 0, 0);
	}
}
