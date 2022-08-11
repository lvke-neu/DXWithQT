/***************************************************************************************
Author: lvke
Date:2022/7/18 22:28
Description:
监听事件接口，当场景中的相机变换（scale、rotation、position）时,通知右边的dockwidget
兼顾连接dx与qt的桥梁
****************************************************************************************/

#pragma once
#include <vector>
#include <string>

class ChapterDockWidget;

class ListeningEvent
{
public:
	void registerListeningEvent(ChapterDockWidget* chapterDockWidget);
	void unregisterListeningEvent(ChapterDockWidget* chapterDockWidget);
	void notifyAll(const std::string& msg);
	void messaegeBox(const std::string& msg);
	void stopTimer();
	void startTimer();
private:
	std::vector<ChapterDockWidget*> m_chapDockWidgets;
};