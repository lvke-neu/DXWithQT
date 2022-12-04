#include "TestComponent.h"
#include "Runtime/Platform/Windows/Bindable/BindableManager.h"
#include "Runtime/Platform/Windows/Math/VertexType.h"
#include "Runtime/Platform/Windows/Math/Transform.h"

namespace Twinkle
{
	TestComponent::TestComponent()
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

		vertexBuffer = Singleton<BindableManager>::GetInstance().CreateVertexBuffer<VertexPosNormalTex>(vertices);

		//indexbuffer
		std::vector<UINT32> indices{
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4,
		8, 9, 10, 10, 11, 8,
		12, 13, 14, 14, 15, 12,
		16, 17, 18, 18, 19, 16,
		20, 21, 22, 22, 23, 20
		};
		
		indexBuffer = Singleton<BindableManager>::GetInstance().CreateIndexBuffer<UINT32>(indices, DXGI_FORMAT_R32_UINT);

		//vertexshader
		vertexShader = Singleton<BindableManager>::GetInstance().CreateVertexShader("\\builtin\\BinShader\\VertexShader.cso");
		
		//inputlayout
		inputLayout = Singleton<BindableManager>::GetInstance().CreateInputLayout("\\builtin\\BinShader\\VertexShader.cso", VertexPosNormalTex::ied);

		//pixelshader
		pixelShader = Singleton<BindableManager>::GetInstance().CreatePixelShader("\\builtin\\BinShader\\PixelShader.cso");

		//texture
		texture = Singleton<BindableManager>::GetInstance().CreateTexture(0, "\\builtin\\Texture\\WoodCrate.dds");

		//samplerstate

		samplerState = Singleton<BindableManager>::GetInstance().CreateSamplerState(0, SamplerStateType::SSLinearWrap);



		//constantbuffer
		Transform transform;
		transform.setPosition(0, 0, 5);
		WorldMatrix worldMatrix;
		worldMatrix.worldMatrix = XMMatrixTranspose(transform.getWorldMatrix());
		
		IBindable* constantBuffer = Singleton<BindableManager>::GetInstance().CreateConstantBuffer<WorldMatrix>(0);
		dynamic_cast<ConstantBuffer<WorldMatrix>*>(constantBuffer)->update(worldMatrix);
		cbs.push_back(constantBuffer);
	}

	TestComponent::~TestComponent()
	{
		Singleton<BindableManager>::GetInstance().Release(vertexBuffer);
		Singleton<BindableManager>::GetInstance().Release(indexBuffer);
		Singleton<BindableManager>::GetInstance().Release(vertexShader);
		Singleton<BindableManager>::GetInstance().Release(inputLayout);
		Singleton<BindableManager>::GetInstance().Release(pixelShader);
		Singleton<BindableManager>::GetInstance().Release(cbs);
		Singleton<BindableManager>::GetInstance().Release(texture);
		Singleton<BindableManager>::GetInstance().Release(samplerState);
	}

	void TestComponent::draw()
	{
		Singleton<BindableManager>::GetInstance().DrawCall<UINT32>(vertexBuffer, indexBuffer, vertexShader, inputLayout, pixelShader, 
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, texture, samplerState, cbs);
	}
}

