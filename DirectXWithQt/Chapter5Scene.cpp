#include "Chapter5Scene.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include <string>
#include "RenderStates.h"

Chapter5Scene::Chapter5Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
{
	initCameraAndLight(pd3dDevice, pd3dImmediateContext);
	m_perspectiveCamera.setPosition(-0.7f, 5.77f, -1.8f);
	m_perspectiveCamera.setRotation(0.57f, 0.0f, 0.0f);
	setDirLight(0.5, -1.0f, 0.0f);


	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.ByteWidth = sizeof(EnableShadow);
	m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pEnableShadowCB.GetAddressOf());
	cbd.ByteWidth = sizeof(ShadowMatrix);
	m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pShadowMatrixCB.GetAddressOf());

	m_pd3dImmediateContext->VSSetConstantBuffers(5, 1, m_pEnableShadowCB.GetAddressOf());
	m_pd3dImmediateContext->PSSetConstantBuffers(5, 1, m_pEnableShadowCB.GetAddressOf());

	m_pd3dImmediateContext->VSSetConstantBuffers(6, 1, m_pShadowMatrixCB.GetAddressOf());
	m_pd3dImmediateContext->PSSetConstantBuffers(6, 1, m_pShadowMatrixCB.GetAddressOf());



	m_generalMaterial.ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_generalMaterial.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_generalMaterial.specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 5.0f);

	m_shadowMaterial.ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	m_shadowMaterial.diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.5f);
	m_shadowMaterial.specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 5.0f);

	set_ShadowMatrix();

}

void Chapter5Scene::initScene()
{
	m_wall = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_wall.setMesh(Geometry::buildPlaneMesh(4.0f, 2.0f));
	m_wall.setShader(SceneShader::shaderPath[4]);
	m_wall.setTexture(L"Texture\\brick.dds");
	m_wall.setMaterial(m_generalMaterial);

	m_floor = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_floor.setMesh(Geometry::buildPlaneMesh(5.0f, 5.0f));
	m_floor.setShader(SceneShader::shaderPath[4]);
	m_floor.setTexture(L"Texture\\floor.dds");
	m_floor.setMaterial(m_generalMaterial);
	m_floor.setTransform(Transform(
		XMFLOAT3(10.0f, 10.0f, 1.0f),
		XMFLOAT3(XM_PI / 2, 0.0f, 0.0f),
		XMFLOAT3(0.0f, -5.0f, 10.0f)
	));

	m_box = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_box.setMesh(Geometry::buildBoxMesh());
	m_box.setShader(SceneShader::shaderPath[4]);
	m_box.setTexture(L"Texture\\WoodCrate.dds");
	m_box.setMaterial(m_generalMaterial);
	m_box.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(-2.0f, 0.0f, 10.0f)
	));

	m_box2 = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_box2.setMesh(Geometry::buildBoxMesh());
	m_box2.setShader(SceneShader::shaderPath[4]);
	m_box2.setTexture(L"Texture\\WoodCrate.dds");
	m_box2.setMaterial(m_generalMaterial);
	m_box2.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(3.0f, -4.0f, 7.0f)
	));

	m_pd3dImmediateContext->RSSetState(nullptr);
}


void Chapter5Scene::updateScene(float deltaTime)
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

	static float rotX = 0.0f;
	rotX += deltaTime;
	m_box.setRotation(rotX, 0.0f, 0.0f);
}

void Chapter5Scene::drawScene()
{


	m_wall.setTransform(Transform(
		XMFLOAT3(10.0f, 5.0f, 1.0f),
		XMFLOAT3(0.0f, XM_PI, 0.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f)
	));
	m_wall.draw();


	m_wall.setTransform(Transform(
		XMFLOAT3(10.0f, 5.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, 20.0f)
	));
	m_wall.draw();

	m_wall.setTransform(Transform(
		XMFLOAT3(10.0f, 5.0f, 1.0f),
		XMFLOAT3(0.0f, -XM_PI / 2, 0.0f),
		XMFLOAT3(-10.0f, 0.0f, 10.0f)
	));
	m_wall.draw();


	m_wall.setTransform(Transform(
		XMFLOAT3(10.0f, 5.0f, 1.0f),
		XMFLOAT3(0.0f, XM_PI / 2, 0.0f),
		XMFLOAT3(10.0f, 0.0f, 10.0f)
	));
	m_wall.draw();

	m_floor.draw();

	m_box.draw();
	m_box2.draw();
	



	m_pd3dImmediateContext->OMSetBlendState(RenderStates::BSTransparent.Get(), nullptr, 0xFFFFFFFF);
	set_EnableShadow(true);
	m_box.setMaterial(m_shadowMaterial);
	m_box.draw();
	m_box2.setMaterial(m_shadowMaterial);
	m_box2.draw();
	


	m_pd3dImmediateContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
	set_EnableShadow(false);
	m_box.setMaterial(m_generalMaterial);
	m_box2.setMaterial(m_generalMaterial);
}




void Chapter5Scene::setDirLight(XMFLOAT3 dir)
{
	m_dirLight_dir = dir;
	DirectionLight directionLight;

	directionLight.ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	directionLight.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	directionLight.specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 5.0f);
	directionLight.direction = dir;

	D3D11_MAPPED_SUBRESOURCE mappedData;
	m_pd3dImmediateContext->Map(m_pLightCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
	memcpy_s(mappedData.pData, sizeof(DirectionLight), &directionLight, sizeof(DirectionLight));
	m_pd3dImmediateContext->Unmap(m_pLightCB.Get(), 0);

	m_pd3dImmediateContext->PSSetConstantBuffers(4, 1, m_pLightCB.GetAddressOf());

	set_ShadowMatrix();
}



void Chapter5Scene::set_EnableShadow(bool b)
{
	if (m_pEnableShadowCB)
	{
		EnableShadow enableShadow;
		enableShadow.isShadow = b;

		D3D11_MAPPED_SUBRESOURCE mappedData;
		m_pd3dImmediateContext->Map(m_pEnableShadowCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
		memcpy_s(mappedData.pData, sizeof(EnableShadow), &enableShadow, sizeof(EnableShadow));
		m_pd3dImmediateContext->Unmap(m_pEnableShadowCB.Get(), 0);


	}
}

void Chapter5Scene::set_ShadowMatrix()
{
	if (m_pShadowMatrixCB)
	{
		ShadowMatrix shadowMatrix;



		shadowMatrix.shadowMatrix = XMMatrixTranspose(XMMatrixShadow(XMVectorSet(0.0f, -1.0f, 0.0f, -4.99f), XMVectorSet(m_dirLight_dir.x, m_dirLight_dir.y, m_dirLight_dir.z, 0.0f)));



		D3D11_MAPPED_SUBRESOURCE mappedData;
		m_pd3dImmediateContext->Map(m_pShadowMatrixCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
		memcpy_s(mappedData.pData, sizeof(ShadowMatrix), &shadowMatrix, sizeof(ShadowMatrix));
		m_pd3dImmediateContext->Unmap(m_pShadowMatrixCB.Get(), 0);
	}

}

void Chapter5Scene::notifyAll()
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
