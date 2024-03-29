/************************************************************************
Author: lvke
Date:2022/8/7 22:41
Description:
模型物体（通过读取模型文件生成）

修改不再继承自GameObject，而是一个模型可能包含多个GameObject
************************************************************************/

#pragma once 

#include "GameObject.h"
#include "ObjReader.h"


class ModelObject
{

public:
	ModelObject() = default;
	ModelObject(const ObjReader& objReader, ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);


public:
	void setShader(std::vector<std::wstring> shader);

	Transform getTransform();
	void setTransform(const Transform& transform);
	
	void setPosition(float x, float y, float z);
	void draw();

	BoundingBox getBoundingBox() { return m_boundingBox; };
	//void setBoundingBox(BoundingBox boundingBox) { m_boundingBox = boundingBox; };
private:
	ObjReader objReader;
	std::vector<GameObject> m_gameObjects;
	BoundingBox m_boundingBox;
	Transform m_transform;
};