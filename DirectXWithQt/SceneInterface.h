/************************************************************************
Author: lvke
Date:2022/7/2 9:41
Description:
场景接口类，每个章节的场景均继承自该类
************************************************************************/

#pragma once 
class IScene
{
public:
	virtual ~IScene() = default;
public:
	virtual void initScene() = 0;
	virtual void updateScene() = 0;
	virtual void drawScene() = 0;
};