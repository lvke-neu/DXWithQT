/***************************************************************************************
Author: lvke
Date:2022/7/18 22:28
Description:
监听事件接口，当场景中的相机变换（scale、rotation、position）时,通知右边的dockwidget
****************************************************************************************/

#pragma once
#include <vector>


class ChapterDockWidget;

class ListeningEvent
{
public:
	void registerListeningEvent(ChapterDockWidget* chapterDockWidget);
	void unregisterListeningEvent(ChapterDockWidget* chapterDockWidget);
	void notifyAll(const std::string& msg);

private:
	std::vector<ChapterDockWidget*> m_chapDockWidgets;
};