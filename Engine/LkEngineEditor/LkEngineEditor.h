#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "ui_LkEngineEditor.h"


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


	};
}


#endif // MAINWINDOW_H
