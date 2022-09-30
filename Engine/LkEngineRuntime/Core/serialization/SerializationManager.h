/***************************************************************************************
Author: lvke
Date:2022/9/30 10:03
Description:
Serialization Manager
****************************************************************************************/
#pragma once

#include "../base/SingletonInterface.h"
#include "Reference.h"

namespace LkEngine
{


	class SerializationManager : public ISingleton<SerializationManager>
	{
	public:
		void serialize(Reference* reference, std::string& outSerializationStr);
		void unSerialize(Reference*& reference, const std::string& inSerializationStr, void** parameter);
	};
}