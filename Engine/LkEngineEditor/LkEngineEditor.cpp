#include "LkEngineEditor.h"
#include "../LkEngineRuntime/Core/base/Utility.h"
#include <qdockwidget.h>
#include <qfiledialog.h>
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
		
		initUi();
		initDialog();

		m_renderWindow = new RenderWindow(this);
		setCentralWidget(m_renderWindow);

		LOG_INFO("Window initialization is complete");
	}

	LkEngineEditor::~LkEngineEditor()
	{
		SAFE_DELETE_SET_NULL(m_skyboxDlg);
		SAFE_DELETE_SET_NULL(m_cameraDlg);
		SAFE_DELETE_SET_NULL(m_addComDlg);
		SAFE_DELETE_SET_NULL(m_sceneComCfgDlg);
		SAFE_DELETE_SET_NULL(m_renderWindow);
		SAFE_DELETE_SET_NULL(ui);
	}
	
	void LkEngineEditor::initUi()
	{
		setWindowIcon(QIcon(":/builtin/EngineLogo/logo.png"));
		this->setStyleSheet("QMenu::item:selected{background-color:rgb(0,100,200);}\
                         QMenuBar{background-color:rgb(200,200,200);}");

		ui->openSolution->setIcon(QIcon(":/builtin/EngineLogo/open.jpeg"));
		ui->saveSolution->setIcon(QIcon(":/builtin/EngineLogo/save.jpeg"));
		ui->skybox->setIcon(QIcon(":/builtin/EngineLogo/skybox.jpeg"));
		ui->camera->setIcon(QIcon(":/builtin/EngineLogo/camera.jpeg"));
		ui->light->setIcon(QIcon(":/builtin/EngineLogo/light.jpeg"));
		ui->addComponent->setIcon(QIcon(":/builtin/EngineLogo/addComponent.jpeg"));
		ui->sceneComConfig->setIcon(QIcon(":/builtin/EngineLogo/sceneComConfig.jpeg"));
	}

	void LkEngineEditor::initDialog()
	{
		m_skyboxDlg = new SkyBoxForm(this);
		m_skyboxDlg->setWindowTitle("Skybox");
		m_skyboxDlg->setWindowIcon(QIcon(":/builtin/EngineLogo/skybox.jpeg"));
		m_skyboxDlg->hide();
		m_cameraDlg = new CameraForm(this);
		m_cameraDlg->hide();
		m_cameraDlg->setWindowTitle("Camera");
		m_cameraDlg->setWindowIcon(QIcon(":/builtin/EngineLogo/camera.jpeg"));
		m_addComDlg = new ComponentForm(this);
		m_addComDlg->hide();
		m_addComDlg->setWindowTitle("Add Component");
		m_addComDlg->setWindowIcon(QIcon(":/builtin/EngineLogo/addComponent.jpeg"));
		m_sceneComCfgDlg = new PickInfoForm(this);
		m_sceneComCfgDlg->hide();
		m_sceneComCfgDlg->setWindowTitle("Scene Component Config");
		m_sceneComCfgDlg->setWindowIcon(QIcon(":/builtin/EngineLogo/sceneComConfig.jpeg"));

		connect(ui->openSolution, SIGNAL(triggered()), this, SLOT(openSolution()));
		connect(ui->saveSolution, SIGNAL(triggered()), this, SLOT(saveSolution()));
		connect(ui->skybox, SIGNAL(triggered()), this, SLOT(skyboxConfig()));
		connect(ui->camera, SIGNAL(triggered()), this, SLOT(cameraConfig()));
		connect(ui->addComponent, SIGNAL(triggered()), this, SLOT(addComponent()));
		connect(ui->sceneComConfig, SIGNAL(triggered()), this, SLOT(sceneComConfig()));

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

	void LkEngineEditor::skyboxConfig()
	{
		if (m_skyboxDlg)
			m_skyboxDlg->show();
	}

	void LkEngineEditor::cameraConfig()
	{
		if (m_cameraDlg)
			m_cameraDlg->show();
	}

	void LkEngineEditor::addComponent()
	{
		if (m_addComDlg)
			m_addComDlg->show();
	}

	void LkEngineEditor::sceneComConfig()
	{
		if (m_sceneComCfgDlg)
			m_sceneComCfgDlg->show();
	}






}


