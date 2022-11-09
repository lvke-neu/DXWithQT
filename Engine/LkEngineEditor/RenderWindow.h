/***************************************************************************************
Author: lvke
Date:2022/9/18 11:29
Description:
The render window
****************************************************************************************/

#pragma once

#include <QWidget>
#include <QLabel>
#include "../LkEngineRuntime/Core/engine/Engine.h"
#include "../LkEngineRuntime/Core/engine/GameTimer.h"
#include "../LkEngineRuntime/Core/Event/PickEventManager.h"

namespace LkEngine
{
	class RenderWindow : public QWidget, public AddComponentEvent, public DeleteComponentEvent
	{
		Q_OBJECT

	public:
		RenderWindow(QWidget *parent);
		~RenderWindow();
		virtual QPaintEngine *paintEngine() const
		{
			return NULL;
		}
	public:
		virtual void onAddComponent(IComponent* component) override;
		virtual void onDeleteComponent(IComponent* component) override;
	private:
		virtual void resizeEvent(QResizeEvent *event) override;
		virtual void paintEvent(QPaintEvent *event) override;

		virtual void keyPressEvent(QKeyEvent *event) override;
		virtual void keyReleaseEvent(QKeyEvent *event) override;
		virtual void mousePressEvent(QMouseEvent *event) override;
		virtual void mouseReleaseEvent(QMouseEvent *event) override;
		virtual void mouseMoveEvent(QMouseEvent *event) override;
		virtual void wheelEvent(QWheelEvent *event) override;

		void QMouseEvent2MouseState(QMouseEvent* event, MouseState& ms);
		void CalculateFrameStats();

	private:
		QWidget* m_parent{ nullptr };
		QLabel* m_label{ nullptr };
		GameTimer m_Timer;

	};

}

