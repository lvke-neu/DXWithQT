#include "BasicGeometryGameObject.h"
#include "Runtime/Platform/Windows/Math/Geometry.h"

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
			break;
		case Plane:
			Geometry::CreatePlane<VertexPosNormalTex, UINT32>(vertices, indices, 200.0f, 200.0f, 50.0f, 50.0f);
			break;
		default:
			break;
		}

		m_meshComponent->setMesh<VertexPosNormalTex, UINT32>(vertices, indices, DXGI_FORMAT_R32_UINT);
		m_meshComponent->setVsShader("\\builtin\\BinShader\\BasicVertexShader.cso");
		m_meshComponent->setInputLayout("\\builtin\\BinShader\\BasicVertexShader.cso", VertexPosNormalTex::ied);
		m_meshComponent->setPsShader("\\builtin\\BinShader\\BasicPixelShader.cso");
		m_meshComponent->setTexture("\\builtin\\Texture\\WoodCrate.dds");
		m_meshComponent->setSamplerState(SamplerStateType::SSLinearWrap);
	}

	void BasicGeometryGameObject::tick(float deltaTime)
	{
		m_transformComponent->tick(deltaTime);
		m_meshComponent->tick(deltaTime);
	}

	std::string BasicGeometryGameObject::getType()
	{
		return "BasicGeometryGameObject";
	}
}