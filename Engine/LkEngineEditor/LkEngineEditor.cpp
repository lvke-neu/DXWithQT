#include "LkEngineEditor.h"
#include "../LkEngineRuntime/Core/Utility.h"


namespace LkEngine
{
	LkEngineEditor::LkEngineEditor(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::LkEngineEditor)
	{
		ui->setupUi(this);
		setWindowIcon(QIcon("EngineLogo/logo.png"));

	}

	LkEngineEditor::~LkEngineEditor()
	{
		SAFE_DELETE_SET_NULL(ui);
	}

}


