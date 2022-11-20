#include "LightForm.h"
#include "ui_LightForm.h"
#include "../../LkEngineRuntime/Core/engine/Engine.h"
#include <QColorDialog>

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

	connect(ui->ambientColor, SIGNAL(clicked(bool)), this, SLOT(setLightColor()));
	connect(ui->diffuseColor, SIGNAL(clicked(bool)), this, SLOT(setLightColor()));
	connect(ui->specularColor, SIGNAL(clicked(bool)), this, SLOT(setLightColor()));

	connect(ui->ViewWidth, SIGNAL(valueChanged(double)), this, SLOT(setShadowOrthographicProjMat()));
	connect(ui->ViewHeight, SIGNAL(valueChanged(double)), this, SLOT(setShadowOrthographicProjMat()));
	connect(ui->NearZ, SIGNAL(valueChanged(double)), this, SLOT(setShadowOrthographicProjMat()));
	connect(ui->FarZ, SIGNAL(valueChanged(double)), this, SLOT(setShadowOrthographicProjMat()));
	connect(ui->lightDiscoefficient, SIGNAL(valueChanged(double)), this, SLOT(setShadowOrthographicProjMat()));
	connect(ui->showShadowRange, SIGNAL(toggled(bool)), this, SLOT(onButtonClicked(bool)));
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

void LightForm::setLightColor()
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

void LightForm::setShadowOrthographicProjMat()
{
	LkEngine::Engine::getInstance().changeOrthographicProjMat(ui->ViewWidth->value(), ui->ViewHeight->value(), ui->NearZ->value(), ui->FarZ->value(), ui->lightDiscoefficient->value());
}

void LightForm::onButtonClicked(bool flag)
{
	LkEngine::Engine::getInstance().enableShadowRange(flag);
}
