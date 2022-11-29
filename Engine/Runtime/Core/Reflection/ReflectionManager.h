/***************************************************************************************
Author: lvke
Date:2022/11/28 21:56
Description:
Reflection Manager
****************************************************************************************/
#pragma once

#include <string>
#include <map>
#include <vector>
#include <functional>
#include "../Interface/SingletonInterface.h"

namespace Twinkle
{
	/*************************** Class Field ****************************/
	class ClassField
	{
	public:
		ClassField() : m_name(""), m_type(""), m_offset(0) {}
		ClassField(const std::string& name, const std::string& type, size_t ofsset): m_name(name), m_type(type), m_offset(ofsset) {}
		~ClassField() = default;
	public:
		std::string name() { return m_name; }
		std::string type() { return m_type; }
		size_t offset()    { return m_offset;}

	private:
		std::string m_name;
		std::string m_type;
		size_t m_offset;
	};
	/************************************************************************/

	/*************************** Class Method ******************************/
	class ClassMethod
	{
	public:
		ClassMethod() : m_name(""), m_method(0) {}
		ClassMethod(const std::string& name, uintptr_t method) : m_name(name), m_method(method) {}
		~ClassMethod() {}

		std::string name()
		{
			return m_name;
		}

		uintptr_t method()
		{
			return m_method;
		}

	private:
		std::string m_name;
		uintptr_t m_method;
	};
	/************************************************************************/


	/*************************** Relection Object ****************************/
	class ReflectionManager;
	class ReflectionObject
	{
	public:
		ReflectionObject() = default;
		virtual ~ReflectionObject() = default;
	public:
		void set_class_name(const std::string& className);
		std::string get_class_name() const;

		size_t get_field_count();
		ClassField* get_field(int pos);
		ClassField* get_field(const std::string& fieldName);

		template<typename T>
		void get(const std::string& fieldName, T& value);

		template<typename T>
		void set(const std::string& fieldName, const T& value);

		template <typename R = void, typename ...Args>
		R call(const std::string& methodName, Args... args);
	private:
		std::string m_className{ "" };
	};

	template<typename T>
	void ReflectionObject::get(const std::string& fieldName, T& value)
	{
		size_t offset = Singleton<ReflectionManager>::GetInstance().get_field(m_className, fieldName)->offset();
		value = *(T*)((unsigned char*)(this) + offset);
	}

	template<typename T>
	void ReflectionObject::set(const std::string& fieldName, const T& value)
	{
		size_t offset = Singleton<ReflectionManager>::GetInstance().get_field(m_className, fieldName)->offset();
		*(T*)((unsigned char*)(this) + offset) = value;
	}

	template <typename R, typename ...Args>
	R ReflectionObject::call(const std::string& methodName, Args... args)
	{
		auto func = Singleton<ReflectionManager>::GetInstance().get_class_method(m_className, methodName)->method();
		typedef std::function<R(decltype(this), Args...)> class_method;
		return (*((class_method*)func))(this, args...);
	}

	/************************************************************************/


	/*************************** Relection Manager ****************************/
	typedef ReflectionObject* (*create_object)(void);

	class ReflectionManager
	{
		FRIEND_SINGLETON(ReflectionManager);
	public:
		void register_class(const std::string& className, create_object method);
		ReflectionObject* create_class(const std::string& className);

		void register_class_field(const std::string& className, const std::string& fieldName, const std::string& fieldType, size_t offset);
		size_t get_field_count(const std::string& className);
		ClassField* get_field(const std::string& className, uint32_t pos);
		ClassField* get_field(const std::string& className, const std::string& fieldName);

		void register_class_method(const std::string& className, const std::string& methodName, uintptr_t method);
		size_t get_class_method_count(const std::string& className);
		ClassMethod* get_class_method(const std::string& className, int pos);
		ClassMethod* get_class_method(const std::string& className, const std::string& methodName);
	private:
		ReflectionManager() = default;
		virtual ~ReflectionManager();
		ReflectionManager(const ReflectionManager&) = default;
		ReflectionManager& operator=(const ReflectionManager&) = default;
	private:
		std::map<std::string, create_object> m_classMap;
		std::map<std::string, std::vector<ClassField*>> m_classFieldMap;
		std::map<std::string, std::vector<ClassMethod*>> m_classMethodMap;
	};
	/************************************************************************/


	/*************************** Class Register ****************************/
	class ClassRegister
	{
	public:
		ClassRegister(const std::string& className, create_object method)
		{
			Singleton<ReflectionManager>::GetInstance().register_class(className, method);
		}
		ClassRegister(const std::string& className, const std::string& fieldName, const std::string& fieldType, size_t offset)
		{
			Singleton<ReflectionManager>::GetInstance().register_class_field(className, fieldName, fieldType, offset);
		}
		ClassRegister(const std::string& className, const std::string& methodName, uintptr_t method)
		{
			// register class method
			Singleton<ReflectionManager>::GetInstance().register_class_method(className, methodName, method);
		}
	};
	/************************************************************************/


	/*************************** Macro **************************************/
#define REGISTER_CLASS(className) \
	ReflectionObject* createObject##className()\
	{\
		ReflectionObject* obj = new className();\
		obj->set_class_name(#className);\
		return obj;\
	}\
	ClassRegister classRegister##className(#className, createObject##className);

#define GENERATE_ADDRES_FUNC(fieldName) \
public:\
	size_t get##fieldName##Address()\
	{\
		return (size_t)&m_##fieldName;\
	}\
private:

#define REGISTER_CLASS_FIELD(className, fieldName, fieldType, offsetFuncName) \
    className className##fieldName; \
    ClassRegister classRegister##className##fieldName(#className, #fieldName, #fieldType, className##fieldName.offsetFuncName() - (size_t)(&className##fieldName))
	
#define REGISTER_CLASS_METHOD(className, methodName, returnType, ...) \
    std::function<returnType(className *, ##__VA_ARGS__)> className##methodName##method = &className::methodName; \
    ClassRegister classRegister##className##methodName(#className, #methodName, (uintptr_t)&(className##methodName##method))
	/************************************************************************/
}