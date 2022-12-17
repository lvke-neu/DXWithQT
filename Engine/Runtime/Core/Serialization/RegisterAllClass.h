#include <rttr/registration>
#include "Runtime/Scene/ECS/GameObject/BasicGeometryGameObject.h"

namespace Twinkle
{
	RTTR_REGISTRATION
	{
		rttr::registration::class_<XMFLOAT3>("XMFLOAT3")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("x", &XMFLOAT3::x)
			.property("y", &XMFLOAT3::y)
			.property("z", &XMFLOAT3::z);

		rttr::registration::class_<Transform>("Transform")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
				)
			.property("m_scale", &Transform::getScale, &Transform::SetScale)
			.property("m_rotation", &Transform::getRotation, &Transform::SetRotation)
			.property("m_position", &Transform::getPosition, &Transform::SetPosition);

		rttr::registration::class_<TransformComponent>("TransformComponent")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
				)
			.property("m_transform", &TransformComponent::getTransform, &TransformComponent::setTransform);

		rttr::registration::class_<MeshComponent>("MeshComponent")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
				)
			.property("m_vsShaderPath", &MeshComponent::getVsShader, &MeshComponent::setVsShader)
			.property("m_psShaderPath", &MeshComponent::getPsShader, &MeshComponent::setPsShader)
			.property("m_texturePath", &MeshComponent::getTexture, &MeshComponent::setTexture);

		rttr::registration::class_<BasicGeometryGameObject>("BasicGeometryGameObject")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
				)
			.property("m_transformComponent", &BasicGeometryGameObject::getTransformComponent, &BasicGeometryGameObject::setTransformComponent)
			.property("m_meshComponent", &BasicGeometryGameObject::getMeshComponent, &BasicGeometryGameObject::setMeshComponent);

	}

}




////rttr test
//rttr::type t = rttr::type::get_by_name("Son");
//size_t sizeee = t.get_properties().size();
//
//LOG_INFO("******************************************************************");
//
//for (auto& prop : t.get_properties())
//{
//	LOG_INFO(prop.get_name().to_string() + ", " + prop.get_type().get_name().to_string());
//}
//
//
//
//std::string jsonStr{ "" };
//Son sn;
//sn.setAge(250);
//sn.setName("lvke");
//sn.setSex(123);
//Singleton<SerializationManager>::GetInstance().Serialize(sn, jsonStr);
//sn.setCp(new comp);
//
//
//
//
//rttr::variant var = rttr::type::get_by_name("Son").create();
//Singleton<SerializationManager>::GetInstance().UnSerialize(jsonStr, var);
//
//Son* s2 = var.get_value<Son*>();