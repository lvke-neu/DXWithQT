/************************************************************************
Author: lvke
Date:2022/6/26 14:45
Description:
DirectX渲染到的widget
************************************************************************/

#pragma once
#include <QWidget>
#include "gameApp.h"
#include "GameTimer.h"


class ChapterDockWidget;

class D3d11RenderWidget : public QWidget
{
	Q_OBJECT

		friend ChapterDockWidget;
public:
	D3d11RenderWidget(QWidget *parent);
	~D3d11RenderWidget();
	virtual QPaintEngine *paintEngine() const
	{
		return NULL;
	}

private:
	virtual void resizeEvent(QResizeEvent *event) override; 
	virtual void paintEvent(QPaintEvent *event) override;  

	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent *event);
	
	void CalculateFrameStats();

private:
	QWidget* m_parent{ nullptr };
	GameApp* m_gameApp{ nullptr };
	GameTimer m_Timer;
                    
};


