/************************************************************************
Author: lvke
Date:2022/8/7 22:41
Description:
模型物体（通过读取模型文件生成），继承自GameObject
************************************************************************/

#pragma once 
#include "GameObject.h"
#include "ObjReader.h"

class ModelObject : public GameObject
{
public:
	ModelObject() = default;
	ModelObject(wchar_t * mboFileName, wchar_t * objFileName, ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);

	void builMesh();
	void buildTexture();
	void buildMaterial();


public:


	void setScale(float x, float y, float z)
	{
		GameObject::setScale(x, y, z);
		objReader.ReadObj(m_objFileName);
		builMesh();
	}


	void setRotation(float x, float y, float z)
	{
		GameObject::setRotation(x, y, z);
		objReader.ReadObj(m_objFileName);
		builMesh();
	}

	
	void setPosition(float x, float y, float z)
	{
		GameObject::setPosition(x, y, z);
		objReader.ReadObj(m_objFileName);
		builMesh();
	
	}
	void setPosition(const XMFLOAT3& pos)
	{
		GameObject::setPosition(pos);
		objReader.ReadObj(m_objFileName);
		builMesh();
	}

	void setTransform(Transform transform)
	{
		GameObject::setTransform(transform);
		objReader.ReadObj(m_objFileName);
		builMesh();
	}

private:
	wchar_t * m_mboFileName;
	wchar_t * m_objFileName;
private:
	ObjReader objReader;
};