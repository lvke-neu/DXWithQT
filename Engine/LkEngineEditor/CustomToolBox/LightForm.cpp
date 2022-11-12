#include "LightForm.h"
#include "ui_LightForm.h"
#include "../../LkEngineRuntime/Core/engine/Engine.h"

LightForm::LightForm(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::LightForm)
{
	ui->setupUi(this);
}

LightForm::~LightForm()
{
	delete ui;
}

void LightForm::initLightProperty()
{
	LkEngine::DirectionLight dirLight = LkEngine::Engine::getInstance().getDirLight();

	ui->ambientX->setValue(dirLight.ambient.x);
	ui->ambientY->setValue(dirLight.ambient.y);
	ui->ambientZ->setValue(dirLight.ambient.z);
	ui->ambientW->setValue(dirLight.ambient.w);

	ui->diffuseX->setValue(dirLight.diffuse.x);
	ui->diffuseY->setValue(dirLight.diffuse.y);
	ui->diffuseZ->setValue(dirLight.diffuse.z);
	ui->diffuseW->setValue(dirLight.diffuse.w);

	ui->specularX->setValue(dirLight.specular.x);
	ui->specularY->setValue(dirLight.specular.y);
	ui->specularZ->setValue(dirLight.specular.z);
	ui->specularW->setValue(dirLight.specular.w);

	ui->directionX->setValue(dirLight.direction.x);
	ui->directionY->setValue(dirLight.direction.y);
	ui->directionZ->setValue(dirLight.direction.z);

	connect(ui->ambientX, SIGNAL(valueChanged(double)), this, SLOT(setLightProperty()));
	connect(ui->ambientY, SIGNAL(valueChanged(double)), this, SLOT(setLightProperty()));
	connect(ui->ambientZ, SIGNAL(valueChanged(double)), this, SLOT(setLightProperty()));
	connect(ui->ambientW, SIGNAL(valueChanged(double)), this, SLOT(setLightProperty()));

	connect(ui->diffuseX, SIGNAL(valueChanged(double)), this, SLOT(setLightProperty()));
	connect(ui->diffuseY, SIGNAL(valueChanged(double)), this, SLOT(setLightProperty()));
	connect(ui->diffuseZ, SIGNAL(valueChanged(double)), this, SLOT(setLightProperty()));
	connect(ui->diffuseW, SIGNAL(valueChanged(double)), this, SLOT(setLightProperty()));

	connect(ui->specularX, SIGNAL(valueChanged(double)), this, SLOT(setLightProperty()));
	connect(ui->specularY, SIGNAL(valueChanged(double)), this, SLOT(setLightProperty()));
	connect(ui->specularZ, SIGNAL(valueChanged(double)), this, SLOT(setLightProperty()));
	connect(ui->specularW, SIGNAL(valueChanged(double)), this, SLOT(setLightProperty()));

	connect(ui->directionX, SIGNAL(valueChanged(double)), this, SLOT(setLightProperty()));
	connect(ui->directionY, SIGNAL(valueChanged(double)), this, SLOT(setLightProperty()));
	connect(ui->directionZ, SIGNAL(valueChanged(double)), this, SLOT(setLightProperty()));
}

void LightForm::setLightProperty()
{
	LkEngine::DirectionLight dirLight;
	dirLight.ambient = DirectX::XMFLOAT4(ui->ambientX->value(), ui->ambientY->value(), ui->ambientZ->value(), ui->ambientW->value());
	dirLight.diffuse = DirectX::XMFLOAT4(ui->diffuseX->value(), ui->diffuseY->value(), ui->diffuseZ->value(), ui->diffuseW->value());
	dirLight.specular = DirectX::XMFLOAT4(ui->specularX->value(), ui->specularY->value(), ui->specularZ->value(), ui->specularW->value());
	dirLight.direction = DirectX::XMFLOAT3(ui->directionX->value(), ui->directionY->value(), ui->directionZ->value());
	LkEngine::Engine::getInstance().setDirLight(dirLight);
}

