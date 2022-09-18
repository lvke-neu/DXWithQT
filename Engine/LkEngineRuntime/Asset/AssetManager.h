/***************************************************************************************
Author: lvke
Date:2022/9/18 12:26
Description:
AssetManager, load shader, load texture
****************************************************************************************/

#pragma once

#include <string>
#include "../Core/base/SingletonInterface.h"
#include "../Core/base/ManagerInterface.h"


namespace LkEngine
{

	class AssetManager : public ISingleton<AssetManager>, public IManager
	{
	public:
		virtual void init() override;

		ComPtr<ID3D11VertexShader> loadVsShaderAsset(const std::string& relativeVsShaderPath, ComPtr<ID3DBlob>& blob);
		ComPtr<ID3D11PixelShader>  loadPsShaderAsset(const std::string& relativePsShaderPath);
		ComPtr<ID3D11ShaderResourceView> loadTextureAsset(const std::string& relativeTexturePath);
	};
}