/***************************************************************************************
Author: lvke
Date:2022/9/18 21:11
Description:
The Interface of Component
****************************************************************************************/

#pragma once 

#include <d3d11.h>
#include <wrl/client.h>
#include <string>
#include "../Common/Material.h"
#include "../Common/Transform.h"

/*
 commonshader constbuffer rule:
	slot 0:ViewMatrix
	slot 1: ProjMatrix

*/

namespace LkEngine
{
	using namespace Microsoft::WRL;

	class IComponent
	{
	public:	
		struct WorldMatrix
		{
			XMMATRIX g_world;
			XMMATRIX g_worldInvTranspose;
		};
	public:
		
		IComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
		virtual ~IComponent();
		virtual void buildMesh() = 0;
		virtual void createVertexLayout(const ComPtr<ID3DBlob>& blob) = 0;
		virtual void bindPipeState() = 0;
		virtual void draw() = 0;
	public:
		std::string getVsShader() { return m_vsShader; }
		void setVsShader(const std::string& vsShader);

		std::string getPsShader() { return m_psShader; }
		void setPsShader(const std::string& psShader);

		std::string getTexture(){ return m_texture; }
		void setTexture(const std::string& texture); 

		Material getMaterial() { return m_material; }
		void setMaterial(const Material& material);
	public:
		Transform getTransform() { return m_transform; }
		void setTransform(const Transform& transform) { m_transform = transform; onTransformChanged(); }

		XMFLOAT3 getScale() { return m_transform.getScale(); }
		void setScale(float x, float y, float z){ setScale(XMFLOAT3(x, y, z));}
		void setScale(const XMFLOAT3& scale) { m_transform.setScale(scale); onTransformChanged();}

		XMFLOAT3 getRotation() { return m_transform.getRotation(); }
		void setRotation(float x, float y, float z){setRotation(XMFLOAT3(x, y, z));}
		void setRotation(const XMFLOAT3& rot) { m_transform.setRotation(rot); onTransformChanged();}

		XMFLOAT3 getPosition() { return m_transform.getPosition(); }
		void setPosition(float x, float y, float z){setPosition(XMFLOAT3(x, y, z));}
		void setPosition(const XMFLOAT3& pos) { m_transform.setPosition(pos); onTransformChanged();}
	public:
		void onTransformChanged();
	protected:
		ComPtr<ID3D11Device> m_pd3dDevice{ nullptr };
		ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext{ nullptr };

		ComPtr<ID3D11VertexShader> m_pVertexShader{ nullptr };
		ComPtr<ID3D11PixelShader> m_pPixelShader{ nullptr };
		ComPtr<ID3D11InputLayout> m_pVertexLayout{ nullptr };

		ComPtr<ID3D11ShaderResourceView> m_pTexture{ nullptr };

		ComPtr<ID3D11Buffer> m_pWorldMatrixCB{ nullptr };;
		ComPtr<ID3D11Buffer> m_pMaterialCB{ nullptr };
	protected:
		std::string m_vsShader;
		std::string m_psShader;
		std::string m_texture;
		Material m_material;
		Transform m_transform;
	};
}
