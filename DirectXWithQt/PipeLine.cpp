#include "PipeLine.h"
#include "d3dUtil.h"

PipeLine* PipeLine::pipeline = new PipeLine;

void PipeLine::init(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
{
	m_pd3dDevice = pd3dDevice;
	m_pd3dImmediateContext = pd3dImmediateContext;
}

void PipeLine::create_VtxIdx_Buffer(const Mesh& mesh, ComPtr<ID3D11Buffer>& vertexBuffer, ComPtr<ID3D11Buffer> indexBuffer)
{
	// VertexBuffer
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = (UINT)mesh.vertexBuffer.size() * sizeof(VertexPosNormalTex);
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = mesh.vertexBuffer.data();
	m_pd3dDevice->CreateBuffer(&vbd, &InitData, vertexBuffer.GetAddressOf());

	//IndexBuffer
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = mesh.indexBuffer.size() * sizeof(DWORD);
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	InitData.pSysMem = mesh.indexBuffer.data();
	m_pd3dDevice->CreateBuffer(&ibd, &InitData, indexBuffer.GetAddressOf());
}

void PipeLine::create_VtxIdx_Shader_InputLayout(const wchar_t* m_shaderPath, ComPtr<ID3D11VertexShader> vertexShader, ComPtr<ID3D11PixelShader> pixelShader, ComPtr<ID3D11InputLayout> vertexLayout)
{
	ComPtr<ID3DBlob> blob;

	// 创建顶点着色器
	CreateShaderFromFile(L"HLSL\\Common_VS.cso", L"HLSL\\Common_VS.hlsl", "VS", "vs_5_0", blob.ReleaseAndGetAddressOf());
	m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, vertexShader.GetAddressOf());


	// 创建顶点布局
	D3D11_INPUT_ELEMENT_DESC inputLayout[3] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{ "NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};

	m_pd3dDevice->CreateInputLayout(inputLayout, ARRAYSIZE(inputLayout),
		blob->GetBufferPointer(), blob->GetBufferSize(), vertexLayout.GetAddressOf());


	// 创建像素着色器
	CreateShaderFromFile(L"HLSL\\Common_PS.cso", L"HLSL\\Common_PS.hlsl", "PS", "ps_5_0", blob.ReleaseAndGetAddressOf());
	m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, pixelShader.GetAddressOf());
}