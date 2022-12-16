//#include "TestComponent.h"
//
//namespace Twinkle
//{
//	class Son : public TestComponent
//	{
//	public:
//		int getSex();
//		void setSex(int sex);
//	private:
//		int m_sex = 0;
//
//		RTTR_ENABLE()
//	};
//
//	RTTR_REGISTRATION
//	{
//		rttr::registration::class_<Twinkle::Son>("Son")
//			.constructor<>()
//			(
//				rttr::policy::ctor::as_std_shared_ptr
//			)
//			.property("m_sex", &Son::getSex, &Twinkle::Son::setSex);
//	}
//
//}
//


#include <rttr/registration>
#include "TestComponent.h"


RTTR_REGISTRATION
{
	rttr::registration::class_<Twinkle::TestComponent>("TestComponent")
		.constructor<>()
		(
			rttr::policy::ctor::as_std_shared_ptr
		)
		.property("m_name", &Twinkle::TestComponent::getName, &Twinkle::TestComponent::setName)
		.property("m_age", &Twinkle::TestComponent::getAge, &Twinkle::TestComponent::setAge);

rttr::registration::class_<Twinkle::Son>("Son")
.constructor<>()
(
	rttr::policy::ctor::as_std_shared_ptr
	)
	.property("m_sex", &Twinkle::Son::getSex, &Twinkle::Son::setSex);
}