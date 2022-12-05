#include "BindableInterface.h"
#include <d3dcompiler.h>
#include "../TextureLoader/DDSTextureLoader.h"
#include "../TextureLoader/WICTextureLoader.h"

namespace Twinkle
{
	ID3DBlob * IBindable::ReadFileToBlob(const std::string & relativeFilePath)
	{
		ID3DBlob* blob{ nullptr };
		std::string absoluteFilePath;

		RelativePath2AbsolutePath(relativeFilePath, absoluteFilePath);

		D3DReadFileToBlob(multiByteToWideChar(absoluteFilePath), &blob);

		return blob;
	}

	ID3D11ShaderResourceView * IBindable::LoadTexture(const std::string & relativeFilePath)
	{
		std::string absoluteFilePath;
		ID3D11ShaderResourceView* pTextureSRV;

		RelativePath2AbsolutePath(relativeFilePath, absoluteFilePath);

		if (absoluteFilePath.substr(absoluteFilePath.size() - 3) == "dds")
		{
			DirectX::CreateDDSTextureFromFile(m_pDevice, multiByteToWideChar(absoluteFilePath), nullptr, &pTextureSRV);
		}
		else
		{
			DirectX::CreateWICTextureFromFile(m_pDevice, multiByteToWideChar(absoluteFilePath), nullptr, &pTextureSRV);
		}

		return pTextureSRV;
	}
}