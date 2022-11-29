/***************************************************************************************
Author: lvke
Date:2022/11/28 21:56
Description:
Serialization Manager
****************************************************************************************/
#pragma once

#include <string>
#include "../Interface/SingletonInterface.h"

namespace Twinkle
{
	class ReflectionObject;
	class SerializationManager
	{
		FRIEND_SINGLETON(SerializationManager);
	public:
		void Serialize(ReflectionObject* objectIn, std::string& objectDesOut);
		void Unserialize(const std::string& objectDesIn, ReflectionObject*& objectOut);
	};
}
