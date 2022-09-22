#include "CameraForm.h"
#include "ui_CameraForm.h"
#include "../../LkEngineRuntime/Core/base/Utility.h"
#include "../../LkEngineRuntime/Core/engine/Engine.h"

CameraForm::CameraForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraForm)
{
    ui->setupUi(this);
	
	connect(ui->radioButton, SIGNAL(toggled(bool)), this, SLOT(setWireFrame(bool)));
}

CameraForm::~CameraForm()
{
    delete ui;
}

void CameraForm::setWireFrame(bool b)
{
	Engine::getInstance().setWireFrame(b);
	std::string loginfo = b ? "true" : "false";
	LOG_INFO(loginfo)
}