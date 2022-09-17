#include "Service.h"
#include "Reflection.h"
#include "CameraManager.h"
#include"rapidjson/document.h"

void Service::call(const std::string& jsonContent, GameApp* gameApp)
{
	rapidjson::Document document;
	if (!document.Parse(jsonContent.c_str()).HasParseError())
	{
		std::string managerName;
		std::string functionName;
		rapidjson::Value funcParameter;

		if (document.HasMember("serviceId"))
		{
			managerName = document["serviceId"].GetString();
		}

		if (document.HasMember("functionName"))
		{
			functionName = document["functionName"].GetString();
		}

		if (document.HasMember("funcParameter"))
		{
			funcParameter = document["funcParameter"];
		}

		IManager* pManager = Reflection<IManager>::getInstance().createObject(managerName, nullptr);
		if (pManager)
		{
			if (gameApp && gameApp->getScene())
			{
				XMFLOAT3 pos_rot(0, 0, 0);

				void* parameter[2];

				parameter[0] = gameApp;
				parameter[1] = &funcParameter;

				pManager->runFunction(functionName, parameter);
			}
		}

		//if (pManager)
		//{
		//	delete pManager;
		//	pManager = nullptr;
		//}

	}

}