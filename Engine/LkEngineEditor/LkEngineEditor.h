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
	public slots:
		void openSolution();
		void saveSolution();
		void skyboxConfig();
		void cameraConfig();
		void addComponent();
		void sceneComConfig();
		void setDragType();
		void lightConfig();
	private:
		void initUi();
		void initDialog();
	private:
		Ui::LkEngineEditor *ui;
		RenderWindow* m_renderWindow{ nullptr };

		QDialog* m_skyboxDlg{ nullptr };
		QDialog* m_cameraDlg{ nullptr };
		QDialog* m_addComDlg{ nullptr };
		QDialog* m_sceneComCfgDlg{ nullptr };
		QDialog* m_lightDlg{ nullptr };
	};
}


#endif // MAINWINDOW_H
