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
//int main()
//{
//	C c1;
//	c1.setName("c1");
//	c1.setAge(20);
//	C c2;
//	c2.setName("c2");
//	c2.setAge(21);
//
//	DataStream ds;
//
//	Singleton<SerializationManager>::GetInstance().Serialize<C>(c1, ds);
//	Singleton<SerializationManager>::GetInstance().Serialize<C>(c2, ds);
//	ds.save("a.out");
//
//
//	C c3, c4;
//	DataStream ds2;
//	ds2.load("a.out");
//	Singleton<SerializationManager>::GetInstance().UnSerialize<C>(ds2, c3);
//	Singleton<SerializationManager>::GetInstance().UnSerialize<C>(ds2, c4);
//
//
//
//	return 0;
//}