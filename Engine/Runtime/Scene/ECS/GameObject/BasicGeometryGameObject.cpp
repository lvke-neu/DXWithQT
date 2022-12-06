#include "BasicGeometryGameObject.h"
#include "../Component/TransformComponent.h"
#include "../Component/MeshComponent.h"
#include "Runtime/Utility/Utility.h"
#include "Runtime/Platform/Windows/Math/Geometry.h"
#include <cmath>

namespace Twinkle
{
	BasicGeometryGameObject::BasicGeometryGameObject(BasicGeometryType geometryType)
	{
		m_transformComponent = new TransformComponent;
		m_meshComponent = new MeshComponent;

		std::vector<VertexPosNormalTex> vertices;
		std::vector<UINT32> indices;

		switch (geometryType)
		{
		case Cube:
			Geometry::CreateCube<VertexPosNormalTex, UINT32>(vertices, indices);
			break;
		case Cylinder:
			Geometry::CreateCylinder<VertexPosNormalTex, UINT32>(vertices, indices);
		default:
			break;
		}

		dynamic_cast<MeshComponent*>(m_meshComponent)->setMesh<VertexPosNormalTex, UINT32>(vertices, indices, DXGI_FORMAT_R32_UINT);
		dynamic_cast<MeshComponent*>(m_meshComponent)->setVsShader("\\builtin\\BinShader\\BasicVertexShader.cso");
		dynamic_cast<MeshComponent*>(m_meshComponent)->setInputLayout("\\builtin\\BinShader\\BasicVertexShader.cso", VertexPosNormalTex::ied);
		dynamic_cast<MeshComponent*>(m_meshComponent)->setPsShader("\\builtin\\BinShader\\BasicPixelShader.cso");
		dynamic_cast<MeshComponent*>(m_meshComponent)->setTexture("\\builtin\\Texture\\WoodCrate.dds");
		dynamic_cast<MeshComponent*>(m_meshComponent)->setSamplerState(SamplerStateType::SSLinearWrap);
	}

	BasicGeometryGameObject::~BasicGeometryGameObject()
	{
		SAFE_DELETE_SETNULL(m_transformComponent);
		SAFE_DELETE_SETNULL(m_meshComponent);
	}

	void BasicGeometryGameObject::tick(float deltaTime)
	{
		m_transformComponent->tick(deltaTime);
		m_meshComponent->tick(deltaTime);
	}

	IComponent * BasicGeometryGameObject::getTransformComponent()
	{
		return m_transformComponent;
	}

	IComponent * BasicGeometryGameObject::getMeshComponent()
	{
		return m_meshComponent;
	}
}