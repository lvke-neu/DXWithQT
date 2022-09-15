/************************************************************************
Author: lvke
Date:2022/09/14 21:47
Description:
相机管理类，设置相机属性（相机飞行、线框模式等等）
************************************************************************/

#pragma once

#include "ManagerInterface.h"


class EffectManager : public IManager
{
public:
	enum BasicPrimitive
	{
		Box,
		Sphere
	};

	EffectManager(void** parameter);
	virtual ~EffectManager();
public:
	void buildBasicPrimitiveEffect(void** parameter, BasicPrimitive type);

	void* setBoxEffect(void** parameter);
	void* setSphereEffect(void** parameter);
	void* setModelEffect(void** parameter);
	void* clearAllEffects(void** parameter);


	void runFunction(const std::string functionName, void** parameter) override;

};