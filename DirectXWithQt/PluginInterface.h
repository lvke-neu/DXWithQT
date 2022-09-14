#pragma once

class IPlugin
{

public:
	IPlugin() = default;
	virtual ~IPlugin() = default;
	virtual void init(){}
};