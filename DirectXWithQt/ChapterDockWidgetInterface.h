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
#include "d3d11renderwidget.h"
#include "EventManager.h"

#define SAFE_RELEASE_SET_NULL(p) { if ((p)) { delete (p); (p) = nullptr; } }

class IChapterDockWidget : public QObject, public CameraMoveEvent, public PickEvent
{
	Q_OBJECT
public:
	IChapterDockWidget() = default;
	IChapterDockWidget(void** parameters);
	virtual ~IChapterDockWidget();
	virtual void init() = 0;
	virtual void onCameraMove(const std::string& msg){}
	virtual void onPickGameObject(GameObject& go) {};
	virtual void onMouseLocateGo(const std::string& msg) {};
	void hide();

protected:
	QMainWindow* m_parentWindow{ nullptr };
	QDockWidget* m_dockWidget{ nullptr };
	D3d11RenderWidget* m_renderWidget{ nullptr };
};