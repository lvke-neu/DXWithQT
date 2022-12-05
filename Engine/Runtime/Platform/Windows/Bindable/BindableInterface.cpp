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

		wchar_t* absoluteFilePathWchar = multiByteToWideChar(absoluteFilePath);
		D3DReadFileToBlob(absoluteFilePathWchar, &blob);

		SAFE_DELETE_SETNULL(absoluteFilePathWchar);

		return blob;
	}

	ID3D11ShaderResourceView * IBindable::LoadTexture(const std::string & relativeFilePath)
	{
		std::string absoluteFilePath;
		ID3D11ShaderResourceView* pTextureSRV;

		RelativePath2AbsolutePath(relativeFilePath, absoluteFilePath);

		wchar_t* absoluteFilePathWchar = multiByteToWideChar(absoluteFilePath);
		if (absoluteFilePath.substr(absoluteFilePath.size() - 3) == "dds")
		{
			DirectX::CreateDDSTextureFromFile(m_pDevice, absoluteFilePathWchar, nullptr, &pTextureSRV);
		}
		else
		{
			DirectX::CreateWICTextureFromFile(m_pDevice, absoluteFilePathWchar, nullptr, &pTextureSRV);
		}

		SAFE_DELETE_SETNULL(absoluteFilePathWchar);

		return pTextureSRV;
	}
}