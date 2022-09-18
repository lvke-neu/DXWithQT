#pragma once 
#include <DirectXMath.h>

namespace LkEngine
{
	using namespace DirectX;

	struct Material
	{
		Material() = default;

		Material(const Material&) = default;
		Material& operator=(const Material&) = default;

		Material(Material&&) = default;
		Material& operator=(Material&&) = default;

		Material(const XMFLOAT4& _ambient, const XMFLOAT4& _diffuse, const XMFLOAT4& _specular,
			const XMFLOAT4& _reflect) :
			ambient(_ambient), diffuse(_diffuse), specular(_specular), reflect(_reflect) {}

		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
		XMFLOAT4 specular;
		XMFLOAT4 reflect;
	};
}




