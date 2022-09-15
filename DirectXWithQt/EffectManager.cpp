#include "EffectManager.h"
#include "Reflection.h"
#include"rapidjson/document.h"
#include "d3dUtil.h"

REGISTER_CLASS(IManager, "EffectManager", EffectManager)


EffectManager::EffectManager(void** parameter)
{
	m_functions["setBoxEffect"] = std::bind(&EffectManager::setBoxEffect, this, std::placeholders::_1);
	m_functions["setSphereEffect"] = std::bind(&EffectManager::setSphereEffect, this, std::placeholders::_1);
}
EffectManager::~EffectManager()
{

}

void EffectManager::runFunction(const std::string functionName, void** parameter)
{
	m_functions[functionName](parameter);
}

void* EffectManager::setBoxEffect(void** parameter)
{
	buildBasicPrimitiveEffect(parameter, Box);
	
	return nullptr;
}

void* EffectManager::setSphereEffect(void** parameter)
{
	buildBasicPrimitiveEffect(parameter, Sphere);
	
	return nullptr;
}


void EffectManager::buildBasicPrimitiveEffect(void** parameter, BasicPrimitive type)
{
	GameApp* gameApp = (GameApp*)parameter[0];

	rapidjson::Value* funcParameter = (rapidjson::Value*)parameter[1];

	XMFLOAT3 scale
	{
		(*funcParameter)["scale"]["x"].GetFloat(),
		(*funcParameter)["scale"]["y"].GetFloat(),
		(*funcParameter)["scale"]["z"].GetFloat()
	};
	XMFLOAT3 rotation
	{
		(*funcParameter)["rotation"]["x"].GetFloat(),
		(*funcParameter)["rotation"]["y"].GetFloat(),
		(*funcParameter)["rotation"]["z"].GetFloat()
	};
	XMFLOAT3 position
	{
		(*funcParameter)["position"]["x"].GetFloat(),
		(*funcParameter)["position"]["y"].GetFloat(),
		(*funcParameter)["position"]["z"].GetFloat()
	};
	std::wstring texture = multiByteToWideChar((*funcParameter)["texture"].GetString());



	Material material;
	material.ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 250.0f);

	GameObject basicPrimitiveEffect(gameApp->getScene()->getD3dDevice(), gameApp->getScene()->getD3dImmediateContext());

	if (type == Box)
		basicPrimitiveEffect.setMesh(Geometry::buildBoxMesh());
	else if (type == Sphere)
		basicPrimitiveEffect.setMesh(Geometry::buildSphereMesh());

	basicPrimitiveEffect.setShader(SceneShader::shaderPath[1]);
	basicPrimitiveEffect.setTexture(texture);
	basicPrimitiveEffect.setMaterial(material);
	basicPrimitiveEffect.setTransform(Transform(
		scale,
		rotation,
		position
	));

	gameApp->getScene()->addEffect(basicPrimitiveEffect);
}
