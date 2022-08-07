#include "Chapter7Scene.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include <string>
#include "RenderStates.h"


Chapter7Scene::Chapter7Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
{
	
	initCameraAndLight(pd3dDevice, pd3dImmediateContext);
	m_perspectiveCamera.setPosition(0.7f, 11.0f, -69.f);
	m_pd3dImmediateContext->RSSetState(RenderStates::RSNoCull.Get());
}


void Chapter7Scene::initScene()
{

	m_house = ModelObject(L"Model\\house.mbo", L"Model\\house.obj", m_pd3dDevice, m_pd3dImmediateContext);
	m_house.setShader(7);
	m_house.setTransform(Transform(
		XMFLOAT3(0.1f, 0.1f, 0.1f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(-2.0f, -5.0f, 0.0f)
	));

	Material material;
	material.ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 250.0f);

	m_plane = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_plane.setMesh(Geometry::buildPlaneMesh(10.0f, 10.0f));
	m_plane.setShader(7);
	m_plane.setTexturePath(L"Texture\\grass.dds");
	m_plane.setMaterial(material);
	m_plane.setTransform(Transform(
		XMFLOAT3(100.0f, 100.0f, 100.0f),
		XMFLOAT3(XM_PI / 2, 0.0f, 0.0f),
		XMFLOAT3(0.0f, -5.0f, 0.0f)
	));
}


void Chapter7Scene::updateScene(float deltaTime)
{

	if (KeyBoard::getInstance().isKeyPress('W'))
	{
		m_perspectiveCamera.moveZAxis(deltaTime * 40);
		notifyAll();
	}
	if (KeyBoard::getInstance().isKeyPress('S'))
	{
		m_perspectiveCamera.moveZAxis(-deltaTime * 40);
		notifyAll();
	}
	if (KeyBoard::getInstance().isKeyPress('A'))
	{
		m_perspectiveCamera.moveXAxis(-deltaTime * 40);
		notifyAll();
	}
	if (KeyBoard::getInstance().isKeyPress('D'))
	{
		m_perspectiveCamera.moveXAxis(deltaTime * 40);
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



}

void Chapter7Scene::drawScene()
{
	m_house.draw();
	m_plane.draw();
}




void Chapter7Scene::setDirLight(XMFLOAT3 dir)
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

void Chapter7Scene::notifyAll()
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

