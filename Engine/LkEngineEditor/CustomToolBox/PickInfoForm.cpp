#include "PickInfoForm.h"
#include "ui_PickInfoForm.h"
#include "../../LkEngineRuntime/Core/Event/PickEventManager.h"
#include "../../LkEngineRuntime/Core/engine/Engine.h"


PickInfoForm::PickInfoForm(QWidget *parent) :
	QDialog(parent),
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

	connect(ui->dragLength, SIGNAL(valueChanged(double)), this, SLOT(setAxisPorperty()));
	connect(ui->dragMoveCoefficient, SIGNAL(valueChanged(double)), this, SLOT(setAxisPorperty()));

	connect(ui->deleteComponent, &QPushButton::clicked, this,
		[=]()
		{
			if (m_pComponent)
			{
				LkEngine::Engine::getInstance().deleteComponent(m_pComponent->getUuId());
				m_pComponent = nullptr;
				ui->UUID->setText("");
				ui->Type->setText("");
				ui->Texture->setText("");
				ui->VsShader->setText("");
				ui->GsShader->setText("");
				ui->PsShader->setText("");

				ui->scaleX->setValue(0);
				ui->scaleY->setValue(0);
				ui->scaleZ->setValue(0);

				ui->rotX->setValue(0);
				ui->rotY->setValue(0);
				ui->rotZ->setValue(0);

				ui->posX->setValue(0);
				ui->posY->setValue(0);
				ui->posZ->setValue(0);
			}
		});
	
	LkEngine::PickEventManager::getInstance().registerPickEvent(this);
}

PickInfoForm::~PickInfoForm()
{
	LkEngine::PickEventManager::getInstance().unRegisterPickEvent(this);
	delete ui;
}



void PickInfoForm::setAxisPorperty()
{
	QDoubleSpinBox* doubleSpinBox = dynamic_cast<QDoubleSpinBox*>(sender());
	if (doubleSpinBox)
	{
		if (doubleSpinBox->objectName() == "dragLength")
		{
			LkEngine::Engine::getInstance().setAxisLength(ui->dragLength->value());
		}
		else if (doubleSpinBox->objectName() == "dragMoveCoefficient")
		{
			LkEngine::Engine::getInstance().setMoveScaleCoefficient(ui->dragMoveCoefficient->value());
		}
	}
}

bool isPicking = false;
void PickInfoForm::onPickComponent(LkEngine::IComponent * component)
{
	m_pComponent = component;

	if (m_pComponent)
	{
		isPicking = true;

		ui->UUID->setText(m_pComponent->getUuId().c_str());
		ui->Type->setText(m_pComponent->getComponetType().c_str());
		ui->Texture->setText(m_pComponent->getTexture().c_str());
		ui->VsShader->setText(m_pComponent->getVsShader().c_str());
		ui->GsShader->setText(m_pComponent->getGsShader().c_str());
		ui->PsShader->setText(m_pComponent->getPsShader().c_str());

		DirectX::XMFLOAT3 scale = m_pComponent->getScale();
		DirectX::XMFLOAT3 rot = m_pComponent->getRotation();
		DirectX::XMFLOAT3 pos = m_pComponent->getPosition();

		ui->scaleX->setValue(scale.x);
		ui->scaleY->setValue(scale.y);
		ui->scaleZ->setValue(scale.z);

		ui->rotX->setValue(rot.x);
		ui->rotY->setValue(rot.y);
		ui->rotZ->setValue(rot.z);

		ui->posX->setValue(pos.x);
		ui->posY->setValue(pos.y);
		ui->posZ->setValue(pos.z);

		isPicking = false;
		//update();
	}
	else
	{
		ui->UUID->setText("");
		ui->Type->setText("");
		ui->Texture->setText("");
		ui->VsShader->setText("");
		ui->GsShader->setText("");
		ui->PsShader->setText("");

		ui->scaleX->setValue(0);
		ui->scaleY->setValue(0);
		ui->scaleZ->setValue(0);

		ui->rotX->setValue(0);
		ui->rotY->setValue(0);
		ui->rotZ->setValue(0);

		ui->posX->setValue(0);
		ui->posY->setValue(0);
		ui->posZ->setValue(0);
	}
}

void PickInfoForm::setComponentPorperty()
{
	if (m_pComponent && ! isPicking)
	{
		m_pComponent->setTexture(ui->Texture->text().toStdString());
		m_pComponent->setVsShader(ui->VsShader->text().toStdString());
		m_pComponent->setPsShader(ui->PsShader->text().toStdString());

		DirectX::XMFLOAT3 scale(ui->scaleX->value(), ui->scaleY->value(), ui->scaleZ->value());
		DirectX::XMFLOAT3 rot(ui->rotX->value(), ui->rotY->value(), ui->rotZ->value());
		DirectX::XMFLOAT3 pos(ui->posX->value(), ui->posY->value(), ui->posZ->value());
		LkEngine::Transform transform(scale, rot, pos);

		m_pComponent->setTransform(transform);
	}
}

