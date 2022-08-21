#include "Chapter8Scene.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include <string>
#include "RenderStates.h"
#include "Ray.h"

Chapter8Scene::Chapter8Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
{
	
	initCameraAndLight(pd3dDevice, pd3dImmediateContext);
	m_perspectiveCamera.setPosition(0, 0, -5.0f);
	setDirLight(XMFLOAT3(0.0f, -0.5f, 0.5f));

	m_pd3dImmediateContext->RSSetState(RenderStates::RSNoCull.Get());
}


void Chapter8Scene::initScene()
{
	Material material;
	material.ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 250.0f);

	m_box1 = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_box1.setMesh(Geometry::buildBoxMesh());
	m_box1.setShader(SceneShader::shaderPath[7]);
	m_box1.setTexture(L"Texture\\WoodCrate.dds");
	m_box1.setMaterial(material);
	m_box1.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(4.0f, 0.0f, 10.0f)
		));

	m_box2 = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_box2.setMesh(Geometry::buildBoxMesh());
	m_box2.setShader(SceneShader::shaderPath[7]);
	m_box2.setTexture(L"Texture\\brick.dds");
	m_box2.setMaterial(material);
	m_box2.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(-4.0f, 0.0f, 10.0f)
	));

	m_rectangle = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_rectangle.setMesh(Geometry::builRectangleMesh());
	m_rectangle.setShader(SceneShader::shaderPath[7]);
	m_rectangle.setTexture(L"Texture\\flare.dds");
	m_rectangle.setMaterial(material);
	m_rectangle.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(0.0f, -4.0f, 5.0f)
	));


}


void Chapter8Scene::updateScene(float deltaTime)
{
	static float rot = 0.0f;
	rot += deltaTime;
	m_box1.setRotation(rot, 0.0f, 0.0f);
	m_box2.setRotation(0.0f, rot, 0.0f);
	m_rectangle.setRotation(0.0f, rot, 0.0f);

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

	Ray ray_camera2pickPoint = Ray::ScreenToRay(m_perspectiveCamera, Mouse::x, Mouse::y);

	float dis;
	BoundingBox aabb1,aabb2,aabb3;
	m_box1.getBoundingBox().Transform(aabb1, m_box1.getTransform().getWorldMatrix());
	m_box2.getBoundingBox().Transform(aabb2, m_box2.getTransform().getWorldMatrix());
	m_rectangle.getBoundingBox().Transform(aabb3, m_rectangle.getTransform().getWorldMatrix());


	if (ray_camera2pickPoint.hit(aabb1, dis))
	{
		ListeningEvent::notifyAll("Pick RightBox");
		if (Mouse::m_whichButton == LeftButton)
		{
			ListeningEvent::stopTimer();
			ListeningEvent::messaegeBox("Pick RightBox");
			ListeningEvent::startTimer();
			Mouse::m_whichButton = NoButton;

		}
	}
	else if (ray_camera2pickPoint.hit(aabb2, dis))
	{
		ListeningEvent::notifyAll("Pick LeftBox");
		if (Mouse::m_whichButton == LeftButton)
		{
			ListeningEvent::stopTimer();
			ListeningEvent::messaegeBox("Pick LeftBox");
			ListeningEvent::startTimer();
			Mouse::m_whichButton = NoButton;
		}
	}
	else if (ray_camera2pickPoint.hit(aabb3, dis))
	{
		ListeningEvent::notifyAll("Pick Rectangle");
		if (Mouse::m_whichButton == LeftButton)
		{
			ListeningEvent::stopTimer();
			ListeningEvent::messaegeBox("Pick Rectangle");
			ListeningEvent::startTimer();
			Mouse::m_whichButton = NoButton;
		}
	}
	else
	{
		ListeningEvent::notifyAll("Pick Null");
	}
	
}

void Chapter8Scene::drawScene()
{
	m_box1.draw();
	m_box2.draw();
	m_rectangle.draw();
}




void Chapter8Scene::setDirLight(XMFLOAT3 dir)
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

void Chapter8Scene::notifyAll()
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