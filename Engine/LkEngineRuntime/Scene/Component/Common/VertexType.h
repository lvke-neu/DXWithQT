#pragma once

#include <DirectXMath.h>
#include <d3d11.h>

namespace LkEngine
{
	using namespace DirectX;

	struct VertexPosNormalTex
	{
		XMFLOAT3 position;
		XMFLOAT3 normal;
		XMFLOAT2 texcoord;
		static D3D11_INPUT_ELEMENT_DESC inputLayout[3];
	};

	struct VertexPos
	{
		XMFLOAT3 position;
		static D3D11_INPUT_ELEMENT_DESC inputLayout[1];
	};
}