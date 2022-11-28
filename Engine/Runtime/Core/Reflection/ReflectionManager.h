/***************************************************************************************
Author: lvke
Date:2022/11/28 21:56
Description:

****************************************************************************************/
#pragma once

#include <string>
#include <map>
#include "../Interface/SingletonInterface.h"

namespace Twinkle
{
	/*************************** Relection Object ****************************/
	class ReflectionObject
	{
	public:
		ReflectionObject() = default;
		virtual ~ReflectionObject() = default;
	};
	/************************************************************************/


	/*************************** Relection Manager ****************************/
	typedef ReflectionObject* (*create_object)(void);

	class ReflectionManager
	{
		friend class Singleton<ReflectionManager>;
	public:
		void register_class(const std::string& className, create_object method);
		ReflectionObject* create_class(const std::string& className);
	private:
		ReflectionManager() = default;
		virtual ~ReflectionManager() = default;
		ReflectionManager(const ReflectionManager&) = default;
		ReflectionManager& operator=(const ReflectionManager&) = default;
	private:
		std::map<std::string, create_object> m_classMap;
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
	};
	/************************************************************************/


	/*************************** Macro **************************************/
#define REGISTER_CLASS(className) \
	ReflectionObject* createObject##className()\
	{\
		ReflectionObject* obj = new className();\
		return obj;\
	}\
	ClassRegister classRegister##className(#className, createObject##className);
	/************************************************************************/
}