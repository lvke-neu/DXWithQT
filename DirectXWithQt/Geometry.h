#pragma once

#include <DirectXMath.h>
#include <vector>

using namespace DirectX;

struct VertexPosNormalTex
{
	XMFLOAT3 position;
};

struct Mesh
{
	std::vector<VertexPosNormalTex> vertexBuffer{};
	std::vector<unsigned long> indexBuffer{};
};

class Geometry
{
public:
	static Mesh buildTriangleMesh();
};