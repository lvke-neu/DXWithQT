#include "ComponentFrom.h"
#include "ui_ComponentFrom.h"
#include "../../LkEngineRuntime/Core/engine/Engine.h"

ComponentFrom::ComponentFrom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComponentFrom)
{
    ui->setupUi(this);

	connect(ui->pushButton, &QPushButton::clicked, this, 
		[]()
		{
			LkEngine::Engine::getInstance().addComponent("BoxComponent");
		});
}

ComponentFrom::~ComponentFrom()
{
    delete ui;
}
