#include "CameraManager.h"
#include "../../../Core/base/Utility.h"

namespace LkEngine
{
	void CameraManager::init()
	{
		m_pViewMatrixCB.Reset();
		m_pProjMatrixCB.Reset();

		D3D11_BUFFER_DESC cbd;
		ZeroMemory(&cbd, sizeof(cbd));
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.ByteWidth = sizeof(ViewMatrix);
		m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pViewMatrixCB.GetAddressOf());

		D3D11_BUFFER_DESC cbd2;
		ZeroMemory(&cbd2, sizeof(cbd2));
		cbd2.Usage = D3D11_USAGE_DYNAMIC;
		cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd2.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;


		cbd2.ByteWidth = sizeof(ProjMatrix);
		m_pd3dDevice->CreateBuffer(&cbd2, nullptr, m_pProjMatrixCB.GetAddressOf());


		m_pd3dImmediateContext->VSSetConstantBuffers(0, 1, m_pViewMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->GSSetConstantBuffers(0, 1, m_pViewMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(0, 1, m_pViewMatrixCB.GetAddressOf());

		m_pd3dImmediateContext->VSSetConstantBuffers(1, 1, m_pProjMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->GSSetConstantBuffers(1, 1, m_pProjMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(1, 1, m_pProjMatrixCB.GetAddressOf());
			
		LOG_INFO("CameraManager initialization is complete");
	}

	XMMATRIX CameraManager::getViewMatrix()
	{
		return XMMatrixInverse(nullptr, m_transform.getWorldMatrix());
	}

	XMMATRIX CameraManager::getProjMatrix()
	{
		return XMMatrixPerspectiveFovLH(m_fovAngleY, m_aspectRatio, m_nearZ, m_farZ);
	}

	void CameraManager::onViewMatrixChanged()
	{
		ViewMatrix viewMatrix;
		viewMatrix.g_view = XMMatrixTranspose(getViewMatrix());
		viewMatrix.g_eyePoW = XMFLOAT3(m_transform.getPosition());

		D3D11_MAPPED_SUBRESOURCE mappedData;
		m_pd3dImmediateContext->Map(m_pViewMatrixCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
		memcpy_s(mappedData.pData, sizeof(ViewMatrix), &viewMatrix, sizeof(ViewMatrix));
		m_pd3dImmediateContext->Unmap(m_pViewMatrixCB.Get(), 0);
	}

	void CameraManager::onProjMatrixChanged()
	{
		ProjMatrix projMatrix;
		projMatrix.g_proj = XMMatrixTranspose(getProjMatrix());
		projMatrix.g_viewportSize = XMFLOAT4(m_ScreenViewport.Width, m_ScreenViewport.Height, 1.0f / m_ScreenViewport.Width, 1.0f / m_ScreenViewport.Height);

		D3D11_MAPPED_SUBRESOURCE mappedData;
		m_pd3dImmediateContext->Map(m_pProjMatrixCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
		memcpy_s(mappedData.pData, sizeof(ProjMatrix), &projMatrix, sizeof(ProjMatrix));
		m_pd3dImmediateContext->Unmap(m_pProjMatrixCB.Get(), 0);
	}

	void CameraManager::changeViewMatrixCB(const XMMATRIX& view)
	{
		ViewMatrix viewMatrix;
		viewMatrix.g_view = XMMatrixTranspose(view);
		viewMatrix.g_eyePoW = XMFLOAT3(m_transform.getPosition());

		D3D11_MAPPED_SUBRESOURCE mappedData;
		m_pd3dImmediateContext->Map(m_pViewMatrixCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
		memcpy_s(mappedData.pData, sizeof(ViewMatrix), &viewMatrix, sizeof(ViewMatrix));
		m_pd3dImmediateContext->Unmap(m_pViewMatrixCB.Get(), 0);
	}
}