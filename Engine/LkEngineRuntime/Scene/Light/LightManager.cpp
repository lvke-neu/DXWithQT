#include "LightManager.h"
#include "../../Core/base/Utility.h"
#include "../ShadowMap/ShadowMapManager.h"

namespace LkEngine
{

	void LightManager::init()
	{
		m_pSceneDirLightCB.Reset();

		D3D11_BUFFER_DESC cbd;
		ZeroMemory(&cbd, sizeof(cbd));
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.ByteWidth = sizeof(DirectionLight);
		m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pSceneDirLightCB.GetAddressOf());

		m_pd3dImmediateContext->VSSetConstantBuffers(2, 1, m_pSceneDirLightCB.GetAddressOf());
		m_pd3dImmediateContext->GSSetConstantBuffers(2, 1, m_pSceneDirLightCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(2, 1, m_pSceneDirLightCB.GetAddressOf());

		setDirLight(COMMON_DIRLIGHT);

		LOG_INFO("LightManager initialization is complete");
	}

	LightManager::~LightManager()
	{
		m_pSceneDirLightCB.Reset();
	}

	void LightManager::setDirLight(const DirectionLight & dirLight)
	{
		m_dirLight = dirLight;
		D3D11_MAPPED_SUBRESOURCE mappedData;
		m_pd3dImmediateContext->Map(m_pSceneDirLightCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
		memcpy_s(mappedData.pData, sizeof(DirectionLight), &dirLight, sizeof(DirectionLight));
		m_pd3dImmediateContext->Unmap(m_pSceneDirLightCB.Get(), 0);

		ShadowMapManager::getInstance().setViewMatrix(dirLight.direction);
	}
}


