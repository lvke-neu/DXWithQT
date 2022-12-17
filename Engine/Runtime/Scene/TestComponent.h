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

	class comp
	{
	public:
		int getA();
		void setA(int aa);
	private:
		int a = 0;

		RTTR_ENABLE()
	};

	class Son : public TestComponent
	{
	public:
		int getSex();
		void setSex(int sex);

		const comp& getCp() const;
		void setCp(const comp& cp);
	private:
		int m_sex = 0;
		comp m_cp;
		RTTR_ENABLE(TestComponent)
	};

}