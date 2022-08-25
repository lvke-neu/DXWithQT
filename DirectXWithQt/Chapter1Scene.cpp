#include "Chapter1Scene.h"

Chapter1Scene::Chapter1Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
{
	initCameraAndLight(pd3dDevice, pd3dImmediateContext);
	
	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.ByteWidth = sizeof(XMFLOAT4);
	m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_psConstantBuffer.GetAddressOf());

	m_pd3dImmediateContext->PSSetConstantBuffers(0, 1, m_psConstantBuffer.GetAddressOf());
}

void Chapter1Scene::initScene()
{
	m_triangle = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_triangle.setMesh(Geometry::buildTriangleMesh());
	m_triangle.setShader(SceneShader::shaderPath[0]);

	setColor(0.0f, 1.0f, 0.0f, 1.0f);
}



void Chapter1Scene::updateScene(float deltaTime)
{

}

void Chapter1Scene::drawScene()
{
	m_triangle.draw();
}




void Chapter1Scene::setColor(float r, float g, float b, float a)
{
	m_color.x = r;
	m_color.y = g;
	m_color.z = b;
	m_color.w = a;

	D3D11_MAPPED_SUBRESOURCE mappedData;
	m_pd3dImmediateContext->Map(m_psConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
	memcpy_s(mappedData.pData, sizeof(XMFLOAT4), &m_color, sizeof(XMFLOAT4));
	m_pd3dImmediateContext->Unmap(m_psConstantBuffer.Get(), 0);
}