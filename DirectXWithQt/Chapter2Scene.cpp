#include "Chapter2Scene.h"
#include "KeyBoard.h"
#include "Mouse.h"



Chapter2Scene::Chapter2Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
	:m_pd3dDevice(pd3dDevice), m_pd3dImmediateContext(pd3dImmediateContext)
{
	//light and material
	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.ByteWidth = sizeof(LightAndMaterial);
	m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_plightAndMaterialCB.GetAddressOf());

	//camera
	m_perspectiveCamera.init(m_pd3dDevice, m_pd3dImmediateContext);
	m_perspectiveCamera.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, -20.0f)
	));
}

void Chapter2Scene::initScene()
{

	set_light_material();

	m_box = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_box.setMesh(Geometry::buildBoxMesh());
	m_box.setShader(2);
	m_box.setTexturePath(L"Texture\\WoodCrate.dds");
	m_box.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f)
		));

	m_plane = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_plane.setMesh(Geometry::buildPlaneMesh(10.0f, 10.0f));
	m_plane.setShader(2);
	m_plane.setTexturePath(L"Texture\\grass.dds");
	m_plane.setTransform(Transform(
		XMFLOAT3(10.0f, 10.0f, 10.0f),
		XMFLOAT3(XM_PI/2, 0.0f, 0.0f),
		XMFLOAT3(0.0f, -5.0f, 0.0f)
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


	if (Mouse::m_whichButton == RightButton)
	{
		float deltaX;
		float deltaY;
		deltaX = m_perspectiveCamera.getRotation().y + Mouse::m_delta.m_x * deltaTime * 10;
		deltaY = m_perspectiveCamera.getRotation().x + Mouse::m_delta.m_y * deltaTime * 10;
		m_perspectiveCamera.setRotation(deltaY, deltaX, 0.0f);

	}

	static float x = 0.0f;
	static float y = 0.0f;
	x += deltaTime * 0.5;
	y += deltaTime * 0.5;
	m_box.setRotation(x, 0.0f, 0.0f);
	

}

void Chapter2Scene::drawScene()
{
	m_box.setPosition(-1.5f, 0.0f, 0.0f);
	m_box.draw();

	m_box.setPosition(1.5f, 0.0f, 0.0f);
	m_box.draw();

	m_plane.draw();
}

void Chapter2Scene::set_light_material()
{
	LightAndMaterial lightAndMaterial;

	lightAndMaterial.directionLight.ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	lightAndMaterial.directionLight.diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	lightAndMaterial.directionLight.specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	lightAndMaterial.directionLight.direction = XMFLOAT3(0.0f, m_lightDir_y, 0.5f);

	lightAndMaterial.material.ambient  = m_ambient;
	lightAndMaterial.material.diffuse  = m_diffuse;
	lightAndMaterial.material.specular = m_specula;

	D3D11_MAPPED_SUBRESOURCE mappedData;
	m_pd3dImmediateContext->Map(m_plightAndMaterialCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
	memcpy_s(mappedData.pData, sizeof(LightAndMaterial), &lightAndMaterial, sizeof(LightAndMaterial));
	m_pd3dImmediateContext->Unmap(m_plightAndMaterialCB.Get(), 0);

	m_pd3dImmediateContext->PSSetConstantBuffers(3, 1, m_plightAndMaterialCB.GetAddressOf());
}



void Chapter2Scene::changeBoxTexture()
{
	static UINT num1 = 1;
	num1 += 1;
	
	switch (num1 % 11)
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

void Chapter2Scene::changeFloorTexture()
{
	static UINT num2 = 1;
	num2 += 1;

	switch (num2 % 11)
	{
	case 1:
		m_plane.setTexturePath(L"Texture\\changeTexture\\1.dds");
		break;
	case 2:
		m_plane.setTexturePath(L"Texture\\changeTexture\\2.dds");
		break;
	case 3:
		m_plane.setTexturePath(L"Texture\\changeTexture\\3.dds");
		break;
	case 4:
		m_plane.setTexturePath(L"Texture\\changeTexture\\4.dds");
		break;
	case 5:
		m_plane.setTexturePath(L"Texture\\changeTexture\\5.dds");
		break;
	case 6:
		m_plane.setTexturePath(L"Texture\\changeTexture\\6.dds");
		break;
	case 7:
		m_plane.setTexturePath(L"Texture\\changeTexture\\7.dds");
		break;
	case 8:
		m_plane.setTexturePath(L"Texture\\changeTexture\\8.dds");
		break;
	case 9:
		m_plane.setTexturePath(L"Texture\\changeTexture\\9.dds");
		break;
	case 10:
		m_plane.setTexturePath(L"Texture\\changeTexture\\10.dds");
		break;
	default:
		break;
	}

}