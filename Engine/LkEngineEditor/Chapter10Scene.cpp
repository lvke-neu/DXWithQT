#include "Chapter10Scene.h"

#define PLANE_LENGTH_WIDHT 10

Chapter10Scene::Chapter10Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
{
	initCameraAndLight(pd3dDevice, pd3dImmediateContext);
	m_perspectiveCamera.setPosition(6.4f, 7.3f, -24.0f);
	setDirLight(XMFLOAT3(0.0f, -0.5f, 0.5f));
}


void Chapter10Scene::initScene()
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
	material.ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 250.0f);

	m_naruto = AssimpModelObject("Model\\2nrtbod1out\\2nrtbod1out.obj", m_pd3dDevice, m_pd3dImmediateContext);
	m_naruto.setShader(SceneShader::shaderPath[9]);
	m_naruto.setMaterial(material);
	m_naruto.setTransform(Transform(
		XMFLOAT3(0.1f, 0.1f, 0.1f),
		XMFLOAT3(XM_PI / 2, 0.0f, 0.0f),
		XMFLOAT3(4.0f, -4.0f, 0.0f)
	));

	
	m_madara = AssimpModelObject("Model\\Madara_Uchiha\\Madara_Uchiha.obj", m_pd3dDevice, m_pd3dImmediateContext);
	m_madara.setShader(SceneShader::shaderPath[9]);
	m_madara.setMaterial(material);
	m_madara.setTransform(Transform(
		XMFLOAT3(4.0f, 4.0f, 4.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(14.0f, -4.0f, 0.0f)
	));

	
	m_superman = AssimpModelObject("Model\\Superman\\1.obj", m_pd3dDevice, m_pd3dImmediateContext);
	m_superman.setShader(SceneShader::shaderPath[9]);
	m_superman.setMaterial(material);
	m_superman.setTransform(Transform(
		XMFLOAT3(10.0f, 10.0f, 10.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(-837.0f, -372.0f, 0.0f)
	));

	m_house = AssimpModelObject("Model\\House\\house.obj", m_pd3dDevice, m_pd3dImmediateContext);
	m_house.setShader(SceneShader::shaderPath[9]);
	m_house.setMaterial(material);
	m_house.setTransform(Transform(
		XMFLOAT3(0.1f, 0.1f, 0.1f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(0.0f, -5.0f, 50.0f)
	));

	m_tree = AssimpModelObject("Model\\Tree\\tree.obj", m_pd3dDevice, m_pd3dImmediateContext);
	m_tree.setShader(SceneShader::shaderPath[9]);
	m_tree.setMaterial(material);
	m_tree.setTransform(Transform(
		XMFLOAT3(0.1f, 0.1f, 0.1f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(10.0f, -5.0f, 20.0f)
	));



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
	m_plane.setMesh2(Geometry2::buildPlaneMesh(PLANE_LENGTH_WIDHT, PLANE_LENGTH_WIDHT));
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

		m_plane.setMesh2(Geometry2::buildPlaneMesh(PLANE_LENGTH_WIDHT, PLANE_LENGTH_WIDHT));
		m_plane.setShader(normalMapShader, VertexPosNormalTangentTex::inputLayout, 4);
		m_plane.setNormalTexture(L"Texture\\stones_nmap.dds");
	}

	if (KeyBoard::getInstance().isKeyPress('C') && m_enableNormalMap)
	{
		m_enableNormalMap = false;
		m_plane.setMesh(Geometry::buildPlaneMesh(PLANE_LENGTH_WIDHT, PLANE_LENGTH_WIDHT));
		m_plane.setShader(SceneShader::shaderPath[9]);
	}

	static float rotY = 0.0f;
	rotY += deltaTime;

	m_naruto.setTransform(Transform(
		XMFLOAT3(0.1f, 0.1f, 0.1f),
		XMFLOAT3(XM_PI / 2, rotY, 0.0f),
		XMFLOAT3(4.0f, -4.0f, 0.0f)
	));

	m_madara.setTransform(Transform(
		XMFLOAT3(4.0f, 4.0f, 4.0f),
		XMFLOAT3(0.0f, rotY, 0.0f),
		XMFLOAT3(14.0f, -4.0f, 0.0f)
	));


}

void Chapter10Scene::drawScene()
{
	
	m_box1.draw();
	if (m_enableNormalMap)
		m_plane.draw2();
	else
		m_plane.draw();

	m_naruto.draw();
	m_madara.draw();
	//m_superman.draw();
	m_house.draw();
	m_tree.draw();

	m_skyBox.draw(m_perspectiveCamera);
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
