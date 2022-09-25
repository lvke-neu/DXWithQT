#include "SkyBoxComponent.h"
#include "../../Asset/AssetManager.h"
#include "Common/RenderStates.h"

namespace LkEngine
{
	SkyBoxComponent::SkyBoxComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext) :BoxComponent(pd3dDevice, pd3dImmediateContext) 
	{
		m_pd3dImmediateContext->RSSetState(RenderStates::RSNoCull.Get());
		m_pd3dImmediateContext->OMSetDepthStencilState(RenderStates::DSSLessEqual.Get(), 0);

		setVsShader("builtin\\Shader\\SkyBoxComponentVS.cso");
		setPsShader("builtin\\Shader\\SkyBoxComponentPS.cso");
		setTexture("builtin\\Texture\\SkyBox\\daylight.jpg");
		setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f)
		));
	}
	void SkyBoxComponent::setTexture(const std::string& texture)
	{
		if (m_texture != texture)
		{
			m_texture = texture;
			m_pTexture.Reset();

			m_pTexture = AssetManager::getInstance().loadSkyBoxTextureAsset(texture);
		}
	}

	void SkyBoxComponent::draw()
	{
		XMMATRIX V = CameraManager::getInstance().getViewMatrix();
		V.r[3] = g_XMIdentityR3;
		CameraManager::getInstance().changeViewMatrixCB(V);
		BoxComponent::draw();
		CameraManager::getInstance().onViewMatrixChanged();
	}
}