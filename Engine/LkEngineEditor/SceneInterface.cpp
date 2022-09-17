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

void IScene::cameraControl(float deltaTime)
{
	if (KeyBoard::getInstance().isKeyPress('W'))
	{
		m_perspectiveCamera.moveZAxis(deltaTime * 20);
		notifyCameraMove();
	}
	if (KeyBoard::getInstance().isKeyPress('S'))
	{
		m_perspectiveCamera.moveZAxis(-deltaTime * 20);
		notifyCameraMove();
	}
	if (KeyBoard::getInstance().isKeyPress('A'))
	{
		m_perspectiveCamera.moveXAxis(-deltaTime * 20);
		notifyCameraMove();
	}
	if (KeyBoard::getInstance().isKeyPress('D'))
	{
		m_perspectiveCamera.moveXAxis(deltaTime * 20);
		notifyCameraMove();
	}


	if (Mouse::m_whichButton == RightButton)
	{
		float deltaX;
		float deltaY;
		deltaX = m_perspectiveCamera.getRotation().y + Mouse::m_delta.m_x * deltaTime * 10;
		deltaY = m_perspectiveCamera.getRotation().x + Mouse::m_delta.m_y * deltaTime * 10;
		m_perspectiveCamera.setRotation(deltaY, deltaX, 0.0f);
		notifyCameraMove();

	}
}

void IScene::notifyCameraMove()
{
	XMFLOAT3 rot = m_perspectiveCamera.getRotation();
	XMFLOAT3 pos = m_perspectiveCamera.getPosition();
	std::string msg;
	msg = "CameraRotation:\n" +
		std::to_string(rot.x) + ",\n" +
		std::to_string(rot.y) + ",\n" +
		std::to_string(rot.z);
	msg += "\nCameraPosition:\n" +
		std::to_string(pos.x) + ",\n" +
		std::to_string(pos.y) + ",\n" +
		std::to_string(pos.z);

	EventManager::getInstance().onCameraMove(msg);
}

void IScene::onResize(float width, float height, const D3D11_VIEWPORT& viewPort)
{
	m_perspectiveCamera.setFrustum(XM_PI / 3, static_cast<float>(width) / height, 0.5f, 1000.0f);
	m_perspectiveCamera.setViewPort(viewPort);
}