#include "Chapter2Scene.h"

Chapter2Scene::Chapter2Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
	:m_pd3dDevice(pd3dDevice), m_pd3dImmediateContext(pd3dImmediateContext)
{
	//PipeLine::init(m_pd3dDevice, m_pd3dImmediateContext);
}

void Chapter2Scene::initScene()
{
	m_triangle.setMesh(Geometry::buildTriangleMesh());
	m_triangle.setShader(2);
	//PipeLine::bindGoToPipeLine(m_triangle);
}

void Chapter2Scene::updateScene()
{

}

void Chapter2Scene::drawScene()
{
	//m_pd3dImmediateContext->DrawIndexed(m_triangle.getMesh().indexBuffer.size(), 0, 0);
}