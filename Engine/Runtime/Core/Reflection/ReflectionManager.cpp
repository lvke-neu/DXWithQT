#include "ReflectionManager.h"
#include "Runtime/Utility/Utility.h"

namespace Twinkle
{
	void ReflectionObject::set_class_name(const std::string& className)
	{
		m_className = className;
	}

	std::string ReflectionObject::get_class_name() const
	{
		return m_className;
	}

	size_t ReflectionObject::get_field_count()
	{
		return Singleton<ReflectionManager>::GetInstance().get_field_count(m_className);
	}

	ClassField* ReflectionObject::get_field(int pos)
	{
		return Singleton<ReflectionManager>::GetInstance().get_field(m_className, pos);
	}

	ClassField* ReflectionObject::get_field(const std::string& fieldName)
	{
		return Singleton<ReflectionManager>::GetInstance().get_field(m_className, fieldName);
	}

	void ReflectionManager::register_class(const std::string & className, create_object method)
	{
		m_classMap[className] = method;
	}

	ReflectionObject* ReflectionManager::create_class(const std::string & className)
	{
		auto iter = m_classMap.find(className);
		
		return iter == m_classMap.end() ? nullptr : iter->second();
	}

	void ReflectionManager::register_class_field(const std::string& className, const std::string& fieldName, const std::string& fieldType, size_t offset)
	{
		m_classFieldMap[className].push_back(new ClassField(fieldName, fieldType, offset));
	}

	size_t ReflectionManager::get_field_count(const std::string& className) 
	{
		return m_classFieldMap[className].size();
	}

	ClassField* ReflectionManager::get_field(const std::string& className, uint32_t pos)
	{
		size_t size = m_classFieldMap[className].size();
		if (pos < 0 || pos >= size)
			return nullptr;
		return m_classFieldMap[className][pos];
	}

	ClassField* ReflectionManager::get_field(const std::string& className, const std::string& fieldName) 
	{
		auto iter = m_classFieldMap.find(className);
		if (iter != m_classFieldMap.end())
		{
			for (auto& classField : iter->second)
			{
				if (classField->name() == fieldName)
					return classField;
			}
		}
		return nullptr;
	}

	void ReflectionManager::register_class_method(const std::string& className, const std::string& methodName, uintptr_t method)
	{
		m_classMethodMap[className].push_back(new ClassMethod(methodName, method));
	}

	size_t ReflectionManager::get_class_method_count(const std::string& className)
	{
		return m_classMethodMap[className].size();
	}

	ClassMethod* ReflectionManager::get_class_method(const std::string& className, int pos)
	{
		size_t size = m_classMethodMap[className].size();
		if (pos < 0 || pos >= size)
		{
			return nullptr;
		}
		return m_classMethodMap[className][pos];
	}

	ClassMethod* ReflectionManager::get_class_method(const std::string& className, const std::string& methodName)
	{
		auto methods = m_classMethodMap[className];
		for (auto it = methods.begin(); it != methods.end(); it++)
		{
			if ((*it)->name() == methodName)
			{
				return *it;
			}
		}
		return nullptr;
	}

	ReflectionManager::~ReflectionManager()
	{
		for (auto& classFieldMap : m_classFieldMap)
		{
			for (auto& classField : classFieldMap.second)
			{
				SAFE_DELETE_SETNULL(classField);
			}
		}

		for (auto& classMethodMap : m_classMethodMap)
		{
			for (auto& classMethod : classMethodMap.second)
			{
				SAFE_DELETE_SETNULL(classMethod);
			}
		}
	}
}

