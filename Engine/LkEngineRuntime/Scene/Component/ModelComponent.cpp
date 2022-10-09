#include "ModelComponent.h"
#include "Common/VertexType.h"
#include "Common/RenderStates.h"
#include "../../../LkEngineRuntime/Core/base/Utility.h"

namespace LkEngine
{
	SubModelComponent::SubModelComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext, aiMesh* mesh) : IComponent(pd3dDevice, pd3dImmediateContext)
	{
		m_mesh = mesh;

		setComponetType("SubModelComponent");

		buildMesh();

		setVsShader("builtin\\Shader\\BasicPrimitiveVS.cso");
		setPsShader("builtin\\Shader\\BasicPrimitivePS.cso");
		setTransform(Transform(
			XMFLOAT3(0.1f, 0.1f, 0.1f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f)
		));
	}

	void SubModelComponent::buildMesh()
	{
		m_pVertexBuffer.Reset();
		m_pIndexBuffer.Reset();

		int vertexCount = m_mesh->mNumVertices;
		VertexPosNormalTex* vertices = new VertexPosNormalTex[vertexCount];

		for (unsigned int i = 0; i < m_mesh->mNumVertices; i++)
		{
			vertices[i].position.x = m_mesh->mVertices[i].x;
			vertices[i].position.y = m_mesh->mVertices[i].y;
			vertices[i].position.z = m_mesh->mVertices[i].z;

			vertices[i].normal.x =	m_mesh->mNormals[i].x;
			vertices[i].normal.y =	m_mesh->mNormals[i].y;
			vertices[i].normal.z =	m_mesh->mNormals[i].z;


			if (m_mesh->mTextureCoords[0])
			{
				vertices[i].texcoord.x = m_mesh->mTextureCoords[0][i].x;
				vertices[i].texcoord.y = m_mesh->mTextureCoords[0][i].y;
			}
			else
				vertices[i].texcoord = XMFLOAT2(0.0f, 0.0f);
		}

		for (unsigned int i = 0; i < m_mesh->mNumFaces; i++)
		{
			aiFace face = m_mesh->mFaces[i];

			for (unsigned int j = 0; j < face.mNumIndices; j++)
				m_indexCount++;
		}

		DWORD* indices = new DWORD[m_indexCount];
		int index = 0;
		for (unsigned int i = 0; i < m_mesh->mNumFaces; i++)
		{
			aiFace face = m_mesh->mFaces[i];

			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices[index++] = face.mIndices[j];
		}

		// VertexBuffer
		D3D11_BUFFER_DESC vbd;
		ZeroMemory(&vbd, sizeof(vbd));
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(VertexPosNormalTex) * vertexCount;
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = vertices;
		m_pd3dDevice->CreateBuffer(&vbd, &InitData, m_pVertexBuffer.GetAddressOf());


		//IndexBuffer
		D3D11_BUFFER_DESC ibd;
		ZeroMemory(&ibd, sizeof(ibd));
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = sizeof(DWORD) * m_indexCount;
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = indices;
		m_pd3dDevice->CreateBuffer(&ibd, &InitData, m_pIndexBuffer.GetAddressOf());
	}

	void SubModelComponent::createVertexLayout(const ComPtr<ID3DBlob>& blob)
	{
		m_pd3dDevice->CreateInputLayout(VertexPosNormalTex::inputLayout, 3, blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout.GetAddressOf());
	}

	void SubModelComponent::bindPipeState()
	{
		UINT stride = sizeof(VertexPosNormalTex);
		UINT offset = 0;
		m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
		m_pd3dImmediateContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());
		m_pd3dImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
		m_pd3dImmediateContext->GSSetShader(m_pGeometryShader.Get(), nullptr, 0);
		m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);


		m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pTexture.GetAddressOf());


		m_pd3dImmediateContext->PSSetSamplers(0, 1, RenderStates::SSLinearWrap.GetAddressOf());

		m_pd3dImmediateContext->VSSetConstantBuffers(2, 1, m_pWorldMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(2, 1, m_pWorldMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->VSSetConstantBuffers(3, 1, m_pMaterialCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(3, 1, m_pMaterialCB.GetAddressOf());

	}

	void SubModelComponent::draw()
	{
		bindPipeState();
		m_pd3dImmediateContext->DrawIndexed(m_indexCount, 0, 0);
	}




	ModelComponent::ModelComponent(void** parameter)
	{
		m_pd3dDevice = (ID3D11Device*)parameter[0];
		m_pd3dImmediateContext = (ID3D11DeviceContext*)parameter[1];
		m_modelPath = *((std::string*)parameter[2]);
		setComponetType("ModelComponent");
		loadModel();

		setTransform(Transform(
			XMFLOAT3(0.1f, 0.1f, 0.1f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f)
		));

		GUID guid;
		CoCreateGuid(&guid);
		const UINT bufferLength = 256;
		char* guidStr = new char[bufferLength];
		_snprintf_s(guidStr, bufferLength, bufferLength - 1,
			"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2],
			guid.Data4[3], guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]);
		m_uuid = guidStr;
	}

	ModelComponent::ModelComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext, const std::string& modelPath)
	{
		m_pd3dDevice = pd3dDevice;
		m_pd3dImmediateContext = pd3dImmediateContext;
		m_modelPath = modelPath;
		setComponetType("ModelComponent");
		loadModel();

		setTransform(Transform(
			XMFLOAT3(0.1f, 0.1f, 0.1f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f)
		));

		GUID guid;
		CoCreateGuid(&guid);
		const UINT bufferLength = 256;
		char* guidStr = new char[bufferLength];
		_snprintf_s(guidStr, bufferLength, bufferLength - 1,
			"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2],
			guid.Data4[3], guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]);
		m_uuid = guidStr;
	}


	void ModelComponent::loadModel()
	{

		Assimp::Importer importer;

		importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT);
		const aiScene* scene = importer.ReadFile(m_modelPath,
			aiProcess_ConvertToLeftHanded |
			aiProcess_GenBoundingBoxes |
			aiProcess_Triangulate |
			aiProcess_ImproveCacheLocality |
			aiProcess_SortByPType);



		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{

			return;
		}


		processNode(scene->mRootNode, scene);
	}

	void ModelComponent::processNode(aiNode* node, const aiScene* scene)
	{

		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

			SubModelComponent subModelComponent(m_pd3dDevice, m_pd3dImmediateContext, mesh);

			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			for (unsigned int j = 0; j < material->GetTextureCount(aiTextureType_DIFFUSE); j++)
			{
				aiString str;
				material->GetTexture(aiTextureType_DIFFUSE, j, &str);
				subModelComponent.setTexture(std::string("builtin\\Model\\") + std::string(str.C_Str()));
			}


			m_subModelComponents.push_back(subModelComponent);
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}

	}

	void ModelComponent::draw()
	{
		for (auto& submodel : m_subModelComponents)
			submodel.draw();
	}
}
