/***************************************************************************************
Author: lvke
Date:2022/12/02 9:48
Description:
Bindable Interface
****************************************************************************************/
#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include "../TextureLoader/DDSTextureLoader.h"
#include "../TextureLoader/WICTextureLoader.h"
#include "Runtime/Utility/Utility.h"

namespace Twinkle
{
	class IBindable
	{
	public:
		virtual void bind() = 0;
		ID3DBlob* ReadFileToBlob(const std::string& relativeFilePath);
		ID3D11ShaderResourceView* LoadTexture(const std::string& relativeFilePath);
	protected:
		ID3D11Device* m_pDevice{ nullptr };
		ID3D11DeviceContext* m_pDeviceContent{ nullptr };
	};
}