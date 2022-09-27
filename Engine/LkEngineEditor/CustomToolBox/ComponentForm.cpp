#include "ComponentForm.h"
#include "ui_ComponentForm.h"
#include "../../LkEngineRuntime/Core/engine/Engine.h"

ComponentForm::ComponentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComponentForm)
{
    ui->setupUi(this);

	connect(ui->pushButton, &QPushButton::clicked, this, 
		[]()
		{
			LkEngine::Engine::getInstance().addComponent("BoxComponent");
		});
	connect(ui->pushButton_2, &QPushButton::clicked, this,
		[]()
		{
			LkEngine::Engine::getInstance().addComponent("SphereComponent");
		});
	connect(ui->pushButton_3, &QPushButton::clicked, this,
		[]()
		{
			LkEngine::Engine::getInstance().addComponent("SpatialImageComponent");
		});
}

ComponentForm::~ComponentForm()
{
    delete ui;
}
