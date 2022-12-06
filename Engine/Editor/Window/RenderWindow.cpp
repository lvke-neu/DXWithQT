#include <qevent.h>
#include "RenderWindow.h"
#include "Runtime/Core/Engine/Engine.h"
#include "Runtime/Core/Event/InputEventManager.h"
#include "Runtime/Core/Event/TickEventManager.h"

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
		Singleton<TickEventManager>::GetInstance().NotifyTick(Singleton<Engine>::GetInstance().GetDeltaTime());
	}

	void RenderWindow::resizeEvent(QResizeEvent* event)
	{
		Singleton<RenderSystem>::GetInstance().OnResize(width(), height());
	}

	void RenderWindow::keyPressEvent(QKeyEvent* event)
	{
		Singleton<InputEventManager>::GetInstance().NotifyKeyPress((KeyBoard)event->key());
	}

	void RenderWindow::keyReleaseEvent(QKeyEvent* event)
	{
		Singleton<InputEventManager>::GetInstance().NotifyKeyRelease((KeyBoard)event->key());
	}

	void RenderWindow::mousePressEvent(QMouseEvent * event)
	{
		MouseState mouseState;
		mouseState.mouseButton = (MouseButton)event->button();
		mouseState.x = event->pos().x();
		mouseState.y = event->pos().y();

		Singleton<InputEventManager>::GetInstance().NotifyMousePress(mouseState);
	}

	void RenderWindow::mouseReleaseEvent(QMouseEvent * event)
	{
		MouseState mouseState;
		mouseState.mouseButton = (MouseButton)event->button();
		mouseState.x = event->pos().x();
		mouseState.y = event->pos().y();

		Singleton<InputEventManager>::GetInstance().NotifyMouseRelease(mouseState);
	}

	void RenderWindow::mouseMoveEvent(QMouseEvent * event)
	{
		MouseState mouseState;

		if (event->buttons() == Qt::NoButton)
		{
			mouseState.mouseButton = NoButton;
		}
		else if (event->buttons() == Qt::LeftButton)
		{
			mouseState.mouseButton = LeftButton;
		}
		else if (event->buttons() == Qt::RightButton)
		{
			mouseState.mouseButton = RightButton;
		}
		else if (event->buttons() == Qt::MiddleButton)
		{
			mouseState.mouseButton = MiddleButton;
		}

		mouseState.x = event->pos().x();
		mouseState.y = event->pos().y();

		Singleton<InputEventManager>::GetInstance().NotifyMouseMove(mouseState);
	}

	void RenderWindow::wheelEvent(QWheelEvent * event)
	{
		MouseState mouseState;
		mouseState.x = event->pos().x();
		mouseState.y = event->pos().y();
		mouseState.delta = event->delta();

		Singleton<InputEventManager>::GetInstance().NotifyMouseWheel(mouseState);
	}
}

