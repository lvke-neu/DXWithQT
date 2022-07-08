#include "Chapter2Scene.h"
#include "KeyBoard.h"
#include "Mouse.h"

Chapter2Scene::Chapter2Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
	:m_pd3dDevice(pd3dDevice), m_pd3dImmediateContext(pd3dImmediateContext)
{
	m_perspectiveCamera.init(m_pd3dDevice, m_pd3dImmediateContext);
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
}


void Chapter2Scene::updateScene(float deltaTime)
{

	if (KeyBoard::getInstance().isKeyPress('W'))
	{
		m_perspectiveCamera.moveZAxis(deltaTime * 10);
	}
	if (KeyBoard::getInstance().isKeyPress('S'))
	{
		m_perspectiveCamera.moveZAxis(-deltaTime * 10);
	}
	if (KeyBoard::getInstance().isKeyPress('A'))
	{
		m_perspectiveCamera.moveXAxis(-deltaTime * 10);
	}
	if (KeyBoard::getInstance().isKeyPress('D'))
	{
		m_perspectiveCamera.moveXAxis(deltaTime * 10);
	}
	//m_box.getTransform().setRotation(XMFLOAT3(angle, 0, 0));

	//m_perspectiveCamera.getTransform().setRotation(XMFLOAT3(0, angle, 0));
	static float deltaX = 0.0f;
	static float deltaY = 0.0f;
	deltaX += Mouse::getDeltaX() * deltaTime * 10;
	deltaY += Mouse::getDeltaY() * deltaTime * 10;
	m_perspectiveCamera.getTransform().setRotation(XMFLOAT3(deltaX, deltaY, 0.0f));
}

void Chapter2Scene::drawScene()
{
	m_box.getTransform().setPosition(XMFLOAT3(-1.5f, 0.0f, 0.0f));
	m_box.draw();

	m_box.getTransform().setPosition(XMFLOAT3(1.5f, 0.0f, 0.0f));
	m_box.draw();
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