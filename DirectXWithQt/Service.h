#pragma once

#include <string>
#include "gameApp.h"
class Service
{

public:
	void call(const std::string& jsonContent, GameApp* gameApp);



private:
	Service() {}
	~Service() {}
	Service(const Service& service) {}
	Service& operator = (const Service& service) {}

public:
	static Service& getInstance()
	{
		static Service instance;
		return instance;
	}
};