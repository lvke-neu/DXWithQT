#include "PickInfoForm.h"
#include "ui_PickInfoForm.h"
#include "../../LkEngineRuntime/Core/Event/PickEventManager.h"
#include "../../LkEngineRuntime/Core/engine/Engine.h"
#include <QColorDialog>

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

	connect(ui->ambientX, SIGNAL(valueChanged(double)), this, SLOT(setMaterialColor()));
	connect(ui->ambientY, SIGNAL(valueChanged(double)), this, SLOT(setMaterialColor()));
	connect(ui->ambientZ, SIGNAL(valueChanged(double)), this, SLOT(setMaterialColor()));
	connect(ui->ambientX, SIGNAL(valueChanged(double)), this, SLOT(setMaterialColor()));

	connect(ui->diffuseX, SIGNAL(valueChanged(double)), this, SLOT(setMaterialColor()));
	connect(ui->diffuseY, SIGNAL(valueChanged(double)), this, SLOT(setMaterialColor()));
	connect(ui->diffuseZ, SIGNAL(valueChanged(double)), this, SLOT(setMaterialColor()));
	connect(ui->diffuseW, SIGNAL(valueChanged(double)), this, SLOT(setMaterialColor()));

	connect(ui->specularX, SIGNAL(valueChanged(double)), this, SLOT(setMaterialColor()));
	connect(ui->specularY, SIGNAL(valueChanged(double)), this, SLOT(setMaterialColor()));
	connect(ui->specularZ, SIGNAL(valueChanged(double)), this, SLOT(setMaterialColor()));
	connect(ui->specularW, SIGNAL(valueChanged(double)), this, SLOT(setMaterialColor()));

	connect(ui->reflectX, SIGNAL(valueChanged(double)), this, SLOT(setMaterialColor()));
	connect(ui->reflectY, SIGNAL(valueChanged(double)), this, SLOT(setMaterialColor()));
	connect(ui->reflectZ, SIGNAL(valueChanged(double)), this, SLOT(setMaterialColor()));
	connect(ui->reflectW, SIGNAL(valueChanged(double)), this, SLOT(setMaterialColor()));

	connect(ui->ambientColor, SIGNAL(clicked(bool)), this, SLOT(setMaterialColorDlg()));
	connect(ui->diffuseColor, SIGNAL(clicked(bool)), this, SLOT(setMaterialColorDlg()));
	connect(ui->specularColor, SIGNAL(clicked(bool)), this, SLOT(setMaterialColorDlg()));
	connect(ui->reflectColor, SIGNAL(clicked(bool)), this, SLOT(setMaterialColorDlg()));

	connect(ui->dragLength, SIGNAL(valueChanged(double)), this, SLOT(setAxisPorperty()));
	connect(ui->dragMoveCoefficient, SIGNAL(valueChanged(double)), this, SLOT(setAxisPorperty()));
	
	LkEngine::PickEventManager::getInstance().registerPickEvent(this);
	LkEngine::PickEventManager::getInstance().registerDeleteComponentEvent(this);
}

PickInfoForm::~PickInfoForm()
{
	LkEngine::PickEventManager::getInstance().unRegisterPickEvent(this);
	LkEngine::PickEventManager::getInstance().unRegisterDeleteComponentEvent(this);
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

void PickInfoForm::setMaterialColor()
{
	if (m_pComponent)
	{
		LkEngine::Material mat;
		mat.ambient = DirectX::XMFLOAT4(ui->ambientX->value(), ui->ambientY->value(), ui->ambientZ->value(), ui->ambientW->value());
		mat.diffuse = DirectX::XMFLOAT4(ui->diffuseX->value(), ui->diffuseY->value(), ui->diffuseZ->value(), ui->ambientW->value());
		mat.specular = DirectX::XMFLOAT4(ui->specularX->value(), ui->specularY->value(), ui->specularZ->value(), ui->specularW->value());
		mat.reflect = DirectX::XMFLOAT4(ui->reflectX->value(), ui->reflectY->value(), ui->reflectZ->value(), ui->reflectW->value());

		m_pComponent->setMaterial(mat);
	}
}

void PickInfoForm::setMaterialColorDlg()
{
	QToolButton* toolButton = dynamic_cast<QToolButton*>(sender());
	
	if (toolButton)
	{
		QColorDialog dlg(this);
		if (toolButton->objectName() == "ambientColor")
		{
			dlg.setWindowTitle("Ambient Color Editor");
			DirectX::XMFLOAT4 ambientColor(ui->ambientX->value(), ui->ambientY->value(), ui->ambientZ->value(), ui->ambientW->value());
			dlg.setCurrentColor(QColor(250 * ambientColor.x, 250 * ambientColor.y, 250 * ambientColor.z, 250 * ambientColor.w));
			connect(&dlg, &QColorDialog::currentColorChanged, this, [&](const QColor& qColor)
				{
					ui->ambientX->setValue(qColor.red() / 255.0f);
					ui->ambientY->setValue(qColor.green() / 255.0f);
					ui->ambientZ->setValue(qColor.blue() / 255.0f);
					ui->ambientW->setValue(qColor.alpha() / 255.0f);
				});

			if (dlg.exec() != QColorDialog::Accepted)
			{
				ui->ambientX->setValue(ambientColor.x);
				ui->ambientY->setValue(ambientColor.y);
				ui->ambientZ->setValue(ambientColor.z);
				ui->ambientW->setValue(ambientColor.w);
			}
		}
		else if (toolButton->objectName() == "diffuseColor")
		{
			dlg.setWindowTitle("Diffuse Color Editor");
			DirectX::XMFLOAT4 diffuseColor(ui->diffuseX->value(), ui->diffuseY->value(), ui->diffuseZ->value(), ui->diffuseW->value());
			dlg.setCurrentColor(QColor(250 * diffuseColor.x, 250 * diffuseColor.y, 250 * diffuseColor.z, 250 * diffuseColor.w));
			connect(&dlg, &QColorDialog::currentColorChanged, this, [&](const QColor& qColor)
				{
					ui->diffuseX->setValue(qColor.red() / 255.0f);
					ui->diffuseY->setValue(qColor.green() / 255.0f);
					ui->diffuseZ->setValue(qColor.blue() / 255.0f);
					ui->diffuseW->setValue(qColor.alpha() / 255.0f);
				});
			if (dlg.exec() != QColorDialog::Accepted)
			{
				ui->diffuseX->setValue(diffuseColor.x);
				ui->diffuseY->setValue(diffuseColor.y);
				ui->diffuseZ->setValue(diffuseColor.z);
				ui->diffuseW->setValue(diffuseColor.w);
			}
		}
		else if (toolButton->objectName() == "specularColor")
		{
			dlg.setWindowTitle("Specular Color Editor");
			DirectX::XMFLOAT4 specularColor(ui->specularX->value(), ui->specularY->value(), ui->specularZ->value(), ui->specularW->value());
			dlg.setCurrentColor(QColor(250 * specularColor.x, 250 * specularColor.y, 250 * specularColor.z));
			connect(&dlg, &QColorDialog::currentColorChanged, this, [&](const QColor& qColor)
				{
					ui->specularX->setValue(qColor.red() / 255.0f);
					ui->specularY->setValue(qColor.green() / 255.0f);
					ui->specularZ->setValue(qColor.blue() / 255.0f);
					//ui->specularW->setValue(qColor.alpha() / 255.0f);
				});
			if (dlg.exec() != QColorDialog::Accepted)
			{
				ui->specularX->setValue(specularColor.x);
				ui->specularY->setValue(specularColor.y);
				ui->specularZ->setValue(specularColor.z);
				//ui->specularW->setValue(specularColor.w);
			}
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

		if (m_pComponent->getComponetType() != "ModelComponent")
		{
			LkEngine::Material mat;
			mat = m_pComponent->getMaterial();
			ui->ambientX->setValue(mat.ambient.x);
			ui->ambientY->setValue(mat.ambient.y);
			ui->ambientZ->setValue(mat.ambient.z);
			ui->ambientW->setValue(mat.ambient.w);

			ui->diffuseX->setValue(mat.diffuse.x);
			ui->diffuseY->setValue(mat.diffuse.y);
			ui->diffuseZ->setValue(mat.diffuse.z);
			ui->ambientW->setValue(mat.diffuse.w);

			ui->specularX->setValue(mat.specular.x);
			ui->specularY->setValue(mat.specular.y);
			ui->specularZ->setValue(mat.specular.z);
			ui->specularW->setValue(mat.specular.w);

			ui->reflectX->setValue(mat.reflect.x);
			ui->reflectY->setValue(mat.reflect.y);
			ui->reflectZ->setValue(mat.reflect.z);
			ui->reflectW->setValue(mat.reflect.w);
		}

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

		ui->ambientX->setValue(0);
		ui->ambientY->setValue(0);
		ui->ambientZ->setValue(0);
		ui->ambientW->setValue(0);
							   
		ui->diffuseX->setValue(0);
		ui->diffuseY->setValue(0);
		ui->diffuseZ->setValue(0);
		ui->ambientW->setValue(0);

		ui->specularX->setValue(0);
		ui->specularY->setValue(0);
		ui->specularZ->setValue(0);
		ui->specularW->setValue(0);

		ui->reflectX->setValue(0);
		ui->reflectY->setValue(0);
		ui->reflectZ->setValue(0);
		ui->reflectW->setValue(0);
	}
}

void PickInfoForm::onDeleteComponent(LkEngine::IComponent * component)
{
	if (m_pComponent == component)
	{
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

		ui->ambientX->setValue(0);
		ui->ambientY->setValue(0);
		ui->ambientZ->setValue(0);
		ui->ambientW->setValue(0);

		ui->diffuseX->setValue(0);
		ui->diffuseY->setValue(0);
		ui->diffuseZ->setValue(0);
		ui->ambientW->setValue(0);

		ui->specularX->setValue(0);
		ui->specularY->setValue(0);
		ui->specularZ->setValue(0);
		ui->specularW->setValue(0);

		ui->reflectX->setValue(0);
		ui->reflectY->setValue(0);
		ui->reflectZ->setValue(0);
		ui->reflectW->setValue(0);
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

