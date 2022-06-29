#include "Geometry.h"

Mesh Geometry::buildTriangleMesh()
{
	Mesh triangleMesh;
	VertexPosNormalTex vertexPosNormalTex;

	vertexPosNormalTex.position = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	triangleMesh.vertexBuffer.push_back(vertexPosNormalTex);

	vertexPosNormalTex.position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	triangleMesh.vertexBuffer.push_back(vertexPosNormalTex);

	vertexPosNormalTex.position = XMFLOAT3(1.0f, 0.0f, 0.0f);
	triangleMesh.vertexBuffer.push_back(vertexPosNormalTex);

	triangleMesh.indexBuffer.push_back(0);
	triangleMesh.indexBuffer.push_back(1);
	triangleMesh.indexBuffer.push_back(2);

	return triangleMesh;
}