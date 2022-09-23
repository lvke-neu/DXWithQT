#include "SkyBoxForm.h"
#include "ui_SkyBoxForm.h"
#include "../../LkEngineRuntime/Core/base/Utility.h"
#include "../../LkEngineRuntime/Core/engine/Engine.h"

SkyBoxForm::SkyBoxForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SkyBoxForm)
{
    ui->setupUi(this);

	
	connect(ui->comboBox, SIGNAL(activated(QString)), this, SLOT(setSkyBoxTexture(QString)));
}

SkyBoxForm::~SkyBoxForm()
{
    delete ui;
}

void SkyBoxForm::setSkyBoxTexture(QString skyBoxTexture)
{
	Engine::getInstance().setSkyBoxTexture(("builtin\\Texture\\SkyBox\\" + skyBoxTexture.toStdString()).c_str());
	LOG_INFO(skyBoxTexture.toStdString())
}

