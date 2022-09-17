/************************************************************************
Author: lvke
Date:2022/9/10 11:01
Description:
通过assimp库来读取模型文件
************************************************************************/

#pragma once 

#include "GameObject.h"
#include <assimp/Importer.hpp>      
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class AssimpModelObject
{

public:
	AssimpModelObject() = default;
	AssimpModelObject(const std::string& filePath, ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);


public:
	void setMaterial(const Material& material);
	
	void setShader(std::vector<std::wstring> shader);

	Transform getTransform();
	void setTransform(const Transform& transform);

	void setPosition(float x, float y, float z);
	void draw();

	BoundingBox getBoundingBox() { return m_boundingBox; };
	//void setBoundingBox(BoundingBox boundingBox) { m_boundingBox = boundingBox; };

private:
	void loadModel(std::string const &path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);


private:
	std::vector<GameObject> m_gameObjects;
	BoundingBox m_boundingBox;
	Transform m_transform;


	ComPtr<ID3D11Device> m_pd3dDevice;
	ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext;
};