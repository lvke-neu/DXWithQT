/***************************************************************************************
Author: lvke
Date:2022/12/02 9:48
Description:
Bindable Interface
****************************************************************************************/
#pragma once
#include <d3d11.h>
#include "../DirectX11Manager.h"
#include "Runtime/Utility/Utility.h"

namespace Twinkle
{
	class IBindable
	{
	public:
		virtual void bind() = 0;
	protected:
		ID3D11Device* m_pDevice{ nullptr };
		ID3D11DeviceContext* m_pDeviceContent{ nullptr };
	};
}