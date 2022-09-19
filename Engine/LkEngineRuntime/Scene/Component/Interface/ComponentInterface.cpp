#include "ComponentInterface.h"
#include "../../../Asset/AssetManager.h"

namespace LkEngine
{
	IComponent::IComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext):
		m_pd3dDevice(pd3dDevice), m_pd3dImmediateContext(pd3dImmediateContext)
	{
		D3D11_BUFFER_DESC cbd;
		ZeroMemory(&cbd, sizeof(cbd));
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.ByteWidth = sizeof(WorldMatrix);
		m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pWorldMatrixCB.GetAddressOf());


		cbd.ByteWidth = sizeof(Material);
		m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pMaterialCB.GetAddressOf());

		
	}

	IComponent::~IComponent()
	{
		m_pWorldMatrixCB.Reset();
		m_pVertexShader.Reset();
		m_pPixelShader.Reset();
		m_pVertexLayout.Reset();
		m_pTexture.Reset();
		m_pMaterialCB.Reset();
	}

	void IComponent::setVsShader(const std::string& vsShader)
	{ 
		m_vsShader = vsShader;
		m_pVertexShader.Reset();

		ComPtr<ID3DBlob> blob;

		m_pVertexShader = AssetManager::getInstance().loadVsShaderAsset(vsShader, blob);

		createVertexLayout(blob);

		//blob.Reset();


	}

	void IComponent::setPsShader(const std::string& psShader)
	{
		m_psShader = psShader;
		m_pPixelShader.Reset();

		m_pPixelShader = AssetManager::getInstance().loadPsShaderAsset(psShader);
	}

	void IComponent::setTexture(const std::string& texture)
	{
		m_texture = texture;
		m_pTexture.Reset();

		m_pTexture = AssetManager::getInstance().loadTextureAsset(texture);

	}

	void IComponent::setMaterial(const Material& material) 
	{ 
		m_material = material; 

		D3D11_MAPPED_SUBRESOURCE mappedData;
		m_pd3dImmediateContext->Map(m_pMaterialCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
		memcpy_s(mappedData.pData, sizeof(Material), &m_material, sizeof(Material));
		m_pd3dImmediateContext->Unmap(m_pMaterialCB.Get(), 0);
	}

	XMMATRIX XM_CALLCONV InverseTranspose(DirectX::FXMMATRIX M)
	{
		using namespace DirectX;

		XMMATRIX A = M;
		A.r[3] = g_XMIdentityR3;

		return XMMatrixTranspose(XMMatrixInverse(nullptr, A));
	}

	void IComponent::onTransformChanged()
	{
		WorldMatrix worldMatrix;
		worldMatrix.g_world = XMMatrixTranspose(m_transform.getWorldMatrix());
		worldMatrix.g_worldInvTranspose = XMMatrixTranspose(InverseTranspose(m_transform.getWorldMatrix()));


		D3D11_MAPPED_SUBRESOURCE mappedData;
		m_pd3dImmediateContext->Map(m_pWorldMatrixCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
		memcpy_s(mappedData.pData, sizeof(WorldMatrix), &worldMatrix, sizeof(WorldMatrix));
		m_pd3dImmediateContext->Unmap(m_pWorldMatrixCB.Get(), 0);
	}
}
