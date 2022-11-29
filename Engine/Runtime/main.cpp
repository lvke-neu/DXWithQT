#include <iostream>
#include "Core/Reflection/ReflectionManager.h"
#include "Core/Serialization/SerializationManager.h"


using namespace Twinkle;

class B : public ReflectionObject
{

private:
	GENERATE_ADDRES_FUNC(Name);
	std::string m_Name = "lvke";

	GENERATE_ADDRES_FUNC(Age);
	int m_Age = 250;
};

REGISTER_CLASS(B);
REGISTER_CLASS_FIELD(B, m_Name, std::string, getNameAddress);
REGISTER_CLASS_FIELD(B, m_Age, int, getAgeAddress);

class C : public SerializationObject
{
	SERIALIZE(m_name, m_age);
public:
	void setName(const std::string& name) { m_name = name; }
	void setAge(int age) { m_age = age; }
private:
	std::string m_name = "lvke";
	int m_age = 250;
};

int main()
{

	//B* obj = dynamic_cast<B*>((ReflectionObject*)Singleton<ReflectionManager>::GetInstance().create_class("B"));

	C c1;
	c1.setName("c1");
	c1.setAge(20);
	C c2;
	c2.setName("c2");
	c2.setAge(21);

	DataStream ds;

	Singleton<SerializationManager>::GetInstance().Serialize<C>(c1, ds);
	Singleton<SerializationManager>::GetInstance().Serialize<C>(c2, ds);
	ds.save("a.out");


	C c3, c4;
	DataStream ds2;
	ds2.load("a.out");
	Singleton<SerializationManager>::GetInstance().UnSerialize<C>(ds2, c3);
	Singleton<SerializationManager>::GetInstance().UnSerialize<C>(ds2, c4);

	//C c;

	//DataStream ds;
	//ds.load("a.out");
	//ds >> c;


	getchar();



	return 0;
}