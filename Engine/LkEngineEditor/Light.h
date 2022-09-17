#pragma once 
#include <DirectXMath.h>

/*

环境光
漫反射光
高光
*/


using namespace DirectX;
struct DirectionLight
{
	XMFLOAT4 ambient;
	XMFLOAT4 diffuse;
	XMFLOAT4 specular;
	XMFLOAT3 direction;
	float pad;
};