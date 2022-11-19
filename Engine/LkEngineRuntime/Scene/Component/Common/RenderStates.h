#pragma once

#include <d3d11.h>
#include <wrl/client.h>

namespace LkEngine
{
	using namespace Microsoft::WRL;
	class RenderStates
	{
	public:


		static ComPtr<ID3D11SamplerState> SSLinearWrap;
		static ComPtr<ID3D11SamplerState> SSAnisotropicWrap;
		static ComPtr<ID3D11SamplerState> SSShadow;

		static ComPtr<ID3D11RasterizerState> RSWireframe;
		static ComPtr<ID3D11RasterizerState> RSNoCull;
		static ComPtr<ID3D11RasterizerState> RSCullClockWise;

		static ComPtr<ID3D11BlendState> BSTransparent;
		static ComPtr<ID3D11BlendState> BSNoColorWrite;

		static ComPtr<ID3D11DepthStencilState> DSSWriteStencil;
		static ComPtr<ID3D11DepthStencilState> DSSDrawWithStencil;
		static ComPtr<ID3D11DepthStencilState> DSSLessEqual;
		static ComPtr<ID3D11DepthStencilState> DSSNoDepthTest;

		



	public:
		static void Init(ComPtr<ID3D11Device> pd3dDevice);
	};
}

