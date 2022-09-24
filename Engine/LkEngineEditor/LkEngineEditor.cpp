#include "LkEngineEditor.h"
#include "../LkEngineRuntime/Core/base/Utility.h"

#include <qdockwidget.h>

#include "CustomToolBox/ToolBox.h"
#include "CustomToolBox/Form.h"
#include "CustomToolBox/SkyBoxForm.h"
#include "CustomToolBox/CameraForm.h"

namespace LkEngine
{
	LkEngineEditor::LkEngineEditor(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::LkEngineEditor)
	{
		ui->setupUi(this);
		setWindowIcon(QIcon(":/builtin/EngineLogo/logo.png"));

		m_renderWindow = new RenderWindow(this);
		
		ToolBox* toolBox = new ToolBox(m_renderWindow);
		toolBox->addWidget(QString("SkyBox"), new SkyBoxForm());
		toolBox->addWidget(QString("Camera"), new CameraForm());
		toolBox->addWidget(QString("Component"), new Form());

		
		setCentralWidget(m_renderWindow);

		LOG_INFO("Window initialization is complete");
	}

	LkEngineEditor::~LkEngineEditor()
	{
		SAFE_DELETE_SET_NULL(ui);
	}

}


