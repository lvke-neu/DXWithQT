/***************************************************************************************
Author: lvke
Date:2022/9/18 22:06
Description:
Manager's base class
****************************************************************************************/

#pragma once 

#include <d3d11.h>
#include <wrl/client.h>


namespace LkEngine
{
	using namespace Microsoft::WRL;

	class IManager
	{
	public:
		virtual void initialize(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
		{
			m_pd3dDevice = pd3dDevice;
			m_pd3dImmediateContext = pd3dImmediateContext;
			
			init();
		}

		//Derived class's init
		virtual void init() = 0;

		virtual ~IManager() = default;
	protected:
		ComPtr<ID3D11Device> m_pd3dDevice{ nullptr };
		ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext{ nullptr };
	};
}
