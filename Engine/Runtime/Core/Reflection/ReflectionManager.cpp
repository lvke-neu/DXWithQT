#include "ReflectionManager.h"

namespace Twinkle
{
	void ReflectionManager::register_class(const std::string & className, create_object method)
	{
		m_classMap[className] = method;
	}

	ReflectionObject* ReflectionManager::create_class(const std::string & className)
	{
		auto iter = m_classMap.find(className);
		
		return iter == m_classMap.end() ? nullptr : iter->second();
	}
}

