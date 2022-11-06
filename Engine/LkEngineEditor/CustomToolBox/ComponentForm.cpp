#include "ComponentForm.h"
#include "ui_ComponentForm.h"
#include "../../LkEngineRuntime/Core/engine/Engine.h"
#include <qfiledialog.h>

ComponentForm::ComponentForm(QWidget *parent) :
	QDialog(parent),
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
	connect(ui->pushButton_5, &QPushButton::clicked, this,
		[]()
		{
			LkEngine::Engine::getInstance().addComponent("CylinderComponent");
		});
	connect(ui->pushButton_7, &QPushButton::clicked, this,
		[]()
		{
			LkEngine::Engine::getInstance().addComponent("ConeComponent");
		});
	connect(ui->pushButton_4, &QPushButton::clicked, this,
		[=]()
		{
			QString curPath, aFileName;
			curPath = QCoreApplication::applicationDirPath() + "/builtin/Model/";
			aFileName = QFileDialog::getOpenFileName(this, tr("Open Solution"), curPath, tr("*.obj;*.gltf"));
			if (aFileName != "")
				LkEngine::Engine::getInstance().addComponent("ModelComponent", aFileName.toStdString());
		});
	connect(ui->pushButton_6, &QPushButton::clicked, this,
		[=]()
		{
			LkEngine::Engine::getInstance().resetScene();
		});
}

ComponentForm::~ComponentForm()
{
    delete ui;
}
