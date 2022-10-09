/***************************************************************************************
Author: lvke
Date:
Description:
Model Component
****************************************************************************************/
#pragma once

#include "Interface/ComponentInterface.h"
#include <assimp/Importer.hpp>      
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

namespace LkEngine
{
	class SubModelComponent : public IComponent
	{
	public:
		SubModelComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext, aiMesh* mesh);
	public:
		virtual void buildMesh() override;
		virtual void createVertexLayout(const ComPtr<ID3DBlob>& blob) override;
		virtual void bindPipeState() override;
		virtual void draw() override;

	private:
		ComPtr<ID3D11Buffer> m_pVertexBuffer{ nullptr };
		ComPtr<ID3D11Buffer> m_pIndexBuffer{ nullptr };

		UINT m_indexCount = 0;

		aiMesh* m_mesh;
	};

	class ModelComponent : public IComponent
	{
	public:
		ModelComponent(void** parameter);
		ModelComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	
		void buildMesh() {};
		void createVertexLayout(const ComPtr<ID3DBlob>& blob) {};
		void bindPipeState() {};
		void draw();
	public:
		virtual Transform getTransform()
		{ 
			return m_transform; 
		}
		virtual void setTransform(const Transform& transform)
		{
			m_transform = transform;
			for (auto& submodel : m_subModelComponents)
				submodel.setTransform(m_transform); 
		}

		virtual XMFLOAT3 getScale()
		{ 
			return m_transform.getScale(); 
		}
		virtual void setScale(float x, float y, float z)
		{
			m_transform.setScale(XMFLOAT3(x, y, z));
			for (auto& submodel : m_subModelComponents)
				submodel.setScale(XMFLOAT3(x, y, z));
		}
		virtual void setScale(const XMFLOAT3& scale)
		{ 
			m_transform.setScale(scale);
			for (auto& submodel : m_subModelComponents)
				submodel.setScale(scale);
		}

		virtual XMFLOAT3 getRotation()
		{ 
			return m_transform.getRotation(); 
		}
		virtual void setRotation(float x, float y, float z)
		{
			m_transform.setRotation(XMFLOAT3(x, y, z));
			for (auto& submodel : m_subModelComponents)
				submodel.setRotation(XMFLOAT3(x, y, z));
		}
		virtual void setRotation(const XMFLOAT3& rot)
		{ 
			m_transform.setRotation(rot);
			for (auto& submodel : m_subModelComponents)
				submodel.setRotation(rot);
		}

		virtual XMFLOAT3 getPosition()
		{ 
			return m_transform.getPosition(); 
		}
		virtual void setPosition(float x, float y, float z)
		{ 
			m_transform.setPosition(XMFLOAT3(x, y, z));
			for (auto& submodel : m_subModelComponents)
				submodel.setPosition(XMFLOAT3(x, y, z));
		}
		virtual void setPosition(const XMFLOAT3& pos)
		{ 
			m_transform.setPosition(pos);
			for (auto& submodel : m_subModelComponents)
				submodel.setPosition(pos);
		}

		std::string getModelPath();
		void  setModelPath(const std::string& modelPath); 
	private:
		void loadModel();
		void processNode(aiNode* node, const aiScene* scene);
	private:
		std::string m_modelPath{ "" };
		std::vector<SubModelComponent> m_subModelComponents;
	};
}

