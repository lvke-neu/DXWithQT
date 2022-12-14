#include "VertexType.h"

namespace Twinkle
{
	class Geometry
	{
	public:
		template<class VertexType, class IndexType>
		static void CreateCube(std::vector<VertexType>& vertices, std::vector<IndexType>& indices);

		template<class VertexType, class IndexType>
		static void CreateCylinder(std::vector<VertexType>& vertices, std::vector<IndexType>& indices);

		template<class VertexType, class IndexType>
		static void CreatePlane(std::vector<VertexType>& vertices, std::vector<IndexType>& indices, float width, float depth, float texU, float texV);

	};

	template<class VertexType, class IndexType>
	void Geometry::CreateCube(std::vector<VertexType>& vertices, std::vector<IndexType>& indices)
	{
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

		std::vector<IndexType> indicesTmp{
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4,
		8, 9, 10, 10, 11, 8,
		12, 13, 14, 14, 15, 12,
		16, 17, 18, 18, 19, 16,
		20, 21, 22, 22, 23, 20
		};
		indices = indicesTmp;
	}

	template<class VertexType, class IndexType>
	void Geometry::CreateCylinder(std::vector<VertexType>& vertices, std::vector<IndexType>& indices)
	{
		const uint32_t c_radiusSegments = 20;
		const UINT vertexCount = (c_radiusSegments + 1) * 2 + (c_radiusSegments + 2) * 2;
		vertices.resize(vertexCount);

		for (uint16_t i = 0; i < 2; i++)
		{
			uint16_t posStart = 0;
			if (i == 0)
			{
				posStart = 2 * (c_radiusSegments + 1);
				vertices[posStart].normal = XMFLOAT3(0, -1, 0);
			}
			else
			{
				posStart = 2 * (c_radiusSegments + 1) + (c_radiusSegments + 2);
				vertices[posStart].normal = XMFLOAT3(0, 1, 0);
			}
			float y = i;
			vertices[posStart].position = XMFLOAT3(0, y, 0);
			vertices[posStart].texcoord = XMFLOAT2(0.5, (float)i);


			float dTheta = static_cast<float>(2.0f * XM_PI / c_radiusSegments);
			for (UINT j = 0; j <= c_radiusSegments; ++j)
			{
				float c = cosf(j*dTheta);
				float s = sinf(j*dTheta);
				float r = 0.5;

				vertices[posStart + 1 + j].position = XMFLOAT3(r*c, y, r*s);
				vertices[posStart + 1 + j].normal = vertices[posStart].normal;
				vertices[posStart + 1 + j].texcoord = vertices[posStart].texcoord;

				vertices[i*(c_radiusSegments + 1) + j].position = XMFLOAT3(r*c, y, r*s);
				vertices[i*(c_radiusSegments + 1) + j].normal = XMFLOAT3(c, 0, s);
				vertices[i*(c_radiusSegments + 1) + j].texcoord = XMFLOAT2((float)j / c_radiusSegments, 1.0f - (float)i);
			}
		}


		const uint16_t c_indexCount = c_radiusSegments * 2 * 2 * 3;
		indices.resize(c_indexCount);
		for (uint16_t j = 0; j < c_radiusSegments; ++j)
		{
			//侧面
			indices[0 + 12 * j] = j;
			indices[1 + 12 * j] = c_radiusSegments + j + 1;
			indices[2 + 12 * j] = c_radiusSegments + j + 2;
			indices[3 + 12 * j] = j;
			indices[4 + 12 * j] = c_radiusSegments + j + 2;
			indices[5 + 12 * j] = 1 + j;

			indices[6 + 12 * j] = 2 * (c_radiusSegments + 1);
			indices[7 + 12 * j] = indices[6 + 12 * j] + 1 + j;
			indices[8 + 12 * j] = 1 + indices[7 + 12 * j];
			indices[9 + 12 * j] = 2 * (c_radiusSegments + 1) + (c_radiusSegments + 2);
			indices[10 + 12 * j] = indices[9 + 12 * j] + 2 + j;
			indices[11 + 12 * j] = indices[10 + 12 * j] - 1;
		}
	}

	template<class VertexType, class IndexType>
	void Geometry::CreatePlane(std::vector<VertexType>& vertices, std::vector<IndexType>& indices, float width, float depth, float texU, float texV)
	{
		vertices.resize(4);
		vertices[0].position = XMFLOAT3(-width / 2, 0.0f, -depth / 2);
		vertices[0].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertices[0].texcoord = XMFLOAT2(0.0f, texV);

		vertices[1].position = XMFLOAT3(-width / 2, 0.0f, depth / 2);
		vertices[1].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertices[1].texcoord = XMFLOAT2(0.0f, 0.0f);

		vertices[2].position = XMFLOAT3(width / 2, 0.0f, depth / 2);
		vertices[2].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertices[2].texcoord = XMFLOAT2(texU, 0.0f);

		vertices[3].position = XMFLOAT3(width / 2, 0.0f, -depth / 2);
		vertices[3].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertices[3].texcoord = XMFLOAT2(texU, texV);

		std::vector<IndexType> indicesTmp{0, 1, 2, 2, 3, 0};
		indices = indicesTmp;
	}
	
}