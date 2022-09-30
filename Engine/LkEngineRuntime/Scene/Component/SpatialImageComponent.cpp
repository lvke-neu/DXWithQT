#include "SpatialImageComponent.h"
#include "Common/VertexType.h"
#include "Common/RenderStates.h"
#include "../../Core/serialization/Reflection.h"



namespace LkEngine
{
	SpatialImageComponent::SpatialImageComponent(void** parameter) : IComponent(parameter)
	{
		setComponetType("SpatialImageComponent");

		buildMesh();

		setVsShader("builtin\\Shader\\ScreenPixelFixedImageVS.cso");
		setGsShader("builtin\\Shader\\ScreenPixelFixedImageGS.cso");
		setPsShader("builtin\\Shader\\ScreenPixelFixedImagePS.cso");
		setTexture("builtin\\Texture\\stone.dds");
		setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, -4.0f, 0.0f)
		));
	}

	SpatialImageComponent::SpatialImageComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext) : IComponent(pd3dDevice, pd3dImmediateContext)
	{
		setComponetType("SpatialImageComponent");

		buildMesh();

		setVsShader("builtin\\Shader\\ScreenPixelFixedImageVS.cso");
		setGsShader("builtin\\Shader\\ScreenPixelFixedImageGS.cso");
		setPsShader("builtin\\Shader\\ScreenPixelFixedImagePS.cso");
		setTexture("builtin\\Texture\\stone.dds");
		setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, -4.0f, 0.0f)
		));
	}

	void SpatialImageComponent::buildMesh()
	{
		m_pVertexBuffer.Reset();
		m_pIndexBuffer.Reset();


		VertexPos vertices[1]; 
		vertices[0].position = XMFLOAT3(0.0f, 0.0f, 0.0f);
			
		// VertexBuffer
		D3D11_BUFFER_DESC vbd;
		ZeroMemory(&vbd, sizeof(vbd));
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(vertices);
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = vertices;
		m_pd3dDevice->CreateBuffer(&vbd, &InitData, m_pVertexBuffer.GetAddressOf());


	}

	void SpatialImageComponent::createVertexLayout(const ComPtr<ID3DBlob>& blob)
	{
		m_pd3dDevice->CreateInputLayout(VertexPos::inputLayout, 1, blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout.GetAddressOf());
	}

	void SpatialImageComponent::bindPipeState()
	{
		UINT stride = sizeof(VertexPos);
		UINT offset = 0;
		m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
		m_pd3dImmediateContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

		m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());
		m_pd3dImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
		m_pd3dImmediateContext->GSSetShader(m_pGeometryShader.Get(), nullptr, 0);
		m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);


		m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pTexture.GetAddressOf());


		m_pd3dImmediateContext->PSSetSamplers(0, 1, RenderStates::SSLinearWrap.GetAddressOf());

		m_pd3dImmediateContext->VSSetConstantBuffers(2, 1, m_pWorldMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->GSSetConstantBuffers(2, 1, m_pWorldMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(2, 1, m_pWorldMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->VSSetConstantBuffers(3, 1, m_pMaterialCB.GetAddressOf());
		m_pd3dImmediateContext->GSSetConstantBuffers(3, 1, m_pMaterialCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(3, 1, m_pMaterialCB.GetAddressOf());	
	}

	void SpatialImageComponent::draw()
	{
		m_pd3dImmediateContext->OMSetDepthStencilState(RenderStates::DSSNoDepthTest.Get(), 0);

		bindPipeState();
		m_pd3dImmediateContext->Draw(1, 0);

		m_pd3dImmediateContext->OMSetDepthStencilState(RenderStates::DSSLessEqual.Get(), 0);
	}
}
