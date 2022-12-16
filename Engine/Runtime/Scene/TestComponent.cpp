#include "TestComponent.h"

namespace Twinkle
{
	TestComponent::TestComponent()
	{
		
	}

	TestComponent::~TestComponent()
	{
		
	}

	const std::string& TestComponent::getName() const
	{
		return m_name;
	}


	void TestComponent::setName(const std::string & name)
	{
		m_name = name;
	}

	int TestComponent::getAge()
	{
		return m_age;
	}

	void TestComponent::setAge(int age)
	{
		m_age = age;
	}

	int Son::getSex()
	{
		return m_sex;
	}

	void Son::setSex(int sex)
	{
		m_sex = sex;
	}
}

