#include "LkEngineEditor.h"




LkEngineEditor::LkEngineEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LkEngineEditor)
{
    ui->setupUi(this);
	setWindowIcon(QIcon("EngineLogo/logo.png"));

}

LkEngineEditor::~LkEngineEditor()
{

}


