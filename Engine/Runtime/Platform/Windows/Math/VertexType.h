#include <DirectXMath.h>
#include <d3d11.h>
#include <vector>

namespace Twinkle
{
	using namespace DirectX;

	struct VertexPosNormalTex
	{
		XMFLOAT3 position;
		XMFLOAT3 normal;
		XMFLOAT2 texcoord;
		static std::vector<D3D11_INPUT_ELEMENT_DESC> ied;
	};
}