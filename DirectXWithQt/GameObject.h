/************************************************************************
Author: lvke
Date:2022/6/28 23:15
Description:
GameObject类，设置/获取GO的属性
************************************************************************/

#pragma once

#include <wrl/client.h>
#include "Transform.h"
#include "Geometry.h"
#include "Light_Material.h"


template <class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;
class GameObject
{

public:
	GameObject() = default;
	GameObject(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext):
		m_pd3dDevice(pd3dDevice), m_pd3dImmediateContext(pd3dImmediateContext)
	{

	}
	virtual ~GameObject() = default;
public:
	Mesh& getMesh();
	void setMesh(Mesh mesh);

	uint32_t& getShader();
	void setShader(const uint32_t& shader);

	const wchar_t* getTexturePath();
	void setTexturePath(const wchar_t* texturePath);

	Material& getMaterial();
	void setMaterial(Material material);

	Transform& getTransform();
	void setTransform(Transform transform);

	void draw();


private:
	ComPtr<ID3D11Device> m_pd3dDevice;
	ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext;
private:
	ComPtr<ID3D11Buffer> m_pVertexBuffer{ nullptr };
	ComPtr<ID3D11Buffer> m_pIndexBuffer{ nullptr };

	ComPtr<ID3D11VertexShader> m_pVertexShader{ nullptr };
	ComPtr<ID3D11PixelShader> m_pPixelShader{ nullptr };
	ComPtr<ID3D11InputLayout> m_pVertexLayout{ nullptr };

	ComPtr<ID3D11ShaderResourceView> m_pTexture{ nullptr };
private:
	Mesh m_mesh;
	uint32_t m_shader = -1;
	const wchar_t* m_texturePath = L"\0";
	Material m_material{};
	Transform m_transform{};

public:
	static std::vector<std::vector<const wchar_t*>> shaderPath;

};