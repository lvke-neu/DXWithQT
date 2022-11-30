//#include <iostream>
//#include "Core/Reflection/ReflectionManager.h"
//#include "Core/Serialization/SerializationManager.h"
//
//
//using namespace Twinkle;
//
//class B : public ReflectionObject
//{
//
//private:
//	GENERATE_ADDRES_FUNC(Name);
//	std::string m_Name = "lvke";
//
//	GENERATE_ADDRES_FUNC(Age);
//	int m_Age = 250;
//};
//
//REGISTER_CLASS(B);
//REGISTER_CLASS_FIELD(B, m_Name, std::string, getNameAddress);
//REGISTER_CLASS_FIELD(B, m_Age, int, getAgeAddress);
//
//class C : public SerializationObject
//{
//	SERIALIZE(m_name, m_age);
//public:
//	void setName(const std::string& name) { m_name = name; }
//	void setAge(int age) { m_age = age; }
//private:
//	std::string m_name = "lvke";
//	int m_age = 250;
//};
//
//class D
//{
//public:
//	D() {
//		std::cout << "base const" << std::endl;
//	}
//	~D() {
//		std::cout << "base deconst" << std::endl;
//	}
//private:
//	int a;
//	int b;
//	int c;
//};
//
//class E : public D
//{
//public:
//	E() {
//		std::cout << "devire const" << std::endl;
//	}
//	~E() {
//		std::cout << "devire deconst" << std::endl;
//	}
//private:
//	int c;
//};
//
//template<typename T>
//void func(T a, T b)
//{
//	a - b;
//}
//
//int main()
//{
//	E e;
//	std::cout << sizeof(E);
//
//
//	getchar();
//
//
//
//	return 0;
//}