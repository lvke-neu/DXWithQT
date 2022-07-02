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
	uint32_t& getShader() { return m_shader; }
	void setShader(const uint32_t& shader) { m_shader = shader; }
	const wchar_t* getTexturePath() { return m_texturePath; }
	void setTexturePath(const wchar_t* texturePath) { m_texturePath = texturePath; }
	Material& getMaterial() { return m_material; }
	void setMaterial(Material material) { m_material = material; }
	Transform& getTransform() { return m_transform; }
	void setTransform(Transform transform) { m_transform = transform; }

private:
	Mesh m_mesh;
	uint32_t m_shader = -1;
	const wchar_t* m_texturePath = L"\0";
	Material m_material{};
	Transform m_transform{};

};