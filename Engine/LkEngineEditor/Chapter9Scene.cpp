#include "Chapter9Scene.h"
#include <string>

#include <DirectXColors.h>

Chapter9Scene::Chapter9Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext,
	ComPtr<ID3D11RenderTargetView> pRenderTargetView,
	ComPtr<ID3D11DepthStencilView> pDepthStencilView):m_pRenderTargetView(pRenderTargetView), m_pDepthStencilView(pDepthStencilView)
{
	
	initCameraAndLight(pd3dDevice, pd3dImmediateContext);
	setDirLight(XMFLOAT3(0.0f, -0.5f, 0.0f));
	



	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.ByteWidth = sizeof(EnableReflect);
	m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pEnableReflect.GetAddressOf());

	m_pd3dImmediateContext->VSSetConstantBuffers(5, 1, m_pEnableReflect.GetAddressOf());
	m_pd3dImmediateContext->PSSetConstantBuffers(5, 1, m_pEnableReflect.GetAddressOf());

	setReflect(true);
}


void Chapter9Scene::initScene()
{
	m_skyBox = SkyBox(m_pd3dDevice, m_pd3dImmediateContext);
	m_skyBox.setMesh(Geometry::buildBoxMesh());
	m_skyBox.setShader(std::vector<std::wstring>(
		{
			L"Shader\\SkyBox\\SkyBoxVS.hlsl",
			L"Shader\\SkyBox\\SkyBoxPS.hlsl"
		}
	));
	m_skyBox.setTexture(L"Texture\\SkyBox\\daylight.jpg");
	m_skyBox.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f)
	));

	Material material;
	material.ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	material.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 5.0f);

	m_box1 = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_box1.setMesh(Geometry::buildBoxMesh());
	m_box1.setShader(SceneShader::shaderPath[8]);
	m_box1.setTexture(L"Texture\\WoodCrate.dds");
	m_box1.setMaterial(material);
	m_box1.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(-5.0f, 0.0f, 0.0f)
		));

	m_terrain = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_terrain.setMesh(Geometry::buildTerrainMesh(160, 160, 500, 500));
	m_terrain.setShader(SceneShader::shaderPath[8]);
	m_terrain.setTexture(L"Texture\\grass.dds");
	m_terrain.setMaterial(material);
	m_terrain.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(5.0f, -10.0f, 0.0f)
	));

	material.reflect = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	m_sphere = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_sphere.setMesh(Geometry::buildSphereMesh());
	m_sphere.setShader(SceneShader::shaderPath[8]);
	m_sphere.setTexture(L"Texture\\stone.dds");
	m_sphere.setReflectTexture(m_skyBox.getSkyBoxSRV());
	m_sphere.setMaterial(material);
	m_sphere.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f)
	));

}


void Chapter9Scene::updateScene(float deltaTime)
{
	cameraControl(deltaTime);

	if (KeyBoard::getInstance().isKeyPress('1'))
	{
		m_skyBox.setTexture(L"Texture\\SkyBox\\daylight.jpg");
		m_sphere.setReflectTexture(m_skyBox.getSkyBoxSRV());
	}
	
	if (KeyBoard::getInstance().isKeyPress('2'))
	{
		m_skyBox.setTexture(L"Texture\\SkyBox\\desertcube1024.dds");
		m_sphere.setReflectTexture(m_skyBox.getSkyBoxSRV());
	}

	if (KeyBoard::getInstance().isKeyPress('3'))
	{
		m_skyBox.setTexture(std::vector<std::wstring>
		{
			L"Texture\\SkyBox\\sunset_posX.bmp", L"Texture\\SkyBox\\sunset_negX.bmp",
			L"Texture\\SkyBox\\sunset_posY.bmp", L"Texture\\SkyBox\\sunset_negY.bmp",
			L"Texture\\SkyBox\\sunset_posZ.bmp", L"Texture\\SkyBox\\sunset_negZ.bmp", 
		});
		m_sphere.setReflectTexture(m_skyBox.getSkyBoxSRV());
	}

	if (KeyBoard::getInstance().isKeyPress('R'))
	{
		setReflect(true);
	}
	if (KeyBoard::getInstance().isKeyPress('F'))
	{
		setReflect(false);
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


	//m_skyBox.Cache();
	//for (int i = 0; i < 6; ++i)
	//{
	//	m_skyBox.BeginCapture(XMFLOAT3(), static_cast<D3D11_TEXTURECUBE_FACE>(i));

	//	m_box1.draw();

	//	m_terrain.draw();

	//	m_skyBox.draw(m_skyBox.m_camera);

	//	
	//}
	//m_skyBox.Restore(m_perspectiveCamera);
	//

	//m_pd3dImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), reinterpret_cast<const float*>(&Colors::Black));
	//m_pd3dImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	m_box1.draw();

	m_terrain.draw();

	m_sphere.draw();

	m_skyBox.draw(m_perspectiveCamera);

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


void Chapter9Scene::setReflect(bool b)
{
	EnableReflect enableReflect;
	enableReflect.g_ReflectionEnabled = b;


	D3D11_MAPPED_SUBRESOURCE mappedData;
	m_pd3dImmediateContext->Map(m_pEnableReflect.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
	memcpy_s(mappedData.pData, sizeof(EnableReflect), &enableReflect, sizeof(EnableReflect));
	m_pd3dImmediateContext->Unmap(m_pEnableReflect.Get(), 0);
}