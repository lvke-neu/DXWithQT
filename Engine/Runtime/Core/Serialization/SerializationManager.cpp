#include "SerializationManager.h"
#include "../Reflection/ReflectionManager.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace Twinkle
{
	void SerializationManager::Serialize(ReflectionObject* objectIn, std::string& objectDesOut)
	{
		objectDesOut = "";
		if (objectIn)
		{
			
			rapidjson::StringBuffer strBuf;
			rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);

			writer.StartObject();

			//1¡¢serialize class 
			writer.Key("classType");
			writer.String(objectIn->get_class_name().c_str());

			//2¡¢serialize field
			size_t size = objectIn->get_field_count();
			for (size_t i = 0; i < size; i++)
			{
				ClassField* classField = objectIn->get_field(i);
				writer.Key(classField->name().c_str());
				
				std::string str;
				objectIn->get(classField->name(), str);
			}

			writer.EndObject();

			objectDesOut = strBuf.GetString();
		}
	}

	void SerializationManager::Unserialize(const std::string& objectDesIn, ReflectionObject*& objectOut)
	{
		objectOut = nullptr;
		rapidjson::Document document;
		if (!document.Parse(objectDesIn.c_str()).HasParseError())
		{
			if (document.HasMember("classType"))
			{
				objectOut = Singleton<ReflectionManager>::GetInstance().create_class(document["classType"].GetString());
			}
		}
	}
}
