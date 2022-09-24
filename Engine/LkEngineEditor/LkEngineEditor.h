#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "ui_LkEngineEditor.h"
#include "RenderWindow.h"

namespace Ui {
	class LkEngineEditor;
}


namespace LkEngine
{
	class LkEngineEditor : public QMainWindow
	{
		Q_OBJECT


	public:
		explicit LkEngineEditor(QWidget *parent = nullptr);
		~LkEngineEditor();


	private:
		Ui::LkEngineEditor *ui;
		RenderWindow* m_renderWindow{ nullptr };

	};
}


#endif // MAINWINDOW_H
