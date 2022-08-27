#include "Chapter8DockWidget.h"
#include "Reflection.h"
#include "d3dUtil.h"


REGISTER_CLASS(IChapterDockWidget, "Chapter8DockWidget", Chapter8DockWidget)

Chapter8DockWidget::Chapter8DockWidget(void** parameters) :
	IChapterDockWidget(parameters)
{
	m_dockWidget->setFixedWidth(240);

	m_labelCamProperty = new QLabel(u8"相机属性:", m_dockWidget);


	m_labelPickedGoProperty = new QLabel(u8"选中的物体的属性:", m_dockWidget);

	m_labelScale = new QLabel("Scale:", m_dockWidget);
	m_lineEditScaleX = new QLineEdit(m_dockWidget);
	m_lineEditScaleY = new QLineEdit(m_dockWidget);
	m_lineEditScaleZ = new QLineEdit(m_dockWidget);
	

	m_labelRotation = new QLabel("Rotation:", m_dockWidget);
	m_lineEditRotationX = new QLineEdit(m_dockWidget);
	m_lineEditRotationY = new QLineEdit(m_dockWidget);
	m_lineEditRotationZ = new QLineEdit(m_dockWidget);


	m_labelPosition = new QLabel("Position:", m_dockWidget);
	m_lineEditPositionX = new QLineEdit(m_dockWidget);
	m_lineEditPositionY = new QLineEdit(m_dockWidget);
	m_lineEditPositionZ = new QLineEdit(m_dockWidget);

	m_labelTexture = new QLabel(u8"贴图:", m_dockWidget);
	m_lineEditTexture = new QLineEdit(m_dockWidget);

	m_labelShader = new QLabel("Shder(VS,PS):暂时不允许修改", m_dockWidget);
	m_lineEditVsShader = new QLineEdit(m_dockWidget);
	m_lineEditPsShader = new QLineEdit(m_dockWidget);

	
}

Chapter8DockWidget::~Chapter8DockWidget()
{
	SAFE_RELEASE_SET_NULL(m_labelCamProperty);

	SAFE_RELEASE_SET_NULL(m_labelPickedGoProperty);

	SAFE_RELEASE_SET_NULL(m_labelScale);
	SAFE_RELEASE_SET_NULL(m_lineEditScaleX);
	SAFE_RELEASE_SET_NULL(m_lineEditScaleY);
	SAFE_RELEASE_SET_NULL(m_lineEditScaleZ);

	SAFE_RELEASE_SET_NULL(m_labelRotation);
	SAFE_RELEASE_SET_NULL(m_lineEditRotationX);
	SAFE_RELEASE_SET_NULL(m_lineEditRotationY);
	SAFE_RELEASE_SET_NULL(m_lineEditRotationZ);

	SAFE_RELEASE_SET_NULL(m_labelPosition);
	SAFE_RELEASE_SET_NULL(m_lineEditPositionX);
	SAFE_RELEASE_SET_NULL(m_lineEditPositionY);
	SAFE_RELEASE_SET_NULL(m_lineEditPositionZ);

	SAFE_RELEASE_SET_NULL(m_labelTexture);
	SAFE_RELEASE_SET_NULL(m_lineEditTexture);

	SAFE_RELEASE_SET_NULL(m_labelShader);
	SAFE_RELEASE_SET_NULL(m_lineEditVsShader);
	SAFE_RELEASE_SET_NULL(m_lineEditPsShader);
	
}

void Chapter8DockWidget::init()
{
	m_pickedGameObject = nullptr;

	m_dockWidget->show();

	m_labelCamProperty->setText(u8"相机属性:");
	m_labelCamProperty->setFixedHeight(200);

	m_labelPickedGoProperty->setStyleSheet("QLabel{font:13px;color:red;background-color:rgb(f9,f9,f9);}");
	m_labelPickedGoProperty->setFixedWidth(200);
	m_labelPickedGoProperty->move(0, 230);
	
	m_labelScale->move(0, 260);
	m_lineEditScaleX->setFixedWidth(70);
	m_lineEditScaleY->setFixedWidth(70);
	m_lineEditScaleZ->setFixedWidth(70);
	m_lineEditScaleX->move(0, 290);
	m_lineEditScaleY->move(80, 290);
	m_lineEditScaleZ->move(160, 290);
	m_lineEditScaleX->setText("");
	m_lineEditScaleY->setText("");
	m_lineEditScaleZ->setText("");



	m_labelRotation->move(0, 320);
	m_lineEditRotationX->setFixedWidth(70);
	m_lineEditRotationY->setFixedWidth(70);
	m_lineEditRotationZ->setFixedWidth(70);
	m_lineEditRotationX->move(0, 350);
	m_lineEditRotationY->move(80, 350);
	m_lineEditRotationZ->move(160, 350);
	m_lineEditRotationX->setText("");
	m_lineEditRotationY->setText("");
	m_lineEditRotationZ->setText("");

	m_labelPosition->move(0, 380);
	m_lineEditPositionX->setFixedWidth(70);
	m_lineEditPositionY->setFixedWidth(70);
	m_lineEditPositionZ->setFixedWidth(70);
	m_lineEditPositionX->move(0, 410);
	m_lineEditPositionY->move(80, 410);
	m_lineEditPositionZ->move(160, 410);
	m_lineEditPositionX->setText("");
	m_lineEditPositionY->setText("");
	m_lineEditPositionZ->setText("");

	m_labelTexture->move(0, 440);
	m_lineEditTexture->setFixedWidth(200);
	m_lineEditTexture->move(0, 470);
	m_lineEditTexture->setText("");
	
	m_labelShader->move(0, 500);
	m_labelShader->setFixedWidth(200);
	m_lineEditVsShader->setFixedWidth(200);
	m_lineEditVsShader->move(0, 530);
	m_lineEditVsShader->setText("");
	m_lineEditPsShader->setFixedWidth(200);
	m_lineEditPsShader->move(0, 560);
	m_lineEditPsShader->setText("");
	m_lineEditVsShader->setReadOnly(true);
	m_lineEditPsShader->setReadOnly(true);

	
}

void Chapter8DockWidget::onCameraMove(const std::string& msg)
{
	m_labelCamProperty->setText(("相机属性:\n" + msg).c_str());
}

void Chapter8DockWidget::onPickGameObject(GameObject& go)
{
	m_pickedGameObject = &go;

	m_renderWidget->m_Timer.Stop();

	disConnectSignalAndSlots();
	showTransform();
	showTexture();
	showShader();
	connectSignalAndSlots();

	m_renderWidget->m_Timer.Start();
}

void Chapter8DockWidget::connectSignalAndSlots()
{
	connect(m_lineEditScaleX, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTransform);
	connect(m_lineEditScaleY, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTransform);
	connect(m_lineEditScaleZ, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTransform);

	connect(m_lineEditRotationX, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTransform);
	connect(m_lineEditRotationY, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTransform);
	connect(m_lineEditRotationZ, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTransform);

	connect(m_lineEditPositionX, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTransform);
	connect(m_lineEditPositionY, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTransform);
	connect(m_lineEditPositionZ, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTransform);

	connect(m_lineEditTexture, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTexture);
	connect(m_lineEditVsShader, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTexture);
	connect(m_lineEditPsShader, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTexture);
}

void Chapter8DockWidget::disConnectSignalAndSlots()
{
	disconnect(m_lineEditScaleX, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTransform);
	disconnect(m_lineEditScaleY, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTransform);
	disconnect(m_lineEditScaleZ, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTransform);

	disconnect(m_lineEditRotationX, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTransform);
	disconnect(m_lineEditRotationY, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTransform);
	disconnect(m_lineEditRotationZ, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTransform);

	disconnect(m_lineEditPositionX, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTransform);
	disconnect(m_lineEditPositionY, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTransform);
	disconnect(m_lineEditPositionZ, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeTransform);

	disconnect(m_lineEditTexture, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeShader);
	disconnect(m_lineEditVsShader, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeShader);
	disconnect(m_lineEditPsShader, &QLineEdit::textChanged, this, &Chapter8DockWidget::changeShader);
}

void Chapter8DockWidget::onMouseLocateGo(const std::string& msg)
{
	m_labelPickedGoProperty->setText(("选中的物体 " + msg + " 的属性:").c_str());	
}

void Chapter8DockWidget::showTransform()
{
	m_lineEditScaleX->setText(std::to_string(m_pickedGameObject->getScale().x).c_str());
	m_lineEditScaleY->setText(std::to_string(m_pickedGameObject->getScale().y).c_str());
	m_lineEditScaleZ->setText(std::to_string(m_pickedGameObject->getScale().z).c_str());

	m_lineEditRotationX->setText(std::to_string(m_pickedGameObject->getRotation().x).c_str());
	m_lineEditRotationY->setText(std::to_string(m_pickedGameObject->getRotation().y).c_str());
	m_lineEditRotationZ->setText(std::to_string(m_pickedGameObject->getRotation().z).c_str());

	m_lineEditPositionX->setText(std::to_string(m_pickedGameObject->getPosition().x).c_str());
	m_lineEditPositionY->setText(std::to_string(m_pickedGameObject->getPosition().y).c_str());
	m_lineEditPositionZ->setText(std::to_string(m_pickedGameObject->getPosition().z).c_str());
}

void Chapter8DockWidget::changeTransform()
{
	if (m_pickedGameObject)
	{
		m_pickedGameObject->setScale(m_lineEditScaleX->text().toFloat(), m_lineEditScaleY->text().toFloat(), m_lineEditScaleZ->text().toFloat());
		m_pickedGameObject->setRotation(m_lineEditRotationX->text().toFloat(), m_lineEditRotationY->text().toFloat(), m_lineEditRotationZ->text().toFloat());
		m_pickedGameObject->setPosition(m_lineEditPositionX->text().toFloat(), m_lineEditPositionY->text().toFloat(), m_lineEditPositionZ->text().toFloat());
	}
}

void Chapter8DockWidget::showTexture()
{
	m_lineEditTexture->setText(wideCharToMultiByte(m_pickedGameObject->getTexture().c_str()));
}

void Chapter8DockWidget::changeTexture()
{
	if(m_pickedGameObject)
		m_pickedGameObject->setTexture(multiByteToWideChar(m_lineEditTexture->text().toStdString()));
}

void Chapter8DockWidget::showShader()
{
	m_lineEditVsShader->setText(wideCharToMultiByte(m_pickedGameObject->getShader()[0].c_str()));
	m_lineEditPsShader->setText(wideCharToMultiByte(m_pickedGameObject->getShader()[1].c_str()));
	
}

void Chapter8DockWidget::changeShader()
{
	std::vector<std::wstring> shader;
	shader.resize(2);
	shader[0] = multiByteToWideChar(m_lineEditVsShader->text().toStdString());
	shader[1] = multiByteToWideChar(m_lineEditPsShader->text().toStdString());
	
	if (m_pickedGameObject)
		m_pickedGameObject->setShader(shader);
}

