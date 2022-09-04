#include "Chapter10Scene.h"
#include "RenderStates.h"


Chapter10Scene::Chapter10Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
{
	initCameraAndLight(pd3dDevice, pd3dImmediateContext);
	setDirLight(XMFLOAT3(0.0f, -0.5f, 0.5f));

}


void Chapter10Scene::initScene()
{
	Material material;
	material.ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 250.0f);

	m_box1 = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_box1.setMesh(Geometry::buildBoxMesh());
	m_box1.setShader(SceneShader::shaderPath[9]);
	m_box1.setTexture(L"Texture\\WoodCrate.dds");
	m_box1.setMaterial(material);
	m_box1.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(-2.0f, 0.0f, 0.0f)
		));


	std::vector<std::wstring> normalMapShader =
	{
		L"Shader\\Chapter 10\\NormalMapVS.hlsl",
		L"Shader\\Chapter 10\\NormalMapPS.hlsl"
	};
	m_plane = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_plane.setMesh2(Geometry2::buildPlaneMesh(10.0f, 10.0f));
	m_plane.setShader(normalMapShader, VertexPosNormalTangentTex::inputLayout, 4);
	m_plane.setTexture(L"Texture\\stones.dds");
	m_plane.setNormalTexture(L"Texture\\stones_nmap.dds");
	m_plane.setMaterial(material);
	m_plane.setTransform(Transform(
		XMFLOAT3(100.0f, 100.0f, 100.0f),
		XMFLOAT3(XM_PI / 2, 0.0f, 0.0f),
		XMFLOAT3(0.0f, -5.0f, 0.0f)
	));

}


void Chapter10Scene::updateScene(float deltaTime)
{
	cameraControl(deltaTime);



	if (KeyBoard::getInstance().isKeyPress('N') && !m_enableNormalMap)
	{
		m_enableNormalMap = true;
	
		std::vector<std::wstring> normalMapShader =
		{
			L"Shader\\Chapter 10\\NormalMapVS.hlsl",
			L"Shader\\Chapter 10\\NormalMapPS.hlsl"
		};

		m_plane.setMesh2(Geometry2::buildPlaneMesh(10.0f, 10.0f));
		m_plane.setShader(normalMapShader, VertexPosNormalTangentTex::inputLayout, 4);
		m_plane.setNormalTexture(L"Texture\\stones_nmap.dds");
	}

	if (KeyBoard::getInstance().isKeyPress('C') && m_enableNormalMap)
	{
		m_enableNormalMap = false;
		m_plane.setMesh(Geometry::buildPlaneMesh(10.0f, 10.0f));
		m_plane.setShader(SceneShader::shaderPath[9]);
	}
}

void Chapter10Scene::drawScene()
{
	
	m_box1.draw();
	if (m_enableNormalMap)
		m_plane.draw2();
	else
		m_plane.draw();

}


void Chapter10Scene::setDirLight(XMFLOAT3 dir)
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
