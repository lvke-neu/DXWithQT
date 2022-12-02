/***************************************************************************************
Author: lvke
Date:2022/12/02 9:48
Description:
Bindable Interface
****************************************************************************************/
#pragma once
#include <d3d11.h>

namespace Twinkle
{
	class IBindable
	{
	protected:
		ID3D11Device* m_pDevice{ nullptr };
		ID3D11DeviceContext* m_pDeviceContent{ nullptr };
	};
}