/************************************************************************
Author: lvke
Date:2022/6/28 23:15
Description:
GameObject类，设置/获取GO的属性
************************************************************************/

#pragma once

#include "Transform.h"
class Mesh {};
class Shader {};
class Texture {};
class Material {};


class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;
public:
	Mesh& getMesh() { return m_mesh; }
	void setMesh(Mesh mesh) { m_mesh = mesh; }
	Shader& getShader() { return m_shader; }
	void setShader(Shader shader) { m_shader = shader; }
	Texture& getTexturer() { return m_texture; }
	void setTexture(Texture texture) { m_texture = texture; }
	Material& getMaterial() { return m_material; }
	void setMaterial(Material material) { m_material = material; }
	Transform& getTransform() { return m_transform; }
	void setTransform(Transform transform) { m_transform = transform; }

private:
	Mesh m_mesh;
	Shader m_shader;
	Texture m_texture;
	Material m_material;
	Transform m_transform;

};