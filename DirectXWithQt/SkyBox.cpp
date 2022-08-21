#include "SkyBox.h"
#include "d3dUtil.h"

SkyBox::SkyBox(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext):
	GameObject(pd3dDevice, pd3dImmediateContext)
{

}

void SkyBox::setTexture(const std::wstring& cubemapFilename, bool generateMips)
{
	m_pTexture.Reset();

	if (cubemapFilename.substr(cubemapFilename.size() - 3) == L"dds")
	{
		CreateDDSTextureFromFile(m_pd3dDevice.Get(),
			generateMips ? m_pd3dImmediateContext.Get() : nullptr,
			cubemapFilename.c_str(),
			nullptr,
			m_pTexture.GetAddressOf());
	}
	else
	{
		CreateWICTexture2DCubeFromFile(m_pd3dDevice.Get(),
			m_pd3dImmediateContext.Get(),
			cubemapFilename,
			nullptr,
			m_pTexture.GetAddressOf(),
			generateMips);
	}
}

void SkyBox::setTexture(const std::vector<std::wstring>& cubemapFilenames, bool generateMips)
{
	m_pTexture.Reset();

	CreateWICTexture2DCubeFromFile(m_pd3dDevice.Get(),
		m_pd3dImmediateContext.Get(),
		cubemapFilenames,
		nullptr,
		m_pTexture.GetAddressOf(),
		generateMips);
}

void SkyBox::draw(Camera& camera)
{
	XMMATRIX V = camera.getViewMatrix();
	V.r[3] = g_XMIdentityR3;
	camera.changeViewMatrixCB(V);
	GameObject::draw();
	camera.changeViewMatrixCB();
}

ComPtr<ID3D11ShaderResourceView> SkyBox::getSkyBoxSRV()
{
	return m_pTexture;
}