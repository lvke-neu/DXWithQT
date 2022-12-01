/***************************************************************************************
Author: lvke
Date:2022/11/30 21:34
Description:
Render Window
****************************************************************************************/
#pragma once

#include <QWidget>

namespace  Twinkle
{
	class RenderWindow : public QWidget
	{
		Q_OBJECT

	public:
		RenderWindow(QWidget* parent);
		~RenderWindow();
		virtual QPaintEngine* paintEngine() const
		{
			return NULL;
		}

		virtual void timerEvent(QTimerEvent* event) override;
		virtual void resizeEvent(QResizeEvent* event) override;
	};
}

