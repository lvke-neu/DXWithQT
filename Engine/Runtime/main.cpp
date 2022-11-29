#include <iostream>
#include "Core/Reflection/ReflectionManager.h"
#include "Core/Serialization/SerializationManager.h"

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

private:
	GENERATE_ADDRES_FUNC(Name);
	std::string m_Name = "lvke";

	GENERATE_ADDRES_FUNC(Age);
	int m_Age = 250;
};


REGISTER_CLASS(B);

//REGISTER_CLASS_FIELD(B, m_Name, std::string, getNameAddress);
REGISTER_CLASS_FIELD(B, m_Age, int, getAgeAddress);

//REGISTER_CLASS_FIELD(B, m_Name, std::string);
//
//REGISTER_CLASS_METHOD(B, getName, std::string);
//REGISTER_CLASS_METHOD(B, setName, void, std::string);
//REGISTER_CLASS_METHOD(B, getAge, int);
//REGISTER_CLASS_METHOD(B, setAge, void, int);
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

	B* obj = dynamic_cast<B*>((ReflectionObject*)Singleton<ReflectionManager>::GetInstance().create_class("B"));


	std::string serializeBStr{ "" };
	Singleton<SerializationManager>::GetInstance().Serialize(obj, serializeBStr);

	ReflectionObject* obj2{ nullptr };
	Singleton<SerializationManager>::GetInstance().Unserialize(serializeBStr, obj2);

	getchar();


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

	//ReflectionObject* obj = (ReflectionObject*)Singleton<ReflectionManager>::GetInstance().create_class("B");
	//B* b = dynamic_cast<B*>(obj);
	//if (b)
	//{
	//	b->call("testRelectMethod");
	//	
	//}
		


	return 0;
}