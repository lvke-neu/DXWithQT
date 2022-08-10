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
#include "Material.h"


template <class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;
class GameObject
{

	struct WorldMatrix
	{
		XMMATRIX g_world;
		XMMATRIX g_worldInvTranspose;
	};

public:
	GameObject() = default;
	GameObject(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	virtual ~GameObject() = default;

public:
	XMFLOAT3& getScale() { return m_transform.getScale(); }
	void setScale(float x, float y, float z)
	{
		m_transform.setScale(XMFLOAT3(x, y, z));
		changeWorldMatrixCB();
	}

	XMFLOAT3& getRotation() { return m_transform.getRotation(); }
	void setRotation(float x, float y, float z)
	{
		m_transform.setRotation(XMFLOAT3(x, y, z));
		changeWorldMatrixCB();
	}

	XMFLOAT3& getPosition() { return m_transform.getPosition(); }
	void setPosition(float x, float y, float z)
	{
		setPosition(XMFLOAT3(x, y, z));
	}
	void setPosition(const XMFLOAT3& pos)
	{
		m_transform.setPosition(pos);
		changeWorldMatrixCB();
	}
public:
	Mesh& getMesh();
	void setMesh(Mesh mesh);

	uint32_t& getShader();
	void setShader(const uint32_t& shader);

	const wchar_t* getTexturePath();
	void setTexturePathDDS(const wchar_t* texturePath);
	void setTexturePathWIC(const wchar_t* texturePath);

	Material& getMaterial();
	void setMaterial(Material material);

	Transform& getTransform();
	void setTransform(Transform transform);


	void draw();     
	void draw(UINT IndexCount, UINT StartIndexLocation);
	void draw2d();

	void moveZAxis(float distance) { m_transform.moveZAxis(distance); changeWorldMatrixCB(); }
	void moveXAxis(float distance) { m_transform.moveXAxis(distance); changeWorldMatrixCB(); }
	void changeWorldMatrixCB();
private:
	ComPtr<ID3D11Device> m_pd3dDevice;
	ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext;
private:

	ComPtr<ID3D11Buffer> m_pWorldMatrixCB;//常量buffer，存放世界矩阵，放在槽0

	ComPtr<ID3D11Buffer> m_pVertexBuffer{ nullptr };
	ComPtr<ID3D11Buffer> m_pIndexBuffer{ nullptr };

	ComPtr<ID3D11VertexShader> m_pVertexShader{ nullptr };
	ComPtr<ID3D11PixelShader> m_pPixelShader{ nullptr };
	ComPtr<ID3D11InputLayout> m_pVertexLayout{ nullptr };

	ComPtr<ID3D11ShaderResourceView> m_pTexture{ nullptr };
	ComPtr<ID3D11ShaderResourceView> m_pTexture2{ nullptr };

	ComPtr<ID3D11Buffer> m_pMaterialCB{ nullptr };
private:
	Mesh m_mesh;
	uint32_t m_shader = -1;
	const wchar_t* m_texturePath = L"\0";
	Material m_material{};
	Transform m_transform{};

	

public:
	static std::vector<std::vector<const wchar_t*>> shaderPath;

};