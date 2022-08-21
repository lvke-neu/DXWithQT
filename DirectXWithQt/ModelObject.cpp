#include "ModelObject.h"
#include <thread>

ModelObject::ModelObject(const ObjReader& objReader, ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
{
	Mesh mesh;

	for (auto& objPart : objReader.objParts)
	{
		mesh.vertexBuffer = objPart.vertices;
		mesh.indexBuffer = objPart.indices16.size() != 0 ? objPart.indices16 : objPart.indices32;

		GameObject go(pd3dDevice, pd3dImmediateContext);

		go.setMesh(mesh);
		go.setTexture(objPart.texStrDiffuse.c_str());
		go.setMaterial(objPart.material);
			
		m_gameObjects.push_back(go);
	}

	BoundingBox::CreateFromPoints(m_boundingBox, objReader.vecMax, objReader.vecMin);
	
}

void ModelObject::setShader(std::vector<std::wstring> shader)
{
	for (auto& go : m_gameObjects)
		go.setShader(shader);
}

Transform ModelObject::getTransform()
{
	return m_transform;
}

void ModelObject::setTransform(const Transform& transform)
{
	m_transform = transform;
	for (auto& go : m_gameObjects)
		go.setTransform(transform);
}

void ModelObject::setPosition(float x, float y, float z)
{
	for (auto& go : m_gameObjects)
		go.setPosition(x, y, z);
}

void ModelObject::draw()
{
	for (auto& go : m_gameObjects)
		go.draw();
}

