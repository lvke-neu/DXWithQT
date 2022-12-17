#include <rttr/registration>
#include "Runtime/Scene/TestComponent.h"

namespace Twinkle
{
	RTTR_REGISTRATION
	{
		rttr::registration::class_<TestComponent>("TestComponent")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("m_name", &TestComponent::getName, &TestComponent::setName)
			.property("m_age", &TestComponent::getAge, &TestComponent::setAge);

	rttr::registration::class_<comp>("comp")
	.constructor<>()
	(
		rttr::policy::ctor::as_raw_ptr
		)
		.property("m_a", &comp::getA, &comp::setA);


	rttr::registration::class_<Son>("Son")
		.constructor<>()
		(
			rttr::policy::ctor::as_raw_ptr
		)
		.property("m_sex", &Son::getSex, &Son::setSex)
		.property("m_cp", &Son::getCp, &Son::setCp);
	}

}
