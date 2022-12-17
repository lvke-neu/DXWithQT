/***************************************************************************************
Author: lvke
Date:2022/12/17 12:30
Description:
Serialization Manager based on RTTR
****************************************************************************************/
#pragma once
#include <rttr/type>
#include "Runtime/Interface/SingletonInterface.h"
#include "RegisterAllClass.h"

namespace Twinkle
{
	class SerializationManager
	{
		FRIEND_SINGLETON(SerializationManager);
		PRIVATE_CONSTRUCTOR(SerializationManager);
	public:
		void Serialize(rttr::instance obj_In, std::string& jsonStr_Out);
		void UnSerialize(std::string& jsonStr_In, rttr::instance obj_Out);
	};
}
