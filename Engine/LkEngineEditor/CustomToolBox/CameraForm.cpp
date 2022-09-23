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

static XMFLOAT3 oldScale{ 0.0f, 0.0f, 0.0f };
static XMFLOAT3 oldRot{ 0.0f, 0.0f, 0.0f };
static XMFLOAT3 oldPos{ 0.0f, 0.0f, 0.0f };
void CameraForm::paintEvent(QPaintEvent* event)
{
	XMFLOAT3 scale =  Engine::getInstance().getCameraScale();
	XMFLOAT3 rot   =  Engine::getInstance().getCameraRot();
	XMFLOAT3 pos   =  Engine::getInstance().getCameraPos();

	ui->doubleSpinBox->setValue(scale.x);
	ui->doubleSpinBox_2->setValue(scale.y);
	ui->doubleSpinBox_3->setValue(scale.z);

	ui->doubleSpinBox_4->setValue(rot.x);
	ui->doubleSpinBox_5->setValue(rot.y);
	ui->doubleSpinBox_6->setValue(rot.z);

	ui->doubleSpinBox_7->setValue(pos.x);
	ui->doubleSpinBox_8->setValue(pos.y);
	ui->doubleSpinBox_9->setValue(pos.z);
	//update();
}