/************************************************************************
Author: lvke
Date:2022/09/14 21:46
Description:
各个管理类的基类
************************************************************************/

#pragma once
#include <string>
#include <map>
#include <string>
#include <functional>
#include "gameApp.h"

class IManager
{
public:
	virtual void runFunction(const std::string functionName, void** parameter) = 0;
	virtual ~IManager() {};
protected:
	std::map<std::string, std::function<void(void**)>> m_functions;
}; 