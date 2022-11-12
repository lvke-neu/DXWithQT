#pragma once 
#include <DirectXMath.h>

namespace LkEngine
{
	using namespace DirectX;
	struct DirectionLight
	{
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
		XMFLOAT4 specular;
		XMFLOAT3 direction;
		float pad;
	};

	static DirectionLight COMMON_DIRLIGHT
	{ 
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 5.0f },
		{ 0.0f, -0.5f, 0.5f },
		1.0f
	};
}
