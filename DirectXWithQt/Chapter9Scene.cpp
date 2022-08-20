#include "Chapter9Scene.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include <string>
#include "RenderStates.h"


Chapter9Scene::Chapter9Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
{
	
	initCameraAndLight(pd3dDevice, pd3dImmediateContext);
	setDirLight(XMFLOAT3(0.0f, -0.5f, 0.5f));
	m_perspectiveCamera.setPosition(0.0f, 15.0f, 0.0f);


	m_pd3dImmediateContext->RSSetState(RenderStates::RSNoCull.Get());
	m_pd3dImmediateContext->OMSetDepthStencilState(RenderStates::DSSLessEqual.Get(), 0);

	//m_pd3dImmediateContext->RSSetState(RenderStates::RSWireframe.Get());
}


void Chapter9Scene::initScene()
{
	Material material;
	material.ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	material.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 5.0f);

	m_box1 = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_box1.setMesh(Geometry::buildBoxMesh());
	m_box1.setShader(9);
	m_box1.setTexturePathDDS(L"Texture\\WoodCrate.dds");
	m_box1.setMaterial(material);
	m_box1.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f)
		));

	
	m_sphere = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_sphere.setMesh(Geometry::buildSphereMesh());
	m_sphere.setShader(9);
	m_sphere.setTexturePathDDS(L"Texture\\stone.dds");
	m_sphere.setMaterial(material);
	m_sphere.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(5.0f, 0.0f, 0.0f)
	));

	m_terrain = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_terrain.setMesh(Geometry::buildTerrainMesh(160,160, 500,500));
	m_terrain.setShader(9);
	m_terrain.setTexturePathDDS(L"Texture\\grass.dds");
	m_terrain.setMaterial(material);
	m_terrain.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(5.0f, -10.0f, 0.0f)
	));

	m_skyBox = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_skyBox.setMesh(Geometry::buildBoxMesh());
	m_skyBox.setSkyBoxShader();
	m_skyBox.setSkyBoxTexture(L"Texture\\SkyBox\\daylight.jpg");
	m_skyBox.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f)
	));
}


void Chapter9Scene::updateScene(float deltaTime)
{
	bool isMove = false;

	UINT mulSpeed = 50;

	if (KeyBoard::getInstance().isKeyPress('W'))
	{
		m_perspectiveCamera.moveZAxis(deltaTime * mulSpeed);
		isMove = true;
	}
	if (KeyBoard::getInstance().isKeyPress('S'))
	{
		m_perspectiveCamera.moveZAxis(-deltaTime * mulSpeed);
		isMove = true;
	}
	if (KeyBoard::getInstance().isKeyPress('A'))
	{
		m_perspectiveCamera.moveXAxis(-deltaTime * mulSpeed);
		isMove = true;
	}
	if (KeyBoard::getInstance().isKeyPress('D'))
	{
		m_perspectiveCamera.moveXAxis(deltaTime * mulSpeed);
		isMove = true;
	}


	if (Mouse::m_whichButton == RightButton)
	{
		float deltaX;
		float deltaY;
		deltaX = m_perspectiveCamera.getRotation().y + Mouse::m_delta.m_x * deltaTime * 10;
		deltaY = m_perspectiveCamera.getRotation().x + Mouse::m_delta.m_y * deltaTime * 10;
		m_perspectiveCamera.setRotation(deltaY, deltaX, 0.0f);
		isMove = true;
	}

	if (isMove)
	{
		notifyAll();
	}

	if (KeyBoard::getInstance().isKeyPress('1'))
	{
		m_skyBox.setSkyBoxTexture(L"Texture\\SkyBox\\daylight.jpg");
	}
	
	if (KeyBoard::getInstance().isKeyPress('2'))
	{
		m_skyBox.setSkyBoxTexture(L"Texture\\SkyBox\\desertcube1024.dds");
	}

	if (KeyBoard::getInstance().isKeyPress('3'))
	{
		m_skyBox.setSkyBoxTexture(std::vector<std::wstring>
		{
			L"Texture\\SkyBox\\sunset_posX.bmp", L"Texture\\SkyBox\\sunset_negX.bmp",
			L"Texture\\SkyBox\\sunset_posY.bmp", L"Texture\\SkyBox\\sunset_negY.bmp",
			L"Texture\\SkyBox\\sunset_posZ.bmp", L"Texture\\SkyBox\\sunset_negZ.bmp", 
		});
	}

	static float rotx = 0.0f;
	rotx += deltaTime;
	m_box1.setRotation(rotx, 0.0f, 0.0f);


	static float posY = 0.0f;
	static bool b = true;
	if (b)
		posY += deltaTime * 2;
	else
		posY -= deltaTime * 2;

	if (posY > 2)
		b = false;
	if (posY < -2)
		b = true;

	m_sphere.setPosition(m_sphere.getPosition().x, posY, m_sphere.getPosition().z);

	static bool currentStateLow = 0;
	static bool currentStatehigh = 0;
	if (m_perspectiveCamera.getPosition().y < 10 )
	{
		if (currentStateLow == 0)
		{
			m_terrain.setMesh(Geometry::buildTerrainMesh(160, 160, 100, 100));
			currentStateLow = 1;
			currentStatehigh = 0;
		}

	}
		
	if (m_perspectiveCamera.getPosition().y > 10 )
	{
		if (currentStatehigh == 0)
		{
			m_terrain.setMesh(Geometry::buildTerrainMesh(160, 160, 25, 25));
			currentStatehigh = 1;
			currentStateLow = 0;
		}

	}

}

void Chapter9Scene::drawScene()
{
	m_box1.draw();
	m_sphere.draw();
	m_terrain.draw();
	m_skyBox.drawSkyBox(m_perspectiveCamera);
}




void Chapter9Scene::setDirLight(XMFLOAT3 dir)
{
	DirectionLight directionLight;

	directionLight.ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	directionLight.diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	directionLight.specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	directionLight.direction = dir;

	D3D11_MAPPED_SUBRESOURCE mappedData;
	m_pd3dImmediateContext->Map(m_pLightCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
	memcpy_s(mappedData.pData, sizeof(DirectionLight), &directionLight, sizeof(DirectionLight));
	m_pd3dImmediateContext->Unmap(m_pLightCB.Get(), 0);

	m_pd3dImmediateContext->PSSetConstantBuffers(4, 1, m_pLightCB.GetAddressOf());
}


void Chapter9Scene::notifyAll()
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
	ListeningEvent::notifyAll(msg);

}

