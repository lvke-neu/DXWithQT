#include "SerializationManager.h"
#include "Reflection.h"

namespace LkEngine
{

	void SerializationManager::serialize(Reference* reference, std::string& outSerializationStr)
	{
		if (reference)
		{
			reference->serialize(outSerializationStr);
		}
	}

	void SerializationManager::unSerialize(Reference*& reference, const std::string& inSerializationStr, void** parameter)
	{
		rapidjson::Document document;
		
		if (!document.Parse(inSerializationStr.c_str()).HasParseError())
		{
			if (document.HasMember("classType"))
			{
				reference = Reflection<Reference>::getInstance().createObject(document["classType"].GetString(), parameter);
				if (reference)
				{
					unsigned int arrSize = document["functionName"].GetArray().Size();
					for (unsigned int i = 0; i < arrSize; i++)
					{
						std::string funcname = document["functionName"][i].GetString();
						rapidjson::Value& funcpara = document["funcParameter"][i];
						reference->runFunction(funcname, funcpara);
					}
				}
			}
		}
	}
}