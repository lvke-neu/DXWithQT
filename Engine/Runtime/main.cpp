#include <iostream>
#include "Core/Reflection/ReflectionManager.h"

using namespace Twinkle;

class A : public ReflectionObject
{
public:
	void show()
	{
		std::cout << "Hello, A" << std::endl;
	}
};

REGISTER_CLASS(A);


class B : public ReflectionObject
{
public:
	void show()
	{
		std::cout << "Hello, B" << std::endl;
	}
public:
	std::string m_name = "lvke";
	int m_age = 250;
	std::vector<int> m_vector{1,2,3};
};

REGISTER_CLASS(B);
REGISTER_CLASS_FIELD(B, m_name, std::string);
REGISTER_CLASS_FIELD(B, m_age, int);
//REGISTER_CLASS_FIELD(B, m_vector, std::vector<int>);

class C
{
public:
	C(const std::string& name, int age) : m_name(name), m_age(age)
	{

	}
public:
	std::string m_name;
	int m_age;
};



int main()
{


	//auto offset1 = (size_t)&((C*)0)->m_name;
	//std::cout << offset1 << std::endl;
	//auto offset2 = (size_t)&((C*)0)->m_age;
	//std::cout << offset2 << std::endl;

	//C c("lvke", 26);
	//std::cout << *(std::string*)((size_t)(&c) + offset1) << std::endl;
	//std::cout << *(int*)((size_t)(&c) + offset2) << std::endl;
	//C c("lvke", 26);
	//auto offset1 = (size_t) & (c.m_age)-(size_t) & (c);
	//std::cout << *(int*)((size_t)(&c) + offset1) << std::endl;
	//ReflectionObject* obj = nullptr;

	//obj = (ReflectionObject*)Singleton<ReflectionManager>::GetInstance().create_class("A");
	//A* a = dynamic_cast<A*>(obj);
	//if(a)
	//	a->show();

	ReflectionObject* obj = (ReflectionObject*)Singleton<ReflectionManager>::GetInstance().create_class("B");
	B* b = dynamic_cast<B*>(obj);
	if (b)
	{

		std::cout << b->get_class_name()<< std::endl;		
		std::cout << obj->get_field_count()<< std::endl;

	}
		




	return 0;
}