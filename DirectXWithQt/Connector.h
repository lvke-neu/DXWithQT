/************************************************************************
Author: lvke
Date:2022/7/9 12:26
Description:
连接器，连接渲染窗口与右侧DockWidget
************************************************************************/

#pragma once
#include "ChapterDockWidget.h"
class Connector
{
public:
	static void reg(ChapterDockWidget* chapterDockWidget)
	{
		chapterDockWidget_ = chapterDockWidget;
	}
	
	static void notify(float test)
	{
		chapterDockWidget_->callbackFromGameApp(test);
	}

public:
	static ChapterDockWidget* chapterDockWidget_;
};

