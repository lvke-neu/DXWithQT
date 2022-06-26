#include <QKeyEvent>
#include "d3d11renderwidget.h"
#include "d3dUtil.hpp"


D3d11RenderWidget::D3d11RenderWidget(QWidget *parent)
	: QWidget(parent)
{
	m_parent = parent;

	setAttribute(Qt::WA_PaintOnScreen,true);
	setAttribute(Qt::WA_NativeWindow,true);

	m_gameApp = new GameApp((HWND)winId(), width(), height());
	m_Timer.Start();
	m_Timer.Reset();

}

D3d11RenderWidget::~D3d11RenderWidget()
{
	SAFERELEASE(m_gameApp);
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
	
	
}

void D3d11RenderWidget::keyReleaseEvent(QKeyEvent *event)
{

}


void D3d11RenderWidget::mousePressEvent(QMouseEvent *event)
{


}

void D3d11RenderWidget::mouseReleaseEvent(QMouseEvent *event)
{

}

void D3d11RenderWidget::mouseMoveEvent(QMouseEvent *event)
{
	
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

