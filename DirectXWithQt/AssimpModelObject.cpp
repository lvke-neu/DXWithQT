#include "AssimpModelObject.h"
#include <thread>
#include "d3dUtil.h"

AssimpModelObject::AssimpModelObject(const std::string& filePath, ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext):
	m_pd3dDevice(pd3dDevice), m_pd3dImmediateContext(pd3dImmediateContext)
{


	loadModel(filePath);

	//Mesh mesh;

	//for (auto& objPart : objReader.objParts)
	//{
	//	mesh.vertexBuffer = objPart.vertices;
	//	mesh.indexBuffer = objPart.indices16.size() != 0 ? objPart.indices16 : objPart.indices32;

	//	GameObject go(pd3dDevice, pd3dImmediateContext);

	//	go.setMesh(mesh);
	//	go.setTexture(objPart.texStrDiffuse.c_str());
	//	go.setMaterial(objPart.material);

	//	m_gameObjects.push_back(go);
	//}

	//BoundingBox::CreateFromPoints(m_boundingBox, objReader.vecMax, objReader.vecMin);

}

void AssimpModelObject::setShader(std::vector<std::wstring> shader)
{
	for (auto& go : m_gameObjects)
		go.setShader(shader);
}

Transform AssimpModelObject::getTransform()
{
	return m_transform;
}

void AssimpModelObject::setTransform(const Transform& transform)
{
	m_transform = transform;
	for (auto& go : m_gameObjects)
		go.setTransform(transform);
}

void AssimpModelObject::setPosition(float x, float y, float z)
{
	for (auto& go : m_gameObjects)
		go.setPosition(x, y, z);
}

void AssimpModelObject::draw()
{
	for (auto& go : m_gameObjects)
		go.draw();
}


void AssimpModelObject::loadModel(std::string const &path)
{
	
	Assimp::Importer importer;
	
	importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT);
	const aiScene* scene = importer.ReadFile(path,
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

void AssimpModelObject::processNode(aiNode *node, const aiScene *scene)
{

	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];


		GameObject go(m_pd3dDevice, m_pd3dImmediateContext);
		go.setMesh(processMesh(mesh, scene));

	
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		for (unsigned int j = 0; j < material->GetTextureCount(aiTextureType_DIFFUSE); j++)
		{
			aiString str;
			material->GetTexture(aiTextureType_DIFFUSE, j, &str);	

			std::string texturePath("Model\\");
			texturePath += std::string(str.C_Str());
			go.setTexture(multiByteToWideChar(texturePath));
		}


		m_gameObjects.push_back(go);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}

}

Mesh AssimpModelObject::processMesh(aiMesh *mesh, const aiScene *scene)
{

	Mesh destMesh;
	destMesh.vertexBuffer.resize(mesh->mNumVertices);

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		destMesh.vertexBuffer[i].position.x = mesh->mVertices[i].x;
		destMesh.vertexBuffer[i].position.y = mesh->mVertices[i].y;
		destMesh.vertexBuffer[i].position.z = mesh->mVertices[i].z;

		destMesh.vertexBuffer[i].normal.x = mesh->mNormals[i].x;
		destMesh.vertexBuffer[i].normal.y = mesh->mNormals[i].y;
		destMesh.vertexBuffer[i].normal.z = mesh->mNormals[i].z;
	

		if (mesh->mTextureCoords[0]) 
		{
			destMesh.vertexBuffer[i].texcoord.x = mesh->mTextureCoords[0][i].x;
			destMesh.vertexBuffer[i].texcoord.y = mesh->mTextureCoords[0][i].y;
		}
		else
			destMesh.vertexBuffer[i].texcoord = XMFLOAT2(0.0f, 0.0f);
	}



	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++)
			destMesh.indexBuffer.push_back(face.mIndices[j]);
	}


	return destMesh;



}

