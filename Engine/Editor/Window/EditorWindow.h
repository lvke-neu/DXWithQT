#pragma once

#include "ui_EditorWindow.h"

namespace Twinkle
{
	class RenderWindow;
	class EditorWindow : public QMainWindow
	{
		Q_OBJECT
	public:
		explicit EditorWindow(QWidget *parent = nullptr);
		~EditorWindow();

		virtual void timerEvent(QTimerEvent* event) override;
	private:
		Ui::EditorWindow*ui;
		RenderWindow* m_renderWindow{ nullptr };
	};
}

