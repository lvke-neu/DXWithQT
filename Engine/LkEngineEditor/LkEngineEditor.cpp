#include "LkEngineEditor.h"
#include "../LkEngineRuntime/Core/base/Utility.h"

#include <qdockwidget.h>


#include "CustomToolBox/Form.h"
#include "CustomToolBox/SkyBoxForm.h"
#include "CustomToolBox/CameraForm.h"
#include "CustomToolBox/ComponentFrom.h"
namespace LkEngine
{
	LkEngineEditor::LkEngineEditor(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::LkEngineEditor)
	{
		ui->setupUi(this);
		setWindowIcon(QIcon(":/builtin/EngineLogo/logo.png"));

		m_renderWindow = new RenderWindow(this);
		setCentralWidget(m_renderWindow);

		m_sceneCfgToolBox = new ToolBox(m_renderWindow);
		m_sceneCfgToolBox->addWidget(QString("SkyBox"), new SkyBoxForm());
		m_sceneCfgToolBox->addWidget(QString("Camera"), new CameraForm());
		m_sceneCfgToolBox->addWidget(QString("Component"), new ComponentFrom());
		m_sceneCfgToolBox->hide();
		
		connect(ui->openSceneCfg, SIGNAL(triggered()),this, SLOT(openSceneCfg()));
		connect(ui->closeSceneCfg, SIGNAL(triggered()), this, SLOT(closeSceneCfg()));

		LOG_INFO("Window initialization is complete");
	}

	LkEngineEditor::~LkEngineEditor()
	{
		SAFE_DELETE_SET_NULL(m_sceneCfgToolBox);
		SAFE_DELETE_SET_NULL(m_renderWindow);
		SAFE_DELETE_SET_NULL(ui);
		
	}

	void LkEngineEditor::openSceneCfg()
	{
		m_sceneCfgToolBox->show();
	}

	void LkEngineEditor::closeSceneCfg()
	{
		m_sceneCfgToolBox->hide();
	}

}


