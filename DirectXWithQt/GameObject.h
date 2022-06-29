/************************************************************************
Author: lvke
Date:2022/6/28 23:15
Description:
GameObject类，设置/获取GO的属性
************************************************************************/

#pragma once

#include "Transform.h"
#include "Geometry.h"
#include "Light_Material.h"


class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;
public:
	Mesh& getMesh() { return m_mesh; }
	void setMesh(Mesh mesh) { m_mesh = mesh; }
	const wchar_t* getShader() { return m_shaderPath; }
	void setShader(const wchar_t* shaderPath) { m_shaderPath = shaderPath; }
	const wchar_t* getTexturer() { return m_texturePath; }
	void setTexture(const wchar_t* texturePath) { m_texturePath = texturePath; }
	Material& getMaterial() { return m_material; }
	void setMaterial(Material material) { m_material = material; }
	Transform& getTransform() { return m_transform; }
	void setTransform(Transform transform) { m_transform = transform; }

private:
	Mesh m_mesh;
	const wchar_t*  m_shaderPath;
	const wchar_t* m_texturePath;
	Material m_material;
	Transform m_transform;

};