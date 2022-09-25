#include "PickInfoForm.h"
#include "ui_PickInfoForm.h"
#include "../../LkEngineRuntime/Core/Event/PickEventManager.h"
#include "../../LkEngineRuntime/Core/engine/Engine.h"

PickInfoForm::PickInfoForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PickInfoForm)
{
	ui->setupUi(this);

	connect(ui->Texture, SIGNAL(textChanged(const QString &)), this, SLOT(setComponentPorperty()));
	connect(ui->VsShader, SIGNAL(textChanged(const QString &)), this, SLOT(setComponentPorperty()));
	connect(ui->PsShader, SIGNAL(textChanged(const QString &)), this, SLOT(setComponentPorperty()));

	connect(ui->scaleX, SIGNAL(valueChanged(double)), this, SLOT(setComponentPorperty()));
	connect(ui->scaleY, SIGNAL(valueChanged(double)), this, SLOT(setComponentPorperty()));
	connect(ui->scaleZ, SIGNAL(valueChanged(double)), this, SLOT(setComponentPorperty()));

	connect(ui->rotX, SIGNAL(valueChanged(double)), this, SLOT(setComponentPorperty()));
	connect(ui->rotY, SIGNAL(valueChanged(double)), this, SLOT(setComponentPorperty()));
	connect(ui->rotZ, SIGNAL(valueChanged(double)), this, SLOT(setComponentPorperty()));

	connect(ui->posX, SIGNAL(valueChanged(double)), this, SLOT(setComponentPorperty()));
	connect(ui->posY, SIGNAL(valueChanged(double)), this, SLOT(setComponentPorperty()));
	connect(ui->posZ, SIGNAL(valueChanged(double)), this, SLOT(setComponentPorperty()));

	connect(ui->deleteComponent, &QPushButton::clicked, this,
		[=]()
		{
			if (m_pickedComponent)
			{
				LkEngine::Engine::getInstance().deleteComponent(m_pickedComponent->getUuId());

				m_pickedComponent = nullptr;
				ui->UUID->setText("");
				ui->Type->setText("");
				ui->Texture->setText("");
				ui->VsShader->setText("");
				ui->PsShader->setText("");


				ui->scaleX->setValue(0.0);
				ui->scaleY->setValue(0.0);
				ui->scaleZ->setValue(0.0);

				ui->rotX->setValue(0.0);
				ui->rotY->setValue(0.0);
				ui->rotZ->setValue(0.0);

				ui->posX->setValue(0.0);
				ui->posY->setValue(0.0);
				ui->posZ->setValue(0.0);
			}
				
		});

	LkEngine::PickEventManager::getInstance().registerPickEvent(this);
}

PickInfoForm::~PickInfoForm()
{
	LkEngine::PickEventManager::getInstance().unRegisterPickEvent(this);

	delete ui;
}


void PickInfoForm::onPickComponent(LkEngine::IComponent* component)
{
	if (m_pickedComponent)
	{
		m_pickedComponent = nullptr;
	}

	if (component)
	{
		ui->UUID->setText(component->getUuId().c_str());
		ui->Type->setText(component->getComponetType().c_str());
		ui->Texture->setText(component->getTexture().c_str());
		ui->VsShader->setText(component->getVsShader().c_str());
		ui->PsShader->setText(component->getPsShader().c_str());


		DirectX::XMFLOAT3 scale = component->getScale();
		DirectX::XMFLOAT3 rot = component->getRotation();
		DirectX::XMFLOAT3 pos = component->getPosition();

		ui->scaleX->setValue(scale.x);
		ui->scaleY->setValue(scale.y);
		ui->scaleZ->setValue(scale.z);

		ui->rotX->setValue(rot.x);
		ui->rotY->setValue(rot.y);
		ui->rotZ->setValue(rot.z);

		ui->posX->setValue(pos.x);
		ui->posY->setValue(pos.y);
		ui->posZ->setValue(pos.z);

		m_pickedComponent = component;
	}	
}

void PickInfoForm::setComponentPorperty()
{
	if (m_pickedComponent)
	{
		m_pickedComponent->setTexture(ui->Texture->text().toStdString());
		m_pickedComponent->setVsShader(ui->VsShader->text().toStdString());
		m_pickedComponent->setPsShader(ui->PsShader->text().toStdString());

		DirectX::XMFLOAT3 scale(ui->scaleX->value(), ui->scaleY->value(), ui->scaleZ->value());
		DirectX::XMFLOAT3 rot(ui->rotX->value(), ui->rotY->value(), ui->rotZ->value());
		DirectX::XMFLOAT3 pos(ui->posX->value(), ui->posY->value(), ui->posZ->value());
		LkEngine::Transform transform(scale, rot, pos);

		m_pickedComponent->setTransform(transform);
	}
}
