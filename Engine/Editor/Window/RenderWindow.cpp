#include "RenderWindow.h"
#include "Runtime/Core/Engine/Engine.h"


namespace  Twinkle
{
	RenderWindow::RenderWindow(QWidget* parent)
		: QWidget(parent)
	{
		setAttribute(Qt::WA_PaintOnScreen, true);
		setAttribute(Qt::WA_NativeWindow, true);
		setFocusPolicy(Qt::StrongFocus);
		setMouseTracking(true);
		startTimer(0);

		Singleton<RenderSystem>::GetInstance().Initialize((HWND)winId(), width(), height());
		Singleton<Engine>::GetInstance().Initialize();
	}

	RenderWindow::~RenderWindow()
	{

	}

	void RenderWindow::timerEvent(QTimerEvent* event)
	{
		Singleton<Engine>::GetInstance().Tick();
	}

	void RenderWindow::resizeEvent(QResizeEvent* event)
	{
		Singleton<RenderSystem>::GetInstance().OnResize(width(), height());
	}
}

