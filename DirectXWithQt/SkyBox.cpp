
#include "SkyBox.h"
#include "d3dUtil.h"

SkyBox::SkyBox(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext) :
	GameObject(pd3dDevice, pd3dImmediateContext)
{

}

void SkyBox::setSkyBoxTexture(const std::wstring& cubemapFilename, bool generateMips)
{
	CreateWICTexture2DCubeFromFile(m_pd3dDevice.Get(),
		m_pd3dImmediateContext.Get(),
		cubemapFilename,
		nullptr,
		m_pTexture.GetAddressOf(),
		generateMips);
}

