#include "PlayerGameObject.h"
#include "../Component/TransformComponent.h"
#include "../Component/MeshComponent.h"
#include "Runtime/Utility/Utility.h"
#include "Runtime/Platform/Windows/Math/Geometry.h"

namespace Twinkle
{
	PlayerGameObject::PlayerGameObject()
	{
		m_transformComponent = new TransformComponent;
		m_meshComponent = new MeshComponent;

		std::vector<VertexPosNormalTex> vertices;
		std::vector<UINT32> indices;
		Geometry::CreateCube<VertexPosNormalTex, UINT32>(vertices, indices);
		dynamic_cast<MeshComponent*>(m_meshComponent)->setMesh<VertexPosNormalTex, UINT32>(vertices, indices, DXGI_FORMAT_R32_UINT);
		dynamic_cast<MeshComponent*>(m_meshComponent)->setVsShader("\\builtin\\BinShader\\BasicVertexShader.cso");
		dynamic_cast<MeshComponent*>(m_meshComponent)->setInputLayout("\\builtin\\BinShader\\BasicVertexShader.cso", VertexPosNormalTex::ied);
		dynamic_cast<MeshComponent*>(m_meshComponent)->setPsShader("\\builtin\\BinShader\\BasicPixelShader.cso");
		dynamic_cast<MeshComponent*>(m_meshComponent)->setTexture("\\builtin\\Texture\\WoodCrate.dds");
		dynamic_cast<MeshComponent*>(m_meshComponent)->setSamplerState(SamplerStateType::SSLinearWrap);
	}

	PlayerGameObject::~PlayerGameObject()
	{
		SAFE_DELETE_SETNULL(m_transformComponent);
		SAFE_DELETE_SETNULL(m_meshComponent);
	}

	void PlayerGameObject::tick(float deltaTime)
	{
		static float sum = 0.0f;
		sum += deltaTime * 5;
		

		if (std::sin(sum) <= 0)
		{
			dynamic_cast<MeshComponent*>(m_meshComponent)->setTexture("\\builtin\\Texture\\WoodCrate.dds");
		}
		else
		{
			dynamic_cast<MeshComponent*>(m_meshComponent)->setTexture("\\builtin\\Texture\\grass.dds");
		}

		m_transformComponent->tick(deltaTime);
		m_meshComponent->tick(deltaTime);
	}
}