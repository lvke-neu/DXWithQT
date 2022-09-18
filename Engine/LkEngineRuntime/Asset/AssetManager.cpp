#include "AssetManager.h"
#include "../Core/base/Utility.h"
#include <d3dcompiler.h>
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"

namespace LkEngine
{
	void AssetManager::init()
	{
		LOG_INFO("AssetManager initialization is complete");
	}




	ComPtr<ID3D11VertexShader> AssetManager::loadVsShaderAsset(const std::string& relativeVsShaderPath, ComPtr<ID3DBlob>& blob)
	{
		ComPtr<ID3D11VertexShader> pVertexShader;
		//ComPtr<ID3DBlob> blob;
		std::string absoluteShaderPath;

		RelativePath2AbsolutePath(relativeVsShaderPath, absoluteShaderPath);

		D3DReadFileToBlob(multiByteToWideChar(absoluteShaderPath), blob.ReleaseAndGetAddressOf());
		m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, pVertexShader.GetAddressOf());

		//blob.Reset();

		return pVertexShader;

	}

	ComPtr<ID3D11PixelShader> AssetManager::loadPsShaderAsset(const std::string& relativePsShaderPath)
	{
		ComPtr<ID3D11PixelShader> pPixelShader;
		ComPtr<ID3DBlob> blob;
		std::string absoluteShaderPath;

		RelativePath2AbsolutePath(relativePsShaderPath, absoluteShaderPath);

		D3DReadFileToBlob(multiByteToWideChar(absoluteShaderPath), blob.ReleaseAndGetAddressOf());
		m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, pPixelShader.GetAddressOf());

		//blob.Reset();

		return pPixelShader;

	}

	ComPtr<ID3D11ShaderResourceView> AssetManager::loadTextureAsset(const std::string& relativeTexturePath)
	{
		std::string absoluteTexturePath;
		ComPtr<ID3D11ShaderResourceView> pTextureSRV;

		RelativePath2AbsolutePath(relativeTexturePath, absoluteTexturePath);

		if (absoluteTexturePath.substr(absoluteTexturePath.size() - 3) == "dds")
		{
			DirectX::CreateDDSTextureFromFile(m_pd3dDevice.Get(), multiByteToWideChar(absoluteTexturePath), nullptr, pTextureSRV.GetAddressOf());
		}
		else
		{
			DirectX::CreateWICTextureFromFile(m_pd3dDevice.Get(), multiByteToWideChar(absoluteTexturePath), nullptr, pTextureSRV.GetAddressOf());
		}

		return pTextureSRV;
	}
}