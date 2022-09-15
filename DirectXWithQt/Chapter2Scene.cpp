#include "Chapter2Scene.h"
#include "RenderStates.h"


Chapter2Scene::Chapter2Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
{
	initCameraAndLight(pd3dDevice, pd3dImmediateContext);
	setDirLight(XMFLOAT3(0.0f, -0.5f, 0.5f));

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


void Chapter2Scene::initScene()
{
	Material material;
	material.ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 250.0f);

	m_box1 = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_box1.setMesh(Geometry::buildBoxMesh());
	m_box1.setShader(SceneShader::shaderPath[1]);
	m_box1.setTexture(L"Texture\\WoodCrate.dds");
	m_box1.setMaterial(material);
	m_box1.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(-2.0f, 0.0f, 0.0f)
		));

	m_box2 = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_box2.setMesh(Geometry::buildBoxMesh());
	m_box2.setShader(SceneShader::shaderPath[1]);
	m_box2.setTexture(L"Texture\\WoodCrate.dds");
	m_box2.setMaterial(material);
	m_box2.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(2.0f, 0.0f, 0.0f)
	));

	m_box3 = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_box3.setMesh(Geometry::buildBoxMesh());
	m_box3.setShader(SceneShader::shaderPath[1]);
	m_box3.setTexture(L"Texture\\WoodCrate.dds");
	m_box3.setMaterial(material);
	m_box3.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(10.0f, -4.0f, 30.0f)
	));

	m_plane = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_plane.setMesh(Geometry::buildPlaneMesh(10.0f, 10.0f));
	m_plane.setShader(SceneShader::shaderPath[1]);
	m_plane.setTexture(L"Texture\\grass.dds");
	m_plane.setMaterial(material);
	m_plane.setTransform(Transform(
		XMFLOAT3(100.0f, 100.0f, 100.0f),
		XMFLOAT3(XM_PI/2, 0.0f, 0.0f),
		XMFLOAT3(0.0f, -5.0f, 0.0f)
	));
}


void Chapter2Scene::updateScene(float deltaTime)
{
	cameraControl(deltaTime);


	static float rotX = 0.0f;
	rotX += deltaTime;
	m_box1.setRotation(rotX, 0.0f, 0.0f);
	
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

	
	m_box2.setPosition(m_box2.getPosition().x, posY, m_box2.getPosition().z);
}

void Chapter2Scene::drawScene()
{
	
	//m_box1.draw();

	//m_box2.draw();

	//m_box3.draw();

	m_plane.draw();

	for (auto& x : m_effects)
	{
		x.draw();
	}
}




void Chapter2Scene::setDirLight(XMFLOAT3 dir)
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

void Chapter2Scene::changeBox1Texture()
{
	static UINT num1 = 1;
	num1 += 1;
	
	switch (num1 % 11)
	{
	case 1:
		m_box1.setTexture(L"Texture\\changeTexture\\1.dds");
		break;
	case 2:
		m_box1.setTexture(L"Texture\\changeTexture\\2.dds");
		break;
	case 3:
		m_box1.setTexture(L"Texture\\changeTexture\\3.dds");
		break;
	case 4:
		m_box1.setTexture(L"Texture\\changeTexture\\4.dds");
		break;
	case 5:
		m_box1.setTexture(L"Texture\\changeTexture\\5.dds");
		break;
	case 6:
		m_box1.setTexture(L"Texture\\changeTexture\\6.dds");
		break;
	case 7:
		m_box1.setTexture(L"Texture\\changeTexture\\7.dds");
		break;
	case 8:
		m_box1.setTexture(L"Texture\\changeTexture\\8.dds");
		break;
	case 9:
		m_box1.setTexture(L"Texture\\changeTexture\\9.dds");
		break;
	case 10:
		m_box1.setTexture(L"Texture\\changeTexture\\10.dds");
		break;
	default:
		break;
	}

}

void Chapter2Scene::changeBox2Texture()
{
	static UINT num2 = 1;
	num2 += 1;

	switch (num2 % 11)
	{
	case 1:
		m_box2.setTexture(L"Texture\\changeTexture\\1.dds");
		break;
	case 2:
		m_box2.setTexture(L"Texture\\changeTexture\\2.dds");
		break;
	case 3:
		m_box2.setTexture(L"Texture\\changeTexture\\3.dds");
		break;
	case 4:
		m_box2.setTexture(L"Texture\\changeTexture\\4.dds");
		break;
	case 5:
		m_box2.setTexture(L"Texture\\changeTexture\\5.dds");
		break;
	case 6:
		m_box2.setTexture(L"Texture\\changeTexture\\6.dds");
		break;
	case 7:
		m_box2.setTexture(L"Texture\\changeTexture\\7.dds");
		break;
	case 8:
		m_box2.setTexture(L"Texture\\changeTexture\\8.dds");
		break;
	case 9:
		m_box2.setTexture(L"Texture\\changeTexture\\9.dds");
		break;
	case 10:
		m_box2.setTexture(L"Texture\\changeTexture\\10.dds");
		break;
	default:
		break;
	}

}

void Chapter2Scene::changeFloorTexture()
{
	static UINT num3 = 1;
	num3 += 1;

	switch (num3 % 11)
	{
	case 1:
		m_plane.setTexture(L"Texture\\changeTexture\\1.dds");
		break;
	case 2:
		m_plane.setTexture(L"Texture\\changeTexture\\2.dds");
		break;
	case 3:
		m_plane.setTexture(L"Texture\\changeTexture\\3.dds");
		break;
	case 4:
		m_plane.setTexture(L"Texture\\changeTexture\\4.dds");
		break;
	case 5:
		m_plane.setTexture(L"Texture\\changeTexture\\5.dds");
		break;
	case 6:
		m_plane.setTexture(L"Texture\\changeTexture\\6.dds");
		break;
	case 7:
		m_plane.setTexture(L"Texture\\changeTexture\\7.dds");
		break;
	case 8:
		m_plane.setTexture(L"Texture\\changeTexture\\8.dds");
		break;
	case 9:
		m_plane.setTexture(L"Texture\\changeTexture\\9.dds");
		break;
	case 10:
		m_plane.setTexture(L"Texture\\changeTexture\\10.dds");
		break;
	default:
		break;
	}

}


void Chapter2Scene::setFogEnabled(bool b)
{
	m_enableFog = b;
	Fog fog;
	fog.fogColor = XMFLOAT4(0.75f, 0.75f, 0.75f, 1.0f);
	fog.fogEnabled = b;
	fog.fogStart = 15.0f;
	fog.fogRange = 75.0f;


	D3D11_MAPPED_SUBRESOURCE mappedData;
	m_pd3dImmediateContext->Map(m_pFogCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
	memcpy_s(mappedData.pData, sizeof(Fog), &fog, sizeof(Fog));
	m_pd3dImmediateContext->Unmap(m_pFogCB.Get(), 0);
}

void Chapter2Scene::setFogRange(float range)
{
	if (m_enableFog)
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
}



void Chapter2Scene::setWireframe(bool b)
{
	if(b)
		m_pd3dImmediateContext->RSSetState(RenderStates::RSWireframe.Get());
	else
		m_pd3dImmediateContext->RSSetState(nullptr);
}

void Chapter2Scene::setNoCull(bool b)
{
	if (b)
		m_pd3dImmediateContext->RSSetState(RenderStates::RSNoCull.Get());
	else
		m_pd3dImmediateContext->RSSetState(nullptr);
}
