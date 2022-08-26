/************************************************************************
Author: lvke
Date:2022/6/28 23:15
Description:
GameObject类，设置/获取GO的属性
************************************************************************/

#pragma once

#include <DirectXCollision.h>
#include <wrl/client.h>
#include <string>
#include "Transform.h"
#include "Geometry.h"
#include "Material.h"
#include "Camera.h"

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
	virtual ~GameObject();

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


	BoundingBox getBoundingBox() { return m_boundingBox; };
	void setBoundingBox(BoundingBox boundingBox) { m_boundingBox = boundingBox; };
public:
	Mesh getMesh();
	void setMesh(Mesh mesh);

	std::vector<std::wstring> getShader();
	void setShader(std::vector<std::wstring>);

	std::wstring getTexture();
	void setTexture(const std::wstring& texture);

	Material getMaterial();
	void setMaterial(Material material);

	Transform getTransform();
	void setTransform(Transform transform);

	void draw();     
	void draw(UINT IndexCount, UINT StartIndexLocation);
	void draw2d();


	void moveZAxis(float distance) { m_transform.moveZAxis(distance); changeWorldMatrixCB(); }
	void moveXAxis(float distance) { m_transform.moveXAxis(distance); changeWorldMatrixCB(); }
	void changeWorldMatrixCB();

	void setReflectTexture(const ComPtr<ID3D11ShaderResourceView>& pReflectTexture) { m_pReflectTexture = pReflectTexture; }
protected:
	ComPtr<ID3D11Device> m_pd3dDevice;
	ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext;
protected:

	ComPtr<ID3D11Buffer> m_pWorldMatrixCB;

	ComPtr<ID3D11Buffer> m_pVertexBuffer{ nullptr };
	ComPtr<ID3D11Buffer> m_pIndexBuffer{ nullptr };

	ComPtr<ID3D11VertexShader> m_pVertexShader{ nullptr };
	ComPtr<ID3D11PixelShader> m_pPixelShader{ nullptr };
	ComPtr<ID3D11InputLayout> m_pVertexLayout{ nullptr };

	ComPtr<ID3D11ShaderResourceView> m_pTexture{ nullptr };
	ComPtr<ID3D11ShaderResourceView> m_pTexture2{ nullptr };
	ComPtr<ID3D11ShaderResourceView> m_pReflectTexture{ nullptr };

	ComPtr<ID3D11Buffer> m_pMaterialCB{ nullptr };


protected:
	Mesh m_mesh;
	std::vector<std::wstring> m_shader;
	std::wstring m_texture;
	Material m_material{};
	Transform m_transform{};
	BoundingBox m_boundingBox;

protected:
	void processShader(std::wstring& vsCso, std::wstring& psCso, std::wstring vsHlsl, std::wstring psHlsl);
};