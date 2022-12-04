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
	std::vector<D3D11_INPUT_ELEMENT_DESC> VertexPosNormalTex::ied = 
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

}