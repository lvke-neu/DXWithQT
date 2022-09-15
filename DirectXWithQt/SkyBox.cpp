#include "SkyBox.h"
#include "d3dUtil.h"
#include <DirectXColors.h>
#include "RenderStates.h"

SkyBox::SkyBox(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext):
	GameObject(pd3dDevice, pd3dImmediateContext)
{
	m_pCacheRTV.Reset();
	m_pCacheDSV.Reset();
	m_pDynamicCubeMapDSV.Reset();
	m_pTexture.Reset();
	for (auto& ptr : m_pDynamicCubeMapRTVs)
	{
		ptr.Reset();
	}



	ComPtr<ID3D11Texture2D> texCube;
	D3D11_TEXTURE2D_DESC texDesc;

	texDesc.Width = 256;
	texDesc.Height = 256;
	texDesc.MipLevels = 0;
	texDesc.ArraySize = 6;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS | D3D11_RESOURCE_MISC_TEXTURECUBE;

	m_pd3dDevice->CreateTexture2D(&texDesc, nullptr, texCube.GetAddressOf());

	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	rtvDesc.Format = texDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;

	rtvDesc.Texture2DArray.ArraySize = 1;

	for (int i = 0; i < 6; ++i)
	{
		rtvDesc.Texture2DArray.FirstArraySlice = i;
		m_pd3dDevice->CreateRenderTargetView(texCube.Get(), &rtvDesc,
			m_pDynamicCubeMapRTVs[i].GetAddressOf());
	}



	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = texDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	srvDesc.TextureCube.MostDetailedMip = 0;
	srvDesc.TextureCube.MipLevels = -1;

	m_pd3dDevice->CreateShaderResourceView(texCube.Get(), &srvDesc,
		m_pTexture.GetAddressOf());


	texDesc.Width = 256;
	texDesc.Height = 256;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Format = DXGI_FORMAT_D32_FLOAT;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;

	ComPtr<ID3D11Texture2D> depthTex;
	m_pd3dDevice->CreateTexture2D(&texDesc, nullptr, depthTex.GetAddressOf());

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	dsvDesc.Format = texDesc.Format;
	dsvDesc.Flags = 0;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	m_pd3dDevice->CreateDepthStencilView(
		depthTex.Get(),
		&dsvDesc,
		m_pDynamicCubeMapDSV.GetAddressOf());


	m_camera.init(m_pd3dDevice, m_pd3dImmediateContext);
	D3D11_VIEWPORT viewPort;

	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = static_cast<float>(256);
	viewPort.Height = static_cast<float>(256);
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	m_camera.setViewPort(viewPort);



	m_pd3dImmediateContext->RSSetState(RenderStates::RSNoCull.Get());
	m_pd3dImmediateContext->OMSetDepthStencilState(RenderStates::DSSLessEqual.Get(), 0);

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

ComPtr<ID3D11ShaderResourceView> SkyBox::getDynamicSkyBoxSRV()
{
	return m_pDynamicCubeMapSRV;
}


void  SkyBox::Cache()
{
	m_pd3dImmediateContext->OMGetRenderTargets(1, m_pCacheRTV.GetAddressOf(), m_pCacheDSV.GetAddressOf());

	ID3D11ShaderResourceView* aa = nullptr;
	m_pd3dImmediateContext->PSSetShaderResources(3, 1, &aa);
}

void SkyBox::BeginCapture(const XMFLOAT3& pos, D3D11_TEXTURECUBE_FACE face, float nearZ, float farZ)
{
	static XMFLOAT3 ups[6] = {
		{ 0.0f, 1.0f, 0.0f },	// +X
		{ 0.0f, 1.0f, 0.0f },	// -X
		{ 0.0f, 0.0f, -1.0f },	// +Y
		{ 0.0f, 0.0f, 1.0f },	// -Y
		{ 0.0f, 1.0f, 0.0f },	// +Z
		{ 0.0f, 1.0f, 0.0f }	// -Z
	};

	static XMFLOAT3 looks[6] = {
		{ 1.0f, 0.0f, 0.0f },	// +X
		{ -1.0f, 0.0f, 0.0f },	// -X
		{ 0.0f, 1.0f, 0.0f },	// +Y
		{ 0.0f, -1.0f, 0.0f },	// -Y
		{ 0.0f, 0.0f, 1.0f },	// +Z
		{ 0.0f, 0.0f, -1.0f },	// -Z
	};


	m_camera.lookTo(pos, looks[face], ups[face]);

	m_camera.setFrustum(XM_PIDIV2, 1.0f, nearZ, farZ);

	m_pd3dImmediateContext->ClearRenderTargetView(m_pDynamicCubeMapRTVs[face].Get(), reinterpret_cast<const float*>(&Colors::Black));

	m_pd3dImmediateContext->OMSetRenderTargets(1, m_pDynamicCubeMapRTVs[face].GetAddressOf(), m_pDynamicCubeMapDSV.Get());

	D3D11_VIEWPORT viewPort = m_camera.getViewPort();
	m_pd3dImmediateContext->RSSetViewports(1, &viewPort);
}

void SkyBox::Restore(Camera& camera)
{

	D3D11_VIEWPORT viewPort = camera.getViewPort();
	m_pd3dImmediateContext->RSSetViewports(1, &viewPort);
	m_pd3dImmediateContext->OMSetRenderTargets(1, m_pCacheRTV.GetAddressOf(), m_pCacheDSV.Get());

	
	m_pd3dImmediateContext->GenerateMips(m_pTexture.Get());

	camera.changeViewMatrixCB();
	camera.changeProjMatrixCB();


	m_pd3dImmediateContext->PSSetShaderResources(3, 1, getDynamicSkyBoxSRV().GetAddressOf());


	m_pCacheDSV.Reset();
	m_pCacheRTV.Reset();
}