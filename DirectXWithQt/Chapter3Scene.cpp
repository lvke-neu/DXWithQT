#include "Chapter3Scene.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include <string>
#include "RenderStates.h"

Chapter3Scene::Chapter3Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
{
	initCameraAndLight(pd3dDevice, pd3dImmediateContext);
	m_perspectiveCamera.setPosition(-9.75f, 2.03f, 1.69f);
	m_perspectiveCamera.setRotation(0.2f, 0.98f, 0.0f);
}

void Chapter3Scene::initScene()
{
	Material material;
	material.ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 250.0f);

	m_wall = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_wall.setMesh(Geometry::buildPlaneMesh(4.0f, 2.0f));
	m_wall.setShader(3);
	m_wall.setTexturePath(L"Texture\\brick.dds");
	m_wall.setMaterial(material);

	m_floor = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_floor.setMesh(Geometry::buildPlaneMesh(5.0f, 5.0f));
	m_floor.setShader(3);
	m_floor.setTexturePath(L"Texture\\floor.dds");
	m_floor.setMaterial(material);
	m_floor.setTransform(Transform(
		XMFLOAT3(10.0f, 10.0f, 1.0f),
		XMFLOAT3(XM_PI / 2, 0.0f, 0.0f),
		XMFLOAT3(0.0f, -5.0f, 10.0f)
	));


	material.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
	m_water = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_water.setMesh(Geometry::buildPlaneMesh(5.0f, 5.0f));
	m_water.setShader(3);
	m_water.setTexturePath(L"Texture\\water.dds");
	m_water.setMaterial(material);
	m_water.setTransform(Transform(
		XMFLOAT3(10.0f, 10.0f, 1.0f),
		XMFLOAT3(XM_PI / 2, 0.0f, 0.0f),
		XMFLOAT3(0.0f, -3.0f, 10.0f)
	));


	material.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_staticBox = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_staticBox.setMesh(Geometry::buildBoxMesh());
	m_staticBox.setShader(3);
	m_staticBox.setTexturePath(L"Texture\\WireFence.dds");
	m_staticBox.setMaterial(material);
	m_staticBox.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(2.0f, -3.0f, 7.0f)
	));
	m_dynamicBox = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_dynamicBox.setMesh(Geometry::buildBoxMesh());
	m_dynamicBox.setShader(3);
	m_dynamicBox.setTexturePath(L"Texture\\WireFence.dds");
	m_dynamicBox.setMaterial(material);
	m_dynamicBox.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(-2.0f, -3.0f, 7.0f)
	));

	m_pd3dImmediateContext->RSSetState(RenderStates::RSNoCull.Get());

}


void Chapter3Scene::updateScene(float deltaTime)
{

	if (KeyBoard::getInstance().isKeyPress('W'))
	{
		m_perspectiveCamera.moveZAxis(deltaTime * 20);
		notifyAll();

	}
	if (KeyBoard::getInstance().isKeyPress('S'))
	{
		m_perspectiveCamera.moveZAxis(-deltaTime * 20);
		notifyAll();

	}
	if (KeyBoard::getInstance().isKeyPress('A'))
	{
		m_perspectiveCamera.moveXAxis(-deltaTime * 20);
		notifyAll();

	}
	if (KeyBoard::getInstance().isKeyPress('D'))
	{
		m_perspectiveCamera.moveXAxis(deltaTime * 20);
		notifyAll();

	}


	if (Mouse::m_whichButton == RightButton)
	{
		float deltaX;
		float deltaY;
		deltaX = m_perspectiveCamera.getRotation().y + Mouse::m_delta.m_x * deltaTime * 10;
		deltaY = m_perspectiveCamera.getRotation().x + Mouse::m_delta.m_y * deltaTime * 10;
		m_perspectiveCamera.setRotation(deltaY, deltaX, 0.0f);
		notifyAll();
	}

	static float rotx = 0.0f;
	rotx += deltaTime;
	m_dynamicBox.setRotation(rotx, 0.0f, 0.0f);
	
}

void Chapter3Scene::drawScene()
{


	//前
	m_wall.setTransform(Transform(
		XMFLOAT3(10.0f, 5.0f, 1.0f),
		XMFLOAT3(0.0f, XM_PI, 0.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f)
	));
	m_wall.draw();

	//后
	m_wall.setTransform(Transform(
		XMFLOAT3(10.0f, 5.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, 20.0f)
	));
	m_wall.draw();

	//左
	m_wall.setTransform(Transform(
		XMFLOAT3(10.0f, 5.0f, 1.0f),
		XMFLOAT3(0.0f, -XM_PI/2, 0.0f),
		XMFLOAT3(-10.0f, 0.0f, 10.0f)
	));
	m_wall.draw();

	//右
	m_wall.setTransform(Transform(
		XMFLOAT3(10.0f, 5.0f, 1.0f),
		XMFLOAT3(0.0f, XM_PI / 2, 0.0f),
		XMFLOAT3(10.0f, 0.0f, 10.0f)
	));
	m_wall.draw();

	m_floor.draw();


	m_staticBox.draw();
	m_dynamicBox.draw();

	m_pd3dImmediateContext->OMSetBlendState(RenderStates::BSTransparent.Get(), nullptr, 0xFFFFFFFF);
	m_water.draw();
	m_pd3dImmediateContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);


}




void Chapter3Scene::setDirLight(XMFLOAT3 dir)
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


void Chapter3Scene::setWaterTransparency(float transparency)
{
	Material material;
	material.ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, transparency);
	material.specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 250.0f);

	m_water.setMaterial(material);
}

void Chapter3Scene::notifyAll()
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
