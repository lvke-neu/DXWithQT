#include <DirectXCollision.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include <d3d11.h>

using namespace DirectX;

using namespace Microsoft::WRL;

class TestComponent
{
public:
	struct VertexPosColor
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 color;
		static const D3D11_INPUT_ELEMENT_DESC inputLayout[2];
	};
	
	void initialize(Microsoft::WRL::ComPtr<ID3D11Device> pd3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	void updateScene(float deltaTime);
	void drawScene();

private:
	ComPtr<ID3D11InputLayout> m_pVertexLayout;	
	ComPtr<ID3D11Buffer> m_pVertexBuffer;		
	ComPtr<ID3D11VertexShader> m_pVertexShader;	
	ComPtr<ID3D11PixelShader> m_pPixelShader;	

private:
	Microsoft::WRL::ComPtr<ID3D11Device> m_pd3dDevice{ nullptr };
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext{ nullptr };
};