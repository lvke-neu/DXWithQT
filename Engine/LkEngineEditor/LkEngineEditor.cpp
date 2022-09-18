#include "LkEngineEditor.h"
#include "../LkEngineRuntime/Core/base/Utility.h"


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
	}

	LkEngineEditor::~LkEngineEditor()
	{
		SAFE_DELETE_SET_NULL(ui);
	}

}


