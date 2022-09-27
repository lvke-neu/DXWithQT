#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "ui_LkEngineEditor.h"
#include "RenderWindow.h"
#include "CustomToolBox/ToolBox.h"
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
		void openSceneCfg();
		void closeSceneCfg();
		virtual void onAddComponent(IComponent* component) override;
		virtual void onDeleteComponent(IComponent* component) override;
		
	private:
		Ui::LkEngineEditor *ui;
		RenderWindow* m_renderWindow{ nullptr };
		ToolBox* m_sceneCfgToolBox{ nullptr };
	};
}


#endif // MAINWINDOW_H
