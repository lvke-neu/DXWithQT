#include "Chapter2Scene.h"

Chapter2Scene::Chapter2Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
	:m_pd3dDevice(pd3dDevice), m_pd3dImmediateContext(pd3dImmediateContext)
{


	m_perspectiveCamera.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, 10.0f)
	));
}

void Chapter2Scene::initScene()
{
	m_box = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_box.setMesh(Geometry::buildBoxMesh());
	m_box.setShader(2);
	m_box.setTexturePath(L"Texture\\WoodCrate.dds");
	m_box.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f)
		));



	bindCB2PipeLine();
}


void Chapter2Scene::updateScene(float deltaTime)
{
	//static float angle = 0;
	//angle += deltaTime;
	//m_box.getTransform().setRotation(XMFLOAT3(angle,0,0));

	//bindCB2PipeLine();

	static float angle = 0;
	angle += deltaTime;
	m_box.getTransform().setRotation(XMFLOAT3(angle, 0, 0));
}

void Chapter2Scene::drawScene()
{
	m_box.getTransform().setPosition(XMFLOAT3(-1.5f, 0.0f, 0.0f));
	bindCB2PipeLine();
	m_box.draw();


	m_box.getTransform().setPosition(XMFLOAT3(1.5f, 0.0f, 0.0f));
	bindCB2PipeLine();
	m_box.draw();
}

void Chapter2Scene::bindCB2PipeLine()
{
	WVPMatrixCB wvp;
	wvp.g_world = XMMatrixTranspose(m_box.getTransform().getWorldMatrix());
	wvp.g_view = XMMatrixTranspose(m_perspectiveCamera.getViewMatrix());
	wvp.g_proj = XMMatrixTranspose(m_perspectiveCamera.getProjMatrix());

	ComPtr<ID3D11Buffer> vsConstantBuffer;
	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.ByteWidth = sizeof(wvp);
	m_pd3dDevice->CreateBuffer(&cbd, nullptr, vsConstantBuffer.GetAddressOf());

	D3D11_MAPPED_SUBRESOURCE mappedData;
	m_pd3dImmediateContext->Map(vsConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
	memcpy_s(mappedData.pData, sizeof(WVPMatrixCB), &wvp, sizeof(WVPMatrixCB));
	m_pd3dImmediateContext->Unmap(vsConstantBuffer.Get(), 0);

	m_pd3dImmediateContext->VSSetConstantBuffers(0, 1, vsConstantBuffer.GetAddressOf());

}

void Chapter2Scene::changeTexture()
{
	static UINT num = 1;
	num += 1;
	
	switch (num % 11)
	{
	case 1:
		m_box.setTexturePath(L"Texture\\changeTexture\\1.dds");
		break;
	case 2:
		m_box.setTexturePath(L"Texture\\changeTexture\\2.dds");
		break;
	case 3:
		m_box.setTexturePath(L"Texture\\changeTexture\\3.dds");
		break;
	case 4:
		m_box.setTexturePath(L"Texture\\changeTexture\\4.dds");
		break;
	case 5:
		m_box.setTexturePath(L"Texture\\changeTexture\\5.dds");
		break;
	case 6:
		m_box.setTexturePath(L"Texture\\changeTexture\\6.dds");
		break;
	case 7:
		m_box.setTexturePath(L"Texture\\changeTexture\\7.dds");
		break;
	case 8:
		m_box.setTexturePath(L"Texture\\changeTexture\\8.dds");
		break;
	case 9:
		m_box.setTexturePath(L"Texture\\changeTexture\\9.dds");
		break;
	case 10:
		m_box.setTexturePath(L"Texture\\changeTexture\\10.dds");
		break;
	default:
		break;
	}

}