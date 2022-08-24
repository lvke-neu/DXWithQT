/************************************************************************
Author: lvke
Date:2022/8/23 22:59
Description:
重构dockwidget，各个章节的右侧dockwidget的基类
************************************************************************/

#pragma once 

#include <QObject>
#include <QMainWindow>
#include <QDockWidget>

#define SAFE_RELEASE_SET_NULL(p) { if ((p)) { delete (p); (p) = nullptr; } }


class IChapterDockWidget : public QObject
{
	Q_OBJECT
public:
	IChapterDockWidget() = default;
	IChapterDockWidget(QMainWindow* parent);
	virtual ~IChapterDockWidget();

	virtual void init() = 0;

	void hide()
	{
		m_dockWidget->hide();
	}
protected:
	QMainWindow* m_parentWindow{ nullptr };
	QDockWidget* m_dockWidget{ nullptr };

};