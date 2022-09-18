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

}
