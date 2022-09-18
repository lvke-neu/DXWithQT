/***************************************************************************************
Author: lvke
Date:2022/9/18 11:29
Description:
The render window
****************************************************************************************/

#pragma once

#include <QWidget>

#include "../LkEngineRuntime/Core/engine/GameTimer.h"


namespace LkEngine
{
	class RenderWindow : public QWidget
	{
		Q_OBJECT

	public:
		RenderWindow(QWidget *parent);
		~RenderWindow();
		virtual QPaintEngine *paintEngine() const
		{
			return NULL;
		}

	private:
		virtual void resizeEvent(QResizeEvent *event) override;
		virtual void paintEvent(QPaintEvent *event) override;

		virtual void keyPressEvent(QKeyEvent *event) override;
		virtual void keyReleaseEvent(QKeyEvent *event) override;
		virtual void mousePressEvent(QMouseEvent *event) override;
		virtual void mouseReleaseEvent(QMouseEvent *event) override;
		virtual void mouseMoveEvent(QMouseEvent *event) override;
		virtual void wheelEvent(QWheelEvent *event) override;

		void CalculateFrameStats();

	private:
		QWidget* m_parent{ nullptr };
		GameTimer m_Timer;

	};

}

