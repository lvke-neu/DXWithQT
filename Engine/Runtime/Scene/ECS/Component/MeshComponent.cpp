#include "MeshComponent.h"
#include "Runtime/Platform/Windows/RenderSystem.h"
#include "Runtime/Platform/Windows/Math/VertexType.h"

namespace Twinkle
{
	MeshComponent::MeshComponent()
	{
		std::vector<VertexPosNormalTex> vertices;
		vertices.resize(24);
		vertices[0].position = XMFLOAT3(1, -1, -1);
		vertices[1].position = XMFLOAT3(1, 1, -1);
		vertices[2].position = XMFLOAT3(1, 1, 1);
		vertices[3].position = XMFLOAT3(1, -1, 1);

		vertices[4].position = XMFLOAT3(-1, -1, 1);
		vertices[5].position = XMFLOAT3(-1, 1, 1);
		vertices[6].position = XMFLOAT3(-1, 1, -1);
		vertices[7].position = XMFLOAT3(-1, -1, -1);

		vertices[8].position = XMFLOAT3(-1, 1, -1);
		vertices[9].position = XMFLOAT3(-1, 1, 1);
		vertices[10].position = XMFLOAT3(1, 1, 1);
		vertices[11].position = XMFLOAT3(1, 1, -1);

		vertices[12].position = XMFLOAT3(1, -1, -1);
		vertices[13].position = XMFLOAT3(1, -1, 1);
		vertices[14].position = XMFLOAT3(-1, -1, 1);
		vertices[15].position = XMFLOAT3(-1, -1, -1);

		vertices[16].position = XMFLOAT3(1, -1, 1);
		vertices[17].position = XMFLOAT3(1, 1, 1);
		vertices[18].position = XMFLOAT3(-1, 1, 1);
		vertices[19].position = XMFLOAT3(-1, -1, 1);

		vertices[20].position = XMFLOAT3(-1, -1, -1);
		vertices[21].position = XMFLOAT3(-1, 1, -1);
		vertices[22].position = XMFLOAT3(1, 1, -1);
		vertices[23].position = XMFLOAT3(1, -1, -1);
		for (UINT i = 0; i < 4; ++i)
		{
			vertices[i].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);

			vertices[i + 4].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);

			vertices[i + 8].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

			vertices[i + 12].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);

			vertices[i + 16].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);

			vertices[i + 20].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		}

		for (UINT i = 0; i < 6; ++i)
		{
			vertices[i * 4].texcoord = XMFLOAT2(0.0f, 1.0f);
			vertices[i * 4 + 1].texcoord = XMFLOAT2(0.0f, 0.0f);
			vertices[i * 4 + 2].texcoord = XMFLOAT2(1.0f, 0.0f);
			vertices[i * 4 + 3].texcoord = XMFLOAT2(1.0f, 1.0f);
		}

		m_vertexBuffer = Singleton<RenderSystem>::GetInstance().CreateVertexBuffer<VertexPosNormalTex>(vertices);

		//indexbuffer
		std::vector<UINT32> indices{
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4,
		8, 9, 10, 10, 11, 8,
		12, 13, 14, 14, 15, 12,
		16, 17, 18, 18, 19, 16,
		20, 21, 22, 22, 23, 20
		};

		m_indexBuffer = Singleton<RenderSystem>::GetInstance().CreateIndexBuffer<UINT32>(indices, DXGI_FORMAT_R32_UINT);

		//vertexshader
		m_vertexShader = Singleton<RenderSystem>::GetInstance().CreateVertexShader("\\builtin\\BinShader\\BasicVertexShader.cso");

		//inputlayout
		m_inputLayout = Singleton<RenderSystem>::GetInstance().CreateInputLayout("\\builtin\\BinShader\\BasicVertexShader.cso", VertexPosNormalTex::ied);

		//pixelshader
		m_pixelShader = Singleton<RenderSystem>::GetInstance().CreatePixelShader("\\builtin\\BinShader\\BasicPixelShader.cso");

		//texture
		m_texture = Singleton<RenderSystem>::GetInstance().CreateTexture(0, "\\builtin\\Texture\\WoodCrate.dds");

		//samplerstate
		m_samplerState = Singleton<RenderSystem>::GetInstance().CreateSamplerState(0, SamplerStateType::SSLinearWrap);
	}

	MeshComponent::~MeshComponent()
	{
		Singleton<RenderSystem>::GetInstance().Release(m_vertexBuffer);
		Singleton<RenderSystem>::GetInstance().Release(m_indexBuffer);
		Singleton<RenderSystem>::GetInstance().Release(m_vertexShader);
		Singleton<RenderSystem>::GetInstance().Release(m_inputLayout);
		Singleton<RenderSystem>::GetInstance().Release(m_pixelShader);
		Singleton<RenderSystem>::GetInstance().Release(m_texture);
		Singleton<RenderSystem>::GetInstance().Release(m_samplerState);
	}

	void MeshComponent::tick(float deltaTime)
	{
		Singleton<RenderSystem>::GetInstance().DrawCall<UINT32>(m_vertexBuffer, m_indexBuffer, m_vertexShader, m_inputLayout, m_pixelShader,
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, m_texture, m_samplerState);
	}
}


