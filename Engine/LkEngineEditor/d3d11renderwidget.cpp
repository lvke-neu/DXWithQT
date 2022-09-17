#include <QKeyEvent>
#include "d3d11renderwidget.h"



#include <QDockWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QColorDialog>


D3d11RenderWidget::D3d11RenderWidget(QWidget *parent)
	: QWidget(parent)
{
	m_parent = parent;

	setAttribute(Qt::WA_PaintOnScreen,true);
	setAttribute(Qt::WA_NativeWindow,true);
	setFocusPolicy(Qt::StrongFocus);
	setMouseTracking(true);


	m_gameApp = new GameApp((HWND)winId(), width(), height());
	m_Timer.Start();
	m_Timer.Reset();
}

D3d11RenderWidget::~D3d11RenderWidget()
{
	if (m_gameApp)
	{
		delete m_gameApp;
		m_gameApp = nullptr;
	}
}


void D3d11RenderWidget::paintEvent(QPaintEvent *event)
{
	m_Timer.Tick();
	CalculateFrameStats();
	m_gameApp->UpdateScene(m_Timer.DeltaTime());
	m_gameApp->DrawScene();
	
	

	update();
}

void D3d11RenderWidget::resizeEvent(QResizeEvent *event)
{
	m_gameApp->OnResize(width(), height());
	
}


void D3d11RenderWidget::keyPressEvent(QKeyEvent *event)
{
	m_gameApp->onKeyPress(event->key());
}

void D3d11RenderWidget::keyReleaseEvent(QKeyEvent *event)
{
	m_gameApp->onKeyRelease(event->key());

}


void D3d11RenderWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
	{
		m_button = Qt::RightButton;
		m_preCursorPos = event->pos();
	}
	else if (event->button() == Qt::LeftButton)
	{
		m_gameApp->onLeftButtonPress(event->pos().x(), event->pos().y());
	}
}



void D3d11RenderWidget::mouseMoveEvent(QMouseEvent *event)
{
	m_gameApp->onMouseMove(event->pos().x(), event->pos().y());
	if (m_button == Qt::RightButton)
	{
		m_gameApp->onRightButtonMove(event->pos().x() - m_preCursorPos.x(), event->pos().y() - m_preCursorPos.y());
		m_preCursorPos = event->pos();

		repaint();
	}

}

void D3d11RenderWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (m_button == Qt::RightButton)
	{
		m_button = Qt::NoButton;
		
	}

	m_gameApp->onButtonRelease();
}

void D3d11RenderWidget::wheelEvent(QWheelEvent *event)
{

}

void D3d11RenderWidget::CalculateFrameStats()
{

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	if ((m_Timer.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::string str = "FPS:" + std::to_string(fps);
		m_parent->setWindowTitle(QString(str.c_str()));


		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

