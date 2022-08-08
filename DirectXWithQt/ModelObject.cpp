#include "ModelObject.h"
#include <thread>

ModelObject::ModelObject(wchar_t * mboFileName, wchar_t * objFileName, ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext):
	m_mboFileName(mboFileName), m_objFileName(objFileName),GameObject(pd3dDevice, pd3dImmediateContext)
{

	if (objReader.Read(m_mboFileName, objFileName))
	{
		builMesh();
		buildTexture();
		buildMaterial();
	}
}


void ModelObject::builMesh()
{
	Mesh mesh;
	mesh.vertexBuffer = objReader.objParts[0].vertices;
	int size = objReader.objParts[0].indices16.size();
	mesh.indexBuffer = size != 0 ? objReader.objParts[0].indices16 : objReader.objParts[0].indices32;

	setMesh(mesh);

}

void ModelObject::buildTexture()
{
	setTexturePathNotDDS(objReader.objParts[0].texStrDiffuse.c_str());
}

void ModelObject::buildMaterial()
{
	setMaterial(objReader.objParts[0].material);
}