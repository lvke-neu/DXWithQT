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
	//m_pd3dImmediateContext->RSSetState(RenderStates::RSWireframe.Get());

	srand(time(0));
	for (UINT32 i = 0; i < RAND_TREE_NUM; i++)
	{
		m_randX[i] = rand() % 800 - 100;
		m_randZ[i] = rand() % 800 - 100;
	}

	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.ByteWidth = sizeof(Fog);
	m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pFogCB.GetAddressOf());

	m_pd3dImmediateContext->VSSetConstantBuffers(5, 1, m_pFogCB.GetAddressOf());
	m_pd3dImmediateContext->PSSetConstantBuffers(5, 1, m_pFogCB.GetAddressOf());

	setFogEnabled(true);

}


void Chapter7Scene::initScene()
{

	ObjReader objReader1;
	objReader1.ReadObj(L"Model\\house.obj");
	m_house = ModelObject(objReader1, m_pd3dDevice, m_pd3dImmediateContext);
	m_house.setShader(SceneShader::shaderPath[6]);
	m_house.setTransform(Transform(
		XMFLOAT3(0.1f, 0.1f, 0.1f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(-2.0f, -5.0f, 0.0f)
	));

	ObjReader objReader2;
	objReader2.ReadObj(L"Model\\tree.obj");

	for (UINT32 i = 0; i < RAND_TREE_NUM; i++)
	{
		ModelObject tree(objReader2, m_pd3dDevice, m_pd3dImmediateContext);
		tree.setShader(SceneShader::shaderPath[6]);
		tree.setTransform(Transform(
			XMFLOAT3(0.1f, 0.1f, 0.1f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(m_randX[i], -5.0f, m_randZ[i])
		));
		m_trees.push_back(tree);
	}

	Material material;
	material.ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 250.0f);

	m_plane = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_plane.setMesh(Geometry::buildPlaneMesh(10.0f, 10.0f));
	m_plane.setShader(SceneShader::shaderPath[6]);
	m_plane.setTexture(L"Texture\\grass.dds");
	m_plane.setMaterial(material);
	m_plane.setTransform(Transform(
		XMFLOAT3(1000.0f, 1000.0f, 1000.0f),
		XMFLOAT3(XM_PI / 2, 0.0f, 0.0f),
		XMFLOAT3(0.0f, -5.0f, 0.0f)
	));


	m_box1 = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_box1.setMesh(Geometry::buildBoxMesh());
	m_box1.setShader(SceneShader::shaderPath[6]);
	m_box1.setTexture(L"Texture\\WoodCrate.dds");
	m_box1.setMaterial(material);
	m_box1.setTransform(Transform(
		XMFLOAT3(5.0f, 5.0f, 5.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(70.0f, 5.0f, 0.0f)
	));
}


void Chapter7Scene::updateScene(float deltaTime)
{

	if (KeyBoard::getInstance().isKeyPress('W'))
	{
		m_perspectiveCamera.moveZAxis(deltaTime * 80);
		notifyAll();
	}
	if (KeyBoard::getInstance().isKeyPress('S'))
	{
		m_perspectiveCamera.moveZAxis(-deltaTime * 80);
		notifyAll();
	}
	if (KeyBoard::getInstance().isKeyPress('A'))
	{
		m_perspectiveCamera.moveXAxis(-deltaTime * 80);
		notifyAll();
	}
	if (KeyBoard::getInstance().isKeyPress('D'))
	{
		m_perspectiveCamera.moveXAxis(deltaTime * 80);
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


	static float roty = 0.0f;
	roty += deltaTime;
	m_box1.setRotation(0.0f, roty, 0.0f);

}

void Chapter7Scene::drawScene()
{
	m_house.draw();
	

	for (UINT16 i = 0; i < RAND_TREE_NUM; i++)
	{

		//Frustum Culling
		if (m_enableFrustumCulling)
		{
			BoundingBox worldBoundingBox;
			BoundingBox localBoundingBox = m_trees[i].getBoundingBox();
			localBoundingBox.Transform(worldBoundingBox, m_trees[i].getTransform().getWorldMatrix());
			if (!m_perspectiveCamera.isNeedFrustumCulling(worldBoundingBox))
				m_trees[i].draw();
		}
		else
		{
			m_trees[i].draw();
		}
	}

	m_box1.draw();
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
	ListeningEventManager::getInstance().notifyAll(msg);

}

void Chapter7Scene::setFogEnabled(bool b)
{
	Fog fog;
	fog.fogColor = XMFLOAT4(0.75f, 0.75f, 0.75f, 1.0f);
	fog.fogEnabled = b;
	fog.fogStart = 15.0f;
	fog.fogRange = 1500.0f;


	D3D11_MAPPED_SUBRESOURCE mappedData;
	m_pd3dImmediateContext->Map(m_pFogCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
	memcpy_s(mappedData.pData, sizeof(Fog), &fog, sizeof(Fog));
	m_pd3dImmediateContext->Unmap(m_pFogCB.Get(), 0);
}

void Chapter7Scene::setFogRange(float range)
{
	Fog fog;
	fog.fogColor = XMFLOAT4(0.75f, 0.75f, 0.75f, 1.0f);
	fog.fogEnabled = true;
	fog.fogStart = 15.0f;
	fog.fogRange = range;

	D3D11_MAPPED_SUBRESOURCE mappedData;
	m_pd3dImmediateContext->Map(m_pFogCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
	memcpy_s(mappedData.pData, sizeof(Fog), &fog, sizeof(Fog));
	m_pd3dImmediateContext->Unmap(m_pFogCB.Get(), 0);
}

void Chapter7Scene::setWireframe(bool b)
{
	if (b)
		m_pd3dImmediateContext->RSSetState(RenderStates::RSWireframe.Get());
	else
		m_pd3dImmediateContext->RSSetState(nullptr);
}