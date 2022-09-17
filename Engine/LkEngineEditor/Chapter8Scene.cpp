#include "Chapter8Scene.h"
#include "RenderStates.h"
#include "Ray.h"

Chapter8Scene::Chapter8Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
{
	
	initCameraAndLight(pd3dDevice, pd3dImmediateContext);
	m_perspectiveCamera.setPosition(11.0f, 0.0f, 0.1f);
	m_perspectiveCamera.setRotation(0.08f, -0.8f, 0.0f);
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
		XMFLOAT3(2.0f, 2.0f, 2.0f),
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
		XMFLOAT3(1.0f, 2.0f, 0.0f),
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
	//m_box1.setRotation(rot, 0.0f, 0.0f);
	//m_box2.setRotation(0.0f, rot, 0.0f);
	m_rectangle.setRotation(0.0f, rot, 0.0f);

	cameraControl(deltaTime);

	Ray ray_camera2pickPoint = Ray::ScreenToRay(m_perspectiveCamera, Mouse::x, Mouse::y);

	float dis;
	BoundingBox aabb1,aabb2,aabb3;
	m_box1.getBoundingBox().Transform(aabb1, m_box1.getTransform().getWorldMatrix());
	m_box2.getBoundingBox().Transform(aabb2, m_box2.getTransform().getWorldMatrix());
	m_rectangle.getBoundingBox().Transform(aabb3, m_rectangle.getTransform().getWorldMatrix());


	if (ray_camera2pickPoint.hit(aabb1, dis))
	{
		EventManager::getInstance().onMouseLocateGo("Box1");
		if (Mouse::m_whichButton == LeftButton)
		{
			EventManager::getInstance().onPickGameObject(m_box1);
		}
	}
	else if (ray_camera2pickPoint.hit(aabb2, dis))
	{
		EventManager::getInstance().onMouseLocateGo("Box2");
		if (Mouse::m_whichButton == LeftButton)
		{
			EventManager::getInstance().onPickGameObject(m_box2);
			
		}
	}
	else if (ray_camera2pickPoint.hit(aabb3, dis))
	{
		//EventManager::getInstance().onPickGameObject(m_rectangle);
		//if (Mouse::m_whichButton == LeftButton)
		//{
		//	ListeningEventManager::getInstance().stopTimer();
		//	ListeningEventManager::getInstance().messaegeBox("Pick Rectangle");
		//	ListeningEventManager::getInstance().startTimer();
		//	Mouse::m_whichButton = NoButton;
		//}
	}
	else
	{
		EventManager::getInstance().onMouseLocateGo("NULL");
		//ListeningEventManager::getInstance().notifyAll("Pick Null");
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

