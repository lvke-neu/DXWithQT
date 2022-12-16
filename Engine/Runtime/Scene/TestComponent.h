#pragma once
#include <string>
#include <rttr/type>

namespace Twinkle
{

	class TestComponent
	{
	public:
		TestComponent();
		~TestComponent();

		const std::string& getName() const;
		void setName(const std::string& name);

		int getAge();
		void setAge(int age);
	protected:
		std::string m_name{ "" };
		int m_age = -1;

		RTTR_ENABLE()
	};

	class Son : public TestComponent
	{
	public:
		int getSex();
		void setSex(int sex);
	private:
		int m_sex = 0;

		RTTR_ENABLE()
	};

}