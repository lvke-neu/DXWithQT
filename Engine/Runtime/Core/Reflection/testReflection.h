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
//int main()
//{
//
//	B* obj = dynamic_cast<B*>((ReflectionObject*)Singleton<ReflectionManager>::GetInstance().create_class("B"));
//
//
//
//	return 0;
//}