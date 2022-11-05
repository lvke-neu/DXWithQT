#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "ui_LkEngineEditor.h"
#include "RenderWindow.h"
#include "../LkEngineRuntime/Core/Event/PickEventManager.h"

namespace Ui {
	class LkEngineEditor;
}


namespace LkEngine
{
	class LkEngineEditor : public QMainWindow, public AddComponentEvent, public DeleteComponentEvent
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

		virtual void onAddComponent(IComponent* component) override;
		virtual void onDeleteComponent(IComponent* component) override;

	private:
		void initUi();
		void initDialog();
	private:
		Ui::LkEngineEditor *ui;
		RenderWindow* m_renderWindow{ nullptr };

		QDialog* m_skyboxDlg{ nullptr };
		QDialog* m_cameraDlg{ nullptr };
		QDialog* m_addComDlg{ nullptr };
	};
}


#endif // MAINWINDOW_H
