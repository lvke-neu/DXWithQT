/***************************************************************************************
Author: lvke
Date:2022/9/30 09:35
Description:
The base class that implements serialization
****************************************************************************************/
#pragma once

#include <string>
#include <map>
#include <functional>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace LkEngine
{
	class Reference
	{
	public:
		Reference() = default;
		virtual ~Reference() = default;

		virtual void serialize(std::string& serializationStr) = 0;
		virtual void runFunction(const std::string& funcName, const rapidjson::Value& funcParameter) = 0;
	protected:
		std::map<std::string, std::function<void(const rapidjson::Value& funcParameter)>> m_functions;
	};
}