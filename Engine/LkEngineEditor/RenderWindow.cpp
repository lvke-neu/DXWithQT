#include "RenderWindow.h"
#include "../LkEngineRuntime/Core/engine/Engine.h"
#include "../LkEngineRuntime/Core/base/Utility.h"

namespace LkEngine
{
	RenderWindow::RenderWindow(QWidget *parent)
		: QWidget(parent)
	{
		m_parent = parent;

		setAttribute(Qt::WA_PaintOnScreen, true);
		setAttribute(Qt::WA_NativeWindow, true);
		setFocusPolicy(Qt::StrongFocus);
		setMouseTracking(true);

		Engine::getInstance().initialize((HWND)winId(), m_parent->width(), m_parent->height());
		LOG_INFO("Engine initialization is complete");
		

		m_Timer.Start();
		m_Timer.Reset();
	}

	RenderWindow::~RenderWindow()
	{

	}


	void RenderWindow::paintEvent(QPaintEvent *event)
	{
		m_Timer.Tick();
		CalculateFrameStats();

		Engine::getInstance().updateScene(m_Timer.DeltaTime());
		Engine::getInstance().drawScene();

		update();
	}

	void RenderWindow::resizeEvent(QResizeEvent *event)
	{
		Engine::getInstance().onResize(m_parent->width(), m_parent->height());
		LOG_INFO("Render Window On Resize: Width = " + std::to_string(m_parent->width()) + ", Height = " + std::to_string(m_parent->height()));
	}


	void RenderWindow::keyPressEvent(QKeyEvent *event)
	{

	}

	void RenderWindow::keyReleaseEvent(QKeyEvent *event)
	{


	}


	void RenderWindow::mousePressEvent(QMouseEvent *event)
	{

	}



	void RenderWindow::mouseMoveEvent(QMouseEvent *event)
	{


	}

	void RenderWindow::mouseReleaseEvent(QMouseEvent *event)
	{

	}

	void RenderWindow::wheelEvent(QWheelEvent *event)
	{

	}

	void RenderWindow::CalculateFrameStats()
	{

		static int frameCnt = 0;
		static float timeElapsed = 0.0f;

		frameCnt++;

		if ((m_Timer.TotalTime() - timeElapsed) >= 1.0f)
		{
			float fps = (float)frameCnt; // fps = frameCnt / 1
			float mspf = 1000.0f / fps;

			std::string str = "LK-Engine  FPS:" + std::to_string(fps);
			m_parent->setWindowTitle(QString(str.c_str()));


			// Reset for next average.
			frameCnt = 0;
			timeElapsed += 1.0f;
		}
	}


}

