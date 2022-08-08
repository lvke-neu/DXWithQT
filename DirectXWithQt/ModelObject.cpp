#include "ModelObject.h"
#include <thread>

ModelObject::ModelObject(wchar_t * mboFileName, wchar_t * objFileName, ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext):
	m_mboFileName(mboFileName), m_objFileName(objFileName),GameObject(pd3dDevice, pd3dImmediateContext)
{

	if (objReader.ReadObj(m_objFileName))
	{
		builMesh();
		buildTexture();
		buildMaterial();
	}
}


void ModelObject::builMesh()
{
	Mesh mesh;
	int size;
	mesh.vertexBuffer.clear();
	mesh.indexBuffer.clear();
	for (auto& x : objReader.objParts)
	{
		mesh.vertexBuffer.insert(mesh.vertexBuffer.end(), x.vertices.begin(), x.vertices.end());
		size = x.indices16.size();
		if (size)
		{
			mesh.indexBuffer.insert(mesh.indexBuffer.end(), x.indices16.begin(), x.indices16.end());
		}
		else
		{
			mesh.indexBuffer.insert(mesh.indexBuffer.end(), x.indices32.begin(), x.indices32.end());
		}
	}

	setMesh(mesh);

}

void ModelObject::buildTexture()
{
	setTexturePathWIC(objReader.objParts[0].texStrDiffuse.c_str());
}

void ModelObject::buildMaterial()
{
	setMaterial(objReader.objParts[0].material);
}