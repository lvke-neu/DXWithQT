#include "Geometry.h"



D3D11_INPUT_ELEMENT_DESC  VertexPosNormalTex::inputLayout[3] =
{
	{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	{ "NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
	{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0 }
};

Mesh Geometry::buildTriangleMesh()
{
	Mesh triangleMesh;

	triangleMesh.vertexBuffer.resize(3);

	triangleMesh.vertexBuffer[0].position = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	triangleMesh.vertexBuffer[1].position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	triangleMesh.vertexBuffer[2].position = XMFLOAT3(1.0f, 0.0f, 0.0f);

	triangleMesh.indexBuffer.resize(3);

	triangleMesh.indexBuffer[0] = 0;
	triangleMesh.indexBuffer[1] = 1;
	triangleMesh.indexBuffer[2] = 2;
	

	return triangleMesh;
}

Mesh Geometry::builRectangleMesh()
{
	Mesh rectangleMesh;

	rectangleMesh.vertexBuffer.resize(4);

	rectangleMesh.vertexBuffer[0].position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
	rectangleMesh.vertexBuffer[1].position = XMFLOAT3(1.0f, 1.0f, 0.0f);
	rectangleMesh.vertexBuffer[2].position = XMFLOAT3(1.0f, -1.0f, 0.0f);
	rectangleMesh.vertexBuffer[3].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);

	rectangleMesh.indexBuffer.resize(6);

	rectangleMesh.indexBuffer[0] = 0;
	rectangleMesh.indexBuffer[1] = 1;
	rectangleMesh.indexBuffer[2] = 3;
	rectangleMesh.indexBuffer[3] = 3;
	rectangleMesh.indexBuffer[4] = 1;
	rectangleMesh.indexBuffer[5] = 2;

	rectangleMesh.vMin = XMFLOAT3(-1.0f, -1.0f, 0.0f);
	rectangleMesh.vMax = XMFLOAT3(1.0f, 1.0f, 0.0f);

	return rectangleMesh;
}


Mesh Geometry::buildBoxMesh()
{
	Mesh boxMesh;

	boxMesh.vertexBuffer.resize(24);

	boxMesh.vertexBuffer[0].position = XMFLOAT3(1, -1, -1);
	boxMesh.vertexBuffer[1].position = XMFLOAT3(1, 1, -1);
	boxMesh.vertexBuffer[2].position = XMFLOAT3(1, 1, 1);
	boxMesh.vertexBuffer[3].position = XMFLOAT3(1, -1, 1);
  
	boxMesh.vertexBuffer[4].position = XMFLOAT3(-1, -1, 1);
	boxMesh.vertexBuffer[5].position = XMFLOAT3(-1, 1, 1);
	boxMesh.vertexBuffer[6].position = XMFLOAT3(-1, 1, -1);
	boxMesh.vertexBuffer[7].position = XMFLOAT3(-1, -1, -1);
  
	boxMesh.vertexBuffer[8].position = XMFLOAT3(-1, 1, -1);
	boxMesh.vertexBuffer[9].position = XMFLOAT3(-1, 1, 1);
	boxMesh.vertexBuffer[10].position = XMFLOAT3(1, 1, 1);
	boxMesh.vertexBuffer[11].position = XMFLOAT3(1, 1, -1);

	boxMesh.vertexBuffer[12].position = XMFLOAT3(1, -1, -1);
	boxMesh.vertexBuffer[13].position = XMFLOAT3(1, -1, 1);
	boxMesh.vertexBuffer[14].position = XMFLOAT3(-1, -1, 1);
	boxMesh.vertexBuffer[15].position = XMFLOAT3(-1, -1, -1);
	   
	boxMesh.vertexBuffer[16].position = XMFLOAT3(1, -1, 1);
	boxMesh.vertexBuffer[17].position = XMFLOAT3(1, 1, 1);
	boxMesh.vertexBuffer[18].position = XMFLOAT3(-1, 1, 1);
	boxMesh.vertexBuffer[19].position = XMFLOAT3(-1, -1, 1);
  
	boxMesh.vertexBuffer[20].position = XMFLOAT3(-1, -1, -1);
	boxMesh.vertexBuffer[21].position = XMFLOAT3(-1, 1, -1);
	boxMesh.vertexBuffer[22].position = XMFLOAT3(1, 1, -1);
	boxMesh.vertexBuffer[23].position = XMFLOAT3(1, -1, -1);

	for (UINT i = 0; i < 4; ++i)
	{
		boxMesh.vertexBuffer[i].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);

		boxMesh.vertexBuffer[i + 4].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);

		boxMesh.vertexBuffer[i + 8].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

		boxMesh.vertexBuffer[i + 12].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);

		boxMesh.vertexBuffer[i + 16].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);

		boxMesh.vertexBuffer[i + 20].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	}

	for (UINT i = 0; i < 6; ++i)
	{
		boxMesh.vertexBuffer[i * 4].texcoord = XMFLOAT2(0.0f, 1.0f);
		boxMesh.vertexBuffer[i * 4 + 1].texcoord = XMFLOAT2(0.0f, 0.0f);
		boxMesh.vertexBuffer[i * 4 + 2].texcoord = XMFLOAT2(1.0f, 0.0f);
		boxMesh.vertexBuffer[i * 4 + 3].texcoord = XMFLOAT2(1.0f, 1.0f);
	}

	boxMesh.indexBuffer = 
	{
		0, 1, 2, 2, 3, 0,		
		4, 5, 6, 6, 7, 4,		
		8, 9, 10, 10, 11, 8,	
		12, 13, 14, 14, 15, 12,	
		16, 17, 18, 18, 19, 16, 
		20, 21, 22, 22, 23, 20	
	};

	boxMesh.vMin = XMFLOAT3(-1.0f, -1.0f, -1.0f);
	boxMesh.vMax = XMFLOAT3(1.0f, 1.0f, 1.0f);

	return boxMesh;
}

Mesh Geometry::buildPlaneMesh(float texU, float texV)
{
	Mesh planeMesh;

	planeMesh.vertexBuffer.resize(4);

	planeMesh.vertexBuffer[0].position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
	planeMesh.vertexBuffer[1].position = XMFLOAT3(1.0f, 1.0f, 0.0f);
	planeMesh.vertexBuffer[2].position = XMFLOAT3(1.0f, -1.0f, 0.0f);
	planeMesh.vertexBuffer[3].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);

	for (UINT i = 0; i < 4; ++i)
	{
		planeMesh.vertexBuffer[i].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	}

	planeMesh.vertexBuffer[0].texcoord = XMFLOAT2(0.0f, 0.0f);
	planeMesh.vertexBuffer[1].texcoord = XMFLOAT2(texU, 0.0f);
	planeMesh.vertexBuffer[2].texcoord = XMFLOAT2(texU, texV);
	planeMesh.vertexBuffer[3].texcoord = XMFLOAT2(0.0f, texV);

	planeMesh.indexBuffer =
	{
		0, 1, 3,
		1, 2, 3
	};

	return planeMesh;
}