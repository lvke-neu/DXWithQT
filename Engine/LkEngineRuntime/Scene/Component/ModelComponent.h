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
		ModelComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext, const std::string& modelPath);
	
		void buildMesh() {};
		void createVertexLayout(const ComPtr<ID3DBlob>& blob) {};
		void bindPipeState() {};
		void draw();
	private:
		void loadModel();
		void processNode(aiNode* node, const aiScene* scene);
	private:
		std::string m_modelPath{ "" };
		std::vector<SubModelComponent> m_subModelComponents;
	};
}

