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
		if(blob)
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
		if (blob)
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

	ComPtr<ID3D11ShaderResourceView> AssetManager::loadSkyBoxTextureAsset(const std::string& relativeTexturePath)
	{
		std::string absoluteTexturePath;
		ComPtr<ID3D11ShaderResourceView> pTextureSRV;

		RelativePath2AbsolutePath(relativeTexturePath, absoluteTexturePath);

		if (absoluteTexturePath.substr(absoluteTexturePath.size() - 3) == "dds")
		{
			DirectX::CreateDDSTextureFromFile(m_pd3dDevice.Get(), nullptr, multiByteToWideChar(absoluteTexturePath), nullptr, pTextureSRV.GetAddressOf());
		}
		else
		{
			CreateWICTexture2DCubeFromFile(m_pd3dDevice.Get(), m_pd3dImmediateContext.Get(), multiByteToWideChar(absoluteTexturePath), nullptr, pTextureSRV.GetAddressOf(), false);
		}

		return pTextureSRV;
	}



	HRESULT AssetManager::CreateWICTexture2DCubeFromFile(
		ID3D11Device* d3dDevice,
		ID3D11DeviceContext* d3dDeviceContext,
		const std::wstring& cubeMapFileName,
		ID3D11Texture2D** textureArray,
		ID3D11ShaderResourceView** textureCubeView,
		bool generateMips)
	{

		if (!d3dDevice || !d3dDeviceContext || !(textureArray || textureCubeView))
			return E_INVALIDARG;



		ID3D11Texture2D* srcTex = nullptr;
		ID3D11ShaderResourceView* srcTexSRV = nullptr;


		HRESULT hResult = DirectX::CreateWICTextureFromFile(d3dDevice,
			(generateMips ? d3dDeviceContext : nullptr),
			cubeMapFileName.c_str(),
			(ID3D11Resource**)&srcTex,
			(generateMips ? &srcTexSRV : nullptr));


		if (FAILED(hResult))
		{
			return hResult;
		}

		D3D11_TEXTURE2D_DESC texDesc, texArrayDesc;
		srcTex->GetDesc(&texDesc);


		if (texDesc.Width * 3 != texDesc.Height * 4)
		{
		
			SAFERELEASE(srcTex);
			SAFERELEASE(srcTexSRV);
			return E_FAIL;
		}



		UINT squareLength = texDesc.Width / 4;
		texArrayDesc.Width = squareLength;
		texArrayDesc.Height = squareLength;
		texArrayDesc.MipLevels = (generateMips ? texDesc.MipLevels - 2 : 1);
		texArrayDesc.ArraySize = 6;
		texArrayDesc.Format = texDesc.Format;
		texArrayDesc.SampleDesc.Count = 1;
		texArrayDesc.SampleDesc.Quality = 0;
		texArrayDesc.Usage = D3D11_USAGE_DEFAULT;
		texArrayDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		texArrayDesc.CPUAccessFlags = 0;
		texArrayDesc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

		ID3D11Texture2D* texArray = nullptr;
		hResult = d3dDevice->CreateTexture2D(&texArrayDesc, nullptr, &texArray);
		if (FAILED(hResult))
		{
			SAFERELEASE(srcTex);
			SAFERELEASE(srcTexSRV);
			return hResult;
		}



		D3D11_BOX box;

		box.front = 0;
		box.back = 1;

		for (UINT i = 0; i < texArrayDesc.MipLevels; ++i)
		{

			box.left = squareLength * 2;
			box.top = squareLength;
			box.right = squareLength * 3;
			box.bottom = squareLength * 2;
			d3dDeviceContext->CopySubresourceRegion(
				texArray,
				D3D11CalcSubresource(i, D3D11_TEXTURECUBE_FACE_POSITIVE_X, texArrayDesc.MipLevels),
				0, 0, 0,
				srcTex,
				i,
				&box);


			box.left = 0;
			box.top = squareLength;
			box.right = squareLength;
			box.bottom = squareLength * 2;
			d3dDeviceContext->CopySubresourceRegion(
				texArray,
				D3D11CalcSubresource(i, D3D11_TEXTURECUBE_FACE_NEGATIVE_X, texArrayDesc.MipLevels),
				0, 0, 0,
				srcTex,
				i,
				&box);


			box.left = squareLength;
			box.top = 0;
			box.right = squareLength * 2;
			box.bottom = squareLength;
			d3dDeviceContext->CopySubresourceRegion(
				texArray,
				D3D11CalcSubresource(i, D3D11_TEXTURECUBE_FACE_POSITIVE_Y, texArrayDesc.MipLevels),
				0, 0, 0,
				srcTex,
				i,
				&box);



			box.left = squareLength;
			box.top = squareLength * 2;
			box.right = squareLength * 2;
			box.bottom = squareLength * 3;
			d3dDeviceContext->CopySubresourceRegion(
				texArray,
				D3D11CalcSubresource(i, D3D11_TEXTURECUBE_FACE_NEGATIVE_Y, texArrayDesc.MipLevels),
				0, 0, 0,
				srcTex,
				i,
				&box);

			box.left = squareLength;
			box.top = squareLength;
			box.right = squareLength * 2;
			box.bottom = squareLength * 2;
			d3dDeviceContext->CopySubresourceRegion(
				texArray,
				D3D11CalcSubresource(i, D3D11_TEXTURECUBE_FACE_POSITIVE_Z, texArrayDesc.MipLevels),
				0, 0, 0,
				srcTex,
				i,
				&box);


			box.left = squareLength * 3;
			box.top = squareLength;
			box.right = squareLength * 4;
			box.bottom = squareLength * 2;
			d3dDeviceContext->CopySubresourceRegion(
				texArray,
				D3D11CalcSubresource(i, D3D11_TEXTURECUBE_FACE_NEGATIVE_Z, texArrayDesc.MipLevels),
				0, 0, 0,
				srcTex,
				i,
				&box);


			squareLength /= 2;
		}



		if (textureCubeView)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
			viewDesc.Format = texArrayDesc.Format;
			viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
			viewDesc.TextureCube.MostDetailedMip = 0;
			viewDesc.TextureCube.MipLevels = texArrayDesc.MipLevels;

			hResult = d3dDevice->CreateShaderResourceView(texArray, &viewDesc, textureCubeView);
		}


		if (textureArray)
		{
			*textureArray = texArray;
		}
		else
		{
			SAFERELEASE(texArray);
		}

		SAFERELEASE(srcTex);
		SAFERELEASE(srcTexSRV);

		return hResult;
	}


	
	

}