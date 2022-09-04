#include "Geometry.h"



D3D11_INPUT_ELEMENT_DESC  VertexPosNormalTex::inputLayout[3] =
{
	{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	{ "NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
	{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0 }
};


D3D11_INPUT_ELEMENT_DESC  VertexPosNormalTangentTex::inputLayout[4] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 }
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

Mesh Geometry::buildSphereMesh(float radius, UINT levels, UINT slices)
{

	Mesh sphereMesh;

	UINT vertexCount = 2 + (levels - 1) * (slices + 1);
	UINT indexCount = 6 * (levels - 1) * slices;
	sphereMesh.vertexBuffer.resize(vertexCount);
	sphereMesh.indexBuffer.resize(indexCount);


	DWORD vIndex = 0, iIndex = 0;

	float phi = 0.0f, theta = 0.0f;
	float per_phi = XM_PI / levels;
	float per_theta = XM_2PI / slices;
	float x, y, z;

	sphereMesh.vertexBuffer[vIndex++] = VertexPosNormalTex({ XMFLOAT3(0.0f, radius, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) });



	for (UINT i = 1; i < levels; ++i)
	{
		phi = per_phi * i;

		for (UINT j = 0; j <= slices; ++j)
		{
			theta = per_theta * j;
			x = radius * sinf(phi) * cosf(theta);
			y = radius * cosf(phi);
			z = radius * sinf(phi) * sinf(theta);

			XMFLOAT3 pos = XMFLOAT3(x, y, z), normal;
			XMStoreFloat3(&normal, XMVector3Normalize(XMLoadFloat3(&pos)));

			sphereMesh.vertexBuffer[vIndex++] = VertexPosNormalTex({ pos, normal, XMFLOAT2(theta / XM_2PI, phi / XM_PI) });
		}
	}

	sphereMesh.vertexBuffer[vIndex++] = VertexPosNormalTex({ XMFLOAT3(0.0f, -radius, 0.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) });


	if (levels > 1)
	{
		for (UINT j = 1; j <= slices; ++j)
		{
			sphereMesh.indexBuffer[iIndex++] = 0;
			sphereMesh.indexBuffer[iIndex++] = j % (slices + 1) + 1;
			sphereMesh.indexBuffer[iIndex++] = j;
		}
	}


	for (UINT i = 1; i < levels - 1; ++i)
	{
		for (UINT j = 1; j <= slices; ++j)
		{
			sphereMesh.indexBuffer[iIndex++] = (i - 1) * (slices + 1) + j;
			sphereMesh.indexBuffer[iIndex++] = (i - 1) * (slices + 1) + j % (slices + 1) + 1;
			sphereMesh.indexBuffer[iIndex++] = i * (slices + 1) + j % (slices + 1) + 1;

			sphereMesh.indexBuffer[iIndex++] = i * (slices + 1) + j % (slices + 1) + 1;
			sphereMesh.indexBuffer[iIndex++] = i * (slices + 1) + j;
			sphereMesh.indexBuffer[iIndex++] = (i - 1) * (slices + 1) + j;
		}
	}


	if (levels > 1)
	{
		for (UINT j = 1; j <= slices; ++j)
		{
			sphereMesh.indexBuffer[iIndex++] = (levels - 2) * (slices + 1) + j;
			sphereMesh.indexBuffer[iIndex++] = (levels - 2) * (slices + 1) + j % (slices + 1) + 1;
			sphereMesh.indexBuffer[iIndex++] = (levels - 1) * (slices + 1) + 1;
		}
	}


	return sphereMesh;
}


Mesh Geometry::buildTerrainMesh(float width, float depth, UINT m, UINT n)
{
	UINT vertexCount = m * n;
	UINT faceCount = 2 * (m - 1) * (n - 1);

	float halfWidth = 0.5f * width;
	float halfDepth = 0.5f * depth;
	float dx = width / (n - 1);
	float dz = depth / (m - 1);
	float du = 1.0f / (n - 1);
	float dv = 1.0f / (m - 1);

	Mesh terrainMesh;

	terrainMesh.vertexBuffer.resize(vertexCount);
	for (UINT i = 0; i < m; i++)
	{
		float z = halfDepth - i * dz;
		for (UINT j = 0; j < n; j++)
		{
			float x = -halfWidth + j * dx;

			float y = 0.3f * (z * sinf(0.1f * x) + x * cosf(0.1f * z)) * 0.5;
			terrainMesh.vertexBuffer[i * n + j].position = XMFLOAT3(x, y, z);
			terrainMesh.vertexBuffer[i * n + j].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			terrainMesh.vertexBuffer[i * n + j].texcoord = XMFLOAT2(j * du, i * dv);
		}
	}

	terrainMesh.indexBuffer.resize(faceCount * 3);
	UINT k = 0;
	for (UINT i = 0; i < m - 1; ++i)
	{
		for (UINT j = 0; j < n - 1; ++j)
		{
			terrainMesh.indexBuffer[k] = i * n + j;
			terrainMesh.indexBuffer[k + 1] = i * n + j + 1;
			terrainMesh.indexBuffer[k + 2] = (i + 1) * n + j;
			terrainMesh.indexBuffer[k + 3] = (i + 1) * n + j;
			terrainMesh.indexBuffer[k + 4] = i * n + j + 1;
			terrainMesh.indexBuffer[k + 5] = (i + 1) * n + j + 1; k += 6;
		}
	}

	return terrainMesh;
}



Mesh2 Geometry2::buildPlaneMesh(float texU, float texV)
{
	Mesh2 planeMesh;

	planeMesh.vertexBuffer.resize(4);

	planeMesh.vertexBuffer[0].position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
	planeMesh.vertexBuffer[1].position = XMFLOAT3(1.0f, 1.0f, 0.0f);
	planeMesh.vertexBuffer[2].position = XMFLOAT3(1.0f, -1.0f, 0.0f);
	planeMesh.vertexBuffer[3].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);

	for (UINT i = 0; i < 4; ++i)
	{
		planeMesh.vertexBuffer[i].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	}

	planeMesh.vertexBuffer[0].tangent =	XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	planeMesh.vertexBuffer[1].tangent =	XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	planeMesh.vertexBuffer[2].tangent =	XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	planeMesh.vertexBuffer[3].tangent =	XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	

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