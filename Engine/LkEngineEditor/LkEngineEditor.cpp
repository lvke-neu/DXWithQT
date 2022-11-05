#include "LkEngineEditor.h"
#include "../LkEngineRuntime/Core/base/Utility.h"
#include <qdockwidget.h>
#include <qfiledialog.h>

#include "CustomToolBox/Form.h"
#include "CustomToolBox/SkyBoxForm.h"
#include "CustomToolBox/CameraForm.h"
#include "CustomToolBox/ComponentForm.h"
#include "CustomToolBox/PickInfoForm.h"

namespace LkEngine
{
	LkEngineEditor::LkEngineEditor(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::LkEngineEditor)
	{
		ui->setupUi(this);
		setWindowIcon(QIcon(":/builtin/EngineLogo/logo.png"));
		this->setStyleSheet("QMenu::item:selected{background-color:rgb(0,100,200);}\
                         QMenuBar{background-color:rgb(200,200,200);}");
		ui->openSolution->setIcon(QIcon(":/builtin/EngineLogo/open.jpeg"));
		ui->saveSolution->setIcon(QIcon(":/builtin/EngineLogo/save.jpeg"));
		ui->skybox->setIcon(QIcon(":/builtin/EngineLogo/skybox.jpeg"));
		ui->camera->setIcon(QIcon(":/builtin/EngineLogo/camera.jpeg"));
		ui->light->setIcon(QIcon(":/builtin/EngineLogo/light.jpeg"));

		m_sceneCfgToolBox = new ToolBox(m_renderWindow);
		m_sceneCfgToolBox->addWidget("SkyBox", new SkyBoxForm());
		m_sceneCfgToolBox->addWidget("Camera", new CameraForm());
		m_sceneCfgToolBox->addWidget("Component", new ComponentForm());
		m_sceneCfgToolBox->hide();

		connect(ui->openSolution, SIGNAL(triggered()), this, SLOT(openSolution()));
		connect(ui->saveSolution, SIGNAL(triggered()), this, SLOT(saveSolution()));
		connect(ui->camera, SIGNAL(triggered()), this, SLOT(cameraConfig()));
	

		connect(ui->openSceneCfg, SIGNAL(triggered()),this, SLOT(openSceneCfg()));
		connect(ui->closeSceneCfg, SIGNAL(triggered()), this, SLOT(closeSceneCfg()));


		m_renderWindow = new RenderWindow(this);
		setCentralWidget(m_renderWindow);

		PickEventManager::getInstance().registerAddComponentEvent(this);
		PickEventManager::getInstance().registerDeleteComponentEvent(this);
		LOG_INFO("Window initialization is complete");
	}

	LkEngineEditor::~LkEngineEditor()
	{
		PickEventManager::getInstance().unRegisterAddComponentEvent(this);
		PickEventManager::getInstance().unRegisterDeleteComponentEvent(this);
		SAFE_DELETE_SET_NULL(m_sceneCfgToolBox);
		SAFE_DELETE_SET_NULL(m_renderWindow);
		SAFE_DELETE_SET_NULL(ui);
		
	}

	void LkEngineEditor::openSolution()
	{
		QString curPath, aFileName;
		curPath = QCoreApplication::applicationDirPath() + "/assets";
		aFileName = QFileDialog::getOpenFileName(this, tr("Open Solution"), curPath, tr("*.lkproject"));
		if(aFileName != "")
			Engine::getInstance().openSolution(aFileName.toStdString());
	}

	void LkEngineEditor::saveSolution()
	{
		QString curPath, aFileName;
		curPath = QCoreApplication::applicationDirPath() + "/assets";
		aFileName = QFileDialog::getSaveFileName(this, tr("Save Solution"), curPath, tr("*.lkproject"));
		if (aFileName != "")
			Engine::getInstance().saveSolution(aFileName.toStdString());
	}

	void LkEngineEditor::cameraConfig()
	{
		//CameraForm* cfm = new CameraForm();
		//cfm->show();
	}

	void LkEngineEditor::openSceneCfg()
	{
		m_sceneCfgToolBox->show();
	}

	void LkEngineEditor::closeSceneCfg()
	{
		m_sceneCfgToolBox->hide();
	}

	void LkEngineEditor::onAddComponent(IComponent* component)
	{
		m_sceneCfgToolBox->addWidget(component->getUuId(), new PickInfoForm(component));
	}

	void LkEngineEditor::onDeleteComponent(IComponent* component)
	{
		m_sceneCfgToolBox->deleteWidget(component->getUuId());
	}

}


