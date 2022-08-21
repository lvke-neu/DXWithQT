#include "SceneInterface.h"


void IScene::initCameraAndLight(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
{

	m_pd3dDevice = pd3dDevice;
	m_pd3dImmediateContext = pd3dImmediateContext;

	//light
	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.ByteWidth = sizeof(DirectionLight);
	m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pLightCB.GetAddressOf());
	m_pd3dImmediateContext->PSSetConstantBuffers(4, 1, m_pLightCB.GetAddressOf());
	setDirLight(m_dirLight_dir);

	//camera
	m_perspectiveCamera.init(m_pd3dDevice, m_pd3dImmediateContext);
	m_perspectiveCamera.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, -20.0f)
	));
}

IScene::~IScene()
{
	m_pLightCB.Reset();
}

void IScene::onResize(float width, float height, const D3D11_VIEWPORT& viewPort)
{
	m_perspectiveCamera.setFrustum(XM_PI / 3, static_cast<float>(width) / height, 0.5f, 1000.0f);
	m_perspectiveCamera.setViewPort(viewPort);
}