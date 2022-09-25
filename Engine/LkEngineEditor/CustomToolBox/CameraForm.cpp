#include "CameraForm.h"
#include "ui_CameraForm.h"
#include "../../LkEngineRuntime/Core/base/Utility.h"
#include "../../LkEngineRuntime/Core/engine/Engine.h"
#include "ToolPage.h"
#include "../../LkEngineRuntime/Scene/Component/Common/Transform.h"

CameraForm::CameraForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::CameraForm)
{
	ui->setupUi(this);

	connect(ui->radioButton, SIGNAL(toggled(bool)), this, SLOT(setWireFrame(bool)));

	connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setCameraTransform()));
	connect(ui->doubleSpinBox_2, SIGNAL(valueChanged(double)), this, SLOT(setCameraTransform()));
	connect(ui->doubleSpinBox_3, SIGNAL(valueChanged(double)), this, SLOT(setCameraTransform()));

	connect(ui->doubleSpinBox_4, SIGNAL(valueChanged(double)), this, SLOT(setCameraTransform()));
	connect(ui->doubleSpinBox_5, SIGNAL(valueChanged(double)), this, SLOT(setCameraTransform()));
	connect(ui->doubleSpinBox_6, SIGNAL(valueChanged(double)), this, SLOT(setCameraTransform()));

	connect(ui->doubleSpinBox_7, SIGNAL(valueChanged(double)), this, SLOT(setCameraTransform()));
	connect(ui->doubleSpinBox_8, SIGNAL(valueChanged(double)), this, SLOT(setCameraTransform()));
	connect(ui->doubleSpinBox_9, SIGNAL(valueChanged(double)), this, SLOT(setCameraTransform()));

	connect(ui->doubleSpinBox_10, SIGNAL(valueChanged(double)), this, SLOT(setCameraFrustum()));
	connect(ui->doubleSpinBox_11, SIGNAL(valueChanged(double)), this, SLOT(setCameraFrustum()));
	connect(ui->doubleSpinBox_12, SIGNAL(valueChanged(double)), this, SLOT(setCameraFrustum()));
	connect(ui->doubleSpinBox_13, SIGNAL(valueChanged(double)), this, SLOT(setCameraFrustum()));

	CameraChangedManager::getInstance().registerCameraMoveEvent(this);
	CameraChangedManager::getInstance().registerCameraFrustumChangedEvent(this);
}

CameraForm::~CameraForm()
{
	CameraChangedManager::getInstance().unRegisterCameraMoveEvent(this);
	CameraChangedManager::getInstance().unRegisterCameraFrustumChangedEvent(this);
	delete ui;
}

void CameraForm::setWireFrame(bool b)
{
	Engine::getInstance().setWireFrame(b);
	std::string loginfo = b ? "true" : "false";
	LOG_INFO(loginfo)
}


void CameraForm::onCameraMove()
{
	if (ToolPage::m_bIsExpanded)
	{
		Transform transform = Engine::getInstance().getCameraTransform();
		XMFLOAT3 scale = transform.getScale();
		XMFLOAT3 rot = transform.getRotation();
		XMFLOAT3 pos = transform.getPosition();

		ui->doubleSpinBox->setValue(scale.x);
		ui->doubleSpinBox_2->setValue(scale.y);
		ui->doubleSpinBox_3->setValue(scale.z);

		ui->doubleSpinBox_4->setValue(rot.x);
		ui->doubleSpinBox_5->setValue(rot.y);
		ui->doubleSpinBox_6->setValue(rot.z);

		ui->doubleSpinBox_7->setValue(pos.x);
		ui->doubleSpinBox_8->setValue(pos.y);
		ui->doubleSpinBox_9->setValue(pos.z);

		update();
		
	}

}

void CameraForm::onCameraFrustumChanged()
{
	float FovAngleY; 
	float AspectRatio;
	float NearZ;  
	float FarZ;
	Engine::getInstance().getCameraFrustum(FovAngleY, AspectRatio, NearZ, FarZ);
	ui->doubleSpinBox_10->setValue(FovAngleY);
	ui->doubleSpinBox_11->setValue(AspectRatio);
	ui->doubleSpinBox_12->setValue(NearZ);
	ui->doubleSpinBox_13->setValue(FarZ);

	update();
}


void CameraForm::setCameraTransform()
{

	XMFLOAT3 scale(ui->doubleSpinBox->value(), ui->doubleSpinBox_2->value(), ui->doubleSpinBox_3->value());
	XMFLOAT3 rot(ui->doubleSpinBox_4->value(), ui->doubleSpinBox_5->value(), ui->doubleSpinBox_6->value());
	XMFLOAT3 pos(ui->doubleSpinBox_7->value(), ui->doubleSpinBox_8->value(), ui->doubleSpinBox_9->value());
	LkEngine::Transform transform(scale, rot, pos);
	Engine::getInstance().setCameraTransform(transform);

	//LOG_INFO(transform.to_string())

}


void CameraForm::setCameraFrustum()
{
	Engine::getInstance().setCameraFrustum(ui->doubleSpinBox_10->value(), ui->doubleSpinBox_11->value(), ui->doubleSpinBox_12->value(), ui->doubleSpinBox_13->value());
}