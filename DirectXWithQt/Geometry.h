#pragma once

#include <DirectXMath.h>
#include <vector>
#include <d3d11.h>
using namespace DirectX;

//暂时只支持顶点包含:位置、法线、贴图
struct VertexPosNormalTex
{
	XMFLOAT3 position;
	XMFLOAT3 normal;
	XMFLOAT2 texcoord;

	static 	D3D11_INPUT_ELEMENT_DESC inputLayout[3];
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
	static Mesh buildBoxMesh();
};