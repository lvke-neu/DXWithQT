/***************************************************************************************
Author: lvke
Date:2022/9/18 21:11
Description:
The Interface of Component
****************************************************************************************/

#pragma once 

#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXCollision.h>
#include <string>
#include "../Common/Material.h"
#include "../Common/Transform.h"
#include "../../../Core/serialization/Reference.h"


/*
 commonshader constbuffer rule:
	slot 0:ViewMatrix
	slot 1: ProjMatrix

*/

namespace LkEngine
{
	using namespace Microsoft::WRL;

	class IComponent : public Reference
	{
	public:	
		struct WorldMatrix
		{
			XMMATRIX g_world;
			XMMATRIX g_worldInvTranspose;
		};
	public:
		IComponent(void** parameter);
		IComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
		virtual ~IComponent();
		virtual void buildMesh() = 0;
		virtual void createVertexLayout(const ComPtr<ID3DBlob>& blob) = 0;
		virtual void bindPipeState() = 0;
		virtual void draw() = 0;
	public:
		virtual void serialize(std::string& serializationStr) override;
		virtual void runFunction(const std::string& funcName, const rapidjson::Value& funcParameter) override;
	public:
		std::string getVsShader() { return m_vsShader; }
		void setVsShader(const std::string& vsShader);

		std::string getPsShader() { return m_psShader; }
		void setPsShader(const std::string& psShader);

		std::string getGsShader() { return m_gsShader; }
		void setGsShader(const std::string& gsShader);

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

		BoundingBox getBoundingBox() { return m_boundingBox; };
		void setBoundingBox(BoundingBox boundingBox) { m_boundingBox = boundingBox; };

		std::string getComponetType() { return m_componetType; }
		std::string getUuId() { return m_uuid; }
	protected:
		void setComponetType(const std::string componetType) { m_componetType = componetType; }
		void setUuId(const std::string uuid) { m_uuid = uuid; }
		void bind_Set_Func();

		void set_VsShader(const rapidjson::Value& funcParameter);
		void set_GsShader(const rapidjson::Value& funcParameter);
		void set_PsShader(const rapidjson::Value& funcParameter);
		void set_Texture(const rapidjson::Value& funcParameter);
		void set_Material(const rapidjson::Value& funcParameter);
		void set_Transform(const rapidjson::Value& funcParameter);

	public:
		void onTransformChanged();
	protected:
		ComPtr<ID3D11Device> m_pd3dDevice{ nullptr };
		ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext{ nullptr };

		ComPtr<ID3D11VertexShader> m_pVertexShader{ nullptr };
		ComPtr<ID3D11PixelShader> m_pPixelShader{ nullptr };
		ComPtr<ID3D11GeometryShader> m_pGeometryShader{ nullptr };
		ComPtr<ID3D11InputLayout> m_pVertexLayout{ nullptr };

		ComPtr<ID3D11ShaderResourceView> m_pTexture{ nullptr };

		ComPtr<ID3D11Buffer> m_pWorldMatrixCB{ nullptr };;
		ComPtr<ID3D11Buffer> m_pMaterialCB{ nullptr };
	protected:
		std::string m_vsShader;
		std::string m_gsShader;
		std::string m_psShader;
		std::string m_texture;
		Material m_material;
		Transform m_transform;
		BoundingBox m_boundingBox;

		std::string m_uuid;
		std::string m_componetType;
	};
}
