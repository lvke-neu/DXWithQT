#include "Chapter4Scene.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include <string>
#include "RenderStates.h"

Chapter4Scene::Chapter4Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
{

	initCameraAndLight(pd3dDevice, pd3dImmediateContext);
	m_perspectiveCamera.setPosition(-9.75f, 2.03f, 1.69f);
	m_perspectiveCamera.setRotation(0.2f, 0.98f, 0.0f);

	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.ByteWidth = sizeof(Reflection);
	m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pRelectionCB.GetAddressOf());


	m_pd3dImmediateContext->VSSetConstantBuffers(5, 1, m_pRelectionCB.GetAddressOf());
	m_pd3dImmediateContext->PSSetConstantBuffers(5, 1, m_pRelectionCB.GetAddressOf());
	
}

void Chapter4Scene::initScene()
{
	Material material;
	material.ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 250.0f);

	m_box = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_box.setMesh(Geometry::buildBoxMesh());
	m_box.setShader(SceneShader::shaderPath[3]);
	m_box.setTexture(L"Texture\\WoodCrate.dds");
	m_box.setMaterial(material);
	m_box.setTransform(Transform(
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(0.0f, -1.0f, 10.0f)
	));

	m_firstPersonBox = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_firstPersonBox.setMesh(Geometry::buildBoxMesh());
	m_firstPersonBox.setShader(SceneShader::shaderPath[3]);
	m_firstPersonBox.setTexture(L"Texture\\WoodCrate.dds");
	m_firstPersonBox.setMaterial(material);
	m_firstPersonBox.setTransform(Transform(
		XMFLOAT3(0.5f, 0.5f, 0.5f),
		XMFLOAT3(0.0f, XM_PI / 2, 0.0f),
		XMFLOAT3(0.0f, -4.0f, 10.0f)
	));

	m_wall = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_wall.setMesh(Geometry::buildPlaneMesh(4.0f, 2.0f));
	m_wall.setShader(SceneShader::shaderPath[3]);
	m_wall.setTexture(L"Texture\\brick.dds");
	m_wall.setMaterial(material);

	
	m_mirrorWall = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_mirrorWall.setMesh(Geometry::buildPlaneMesh(1.0f, 2.0f));
	m_mirrorWall.setShader(SceneShader::shaderPath[3]);
	m_mirrorWall.setTexture(L"Texture\\brick.dds");
	m_mirrorWall.setMaterial(material);

	m_floor = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_floor.setMesh(Geometry::buildPlaneMesh(5.0f, 5.0f));
	m_floor.setShader(SceneShader::shaderPath[3]);
	m_floor.setTexture(L"Texture\\floor.dds");
	m_floor.setMaterial(material);
	m_floor.setTransform(Transform(
		XMFLOAT3(10.0f, 10.0f, 1.0f),
		XMFLOAT3(XM_PI / 2, 0.0f, 0.0f),
		XMFLOAT3(0.0f, -5.0f, 10.0f)
	));


	material.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.3f);
	m_mirror = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_mirror.setMesh(Geometry::buildPlaneMesh(1.0f, 1.0f));
	m_mirror.setShader(SceneShader::shaderPath[3]);
	m_mirror.setTexture(L"Texture\\ice.dds");
	m_mirror.setMaterial(material);
	m_mirror.setTransform(Transform(
		XMFLOAT3(4.0f, 5.0f, 1.0f),
		XMFLOAT3(0.0f, XM_PI / 2, 0.0f),
		XMFLOAT3(10.0f, 0.0f, 10.0f)
	));

	
}


void Chapter4Scene::updateScene(float deltaTime)
{
	if (!m_isFirstPerson)
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
	}
	else
	{
		if (KeyBoard::getInstance().isKeyPress('W'))
		{
			m_firstPersonBox.moveZAxis(deltaTime * 20);
		}
		if (KeyBoard::getInstance().isKeyPress('S'))
		{
			m_firstPersonBox.moveZAxis(-deltaTime * 20);
		}
		if (KeyBoard::getInstance().isKeyPress('A'))
		{
			m_firstPersonBox.moveXAxis(-deltaTime * 20);
		}
		if (KeyBoard::getInstance().isKeyPress('D'))
		{
			m_firstPersonBox.moveXAxis(deltaTime * 20);
		}

		XMFLOAT3 adjustedPos;
		XMStoreFloat3(&adjustedPos, XMVectorClamp(XMLoadFloat3(&m_firstPersonBox.getPosition()), XMVectorSet(-9.5f, -9.5f, 0.0f, 0.0f), XMVectorSet(9.5f, 9.5f, 19.5f, 0.0f)));
		m_firstPersonBox.setPosition(adjustedPos);

		m_perspectiveCamera.setPosition(m_firstPersonBox.getPosition());
	}



	static float rotx = 0.0f;
	rotx += deltaTime;
	m_box.setRotation(rotx, 0.0f, 0.0f);

}

void Chapter4Scene::drawScene()
{

	m_pd3dImmediateContext->RSSetState(nullptr);
	m_pd3dImmediateContext->OMSetDepthStencilState(RenderStates::DSSWriteStencil.Get(), 1);
	m_pd3dImmediateContext->OMSetBlendState(RenderStates::BSNoColorWrite.Get(), nullptr, 0xFFFFFFFF);
	m_mirror.draw();


	//开启反射，绘制镜子里的物体
	setIsReflection(true);

	m_pd3dImmediateContext->RSSetState(RenderStates::RSCullClockWise.Get());
	m_pd3dImmediateContext->OMSetDepthStencilState(RenderStates::DSSDrawWithStencil.Get(), 1);
	m_pd3dImmediateContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);

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
		XMFLOAT3(0.0f, -XM_PI / 2, 0.0f),
		XMFLOAT3(-10.0f, 0.0f, 10.0f)
	));
	m_wall.draw();

	m_floor.draw();

	m_box.draw();

	m_firstPersonBox.draw();

	//绘制镜面
	m_pd3dImmediateContext->RSSetState(RenderStates::RSNoCull.Get());
	m_pd3dImmediateContext->OMSetDepthStencilState(RenderStates::DSSDrawWithStencil.Get(), 1);
	m_pd3dImmediateContext->OMSetBlendState(RenderStates::BSTransparent.Get(), nullptr, 0xFFFFFFFF);
	m_mirror.draw();

	//关闭反射
	setIsReflection(false);
	m_pd3dImmediateContext->RSSetState(nullptr);
	m_pd3dImmediateContext->OMSetDepthStencilState(nullptr, 0);
	m_pd3dImmediateContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);

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
		XMFLOAT3(0.0f, -XM_PI / 2, 0.0f),
		XMFLOAT3(-10.0f, 0.0f, 10.0f)
	));
	m_wall.draw();
	
	//镜子所在面的墙
	m_mirrorWall.setTransform(Transform(
		XMFLOAT3(3.0f, 5.0f, 1.0f),
		XMFLOAT3(0.0f, XM_PI / 2, 0.0f),
		XMFLOAT3(10.0f, 0.0f, 17.0f)
	));
	m_mirrorWall.draw();

	//镜子所在面的墙
	m_mirrorWall.setTransform(Transform(
		XMFLOAT3(3.0f, 5.0f, 1.0f),
		XMFLOAT3(0.0f, XM_PI / 2, 0.0f),
		XMFLOAT3(10.0f, 0.0f, 3.0f)
	));
	m_mirrorWall.draw();

	m_floor.draw();

	m_box.draw();

	if(!m_isFirstPerson)
		m_firstPersonBox.draw();
	
}




void Chapter4Scene::setDirLight(XMFLOAT3 dir)
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

void Chapter4Scene::setIsReflection(bool b)
{
	Reflection reflection;
	reflection.isEnableReflec = b;
	reflection.reflectionMatrix = XMMatrixTranspose(XMMatrixReflect(XMVectorSet(-1.0f, 0.0f, 0.0f, 10.0f)));

	D3D11_MAPPED_SUBRESOURCE mappedData;
	m_pd3dImmediateContext->Map(m_pRelectionCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
	memcpy_s(mappedData.pData, sizeof(Reflection), &reflection, sizeof(Reflection));
	m_pd3dImmediateContext->Unmap(m_pRelectionCB.Get(), 0);
}


void Chapter4Scene::setMirrorTransparency(float transparency)
{
	Material material;
	material.ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, transparency);
	material.specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 250.0f);

	m_mirror.setMaterial(material);
}

void Chapter4Scene::notifyAll()
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
