#include "Chapter5DockWidget.h"
#include "Reflection.h"

REGISTER_CLASS(IChapterDockWidget, "Chapter5DockWidget", Chapter5DockWidget)

Chapter5DockWidget::Chapter5DockWidget(void** parameters) :
	IChapterDockWidget(parameters)
{
	m_labelCamProperty = new QLabel(u8"相机属性:", m_dockWidget);

	m_labelDirLightDir = new QLabel(u8"方向光方向(x,y,z)：", m_dockWidget);

	m_lineEditDirLightX = new QLineEdit(m_dockWidget);
	m_sliderDirLightX = new QSlider(Qt::Horizontal, m_dockWidget);
	connect(m_sliderDirLightX, &QSlider::valueChanged, this,
		[=]
		{
			m_lineEditDirLightX->setText(std::to_string(m_sliderDirLightX->value() / 1000.0f).c_str());
			changeDirLight();
		});

	m_lineEditDirLightY = new QLineEdit(m_dockWidget);
	m_sliderDirLightY = new QSlider(Qt::Horizontal, m_dockWidget);
	connect(m_sliderDirLightY, &QSlider::valueChanged, this,
		[=]
		{
			m_lineEditDirLightY->setText(std::to_string(m_sliderDirLightY->value() / 1000.0f).c_str());
			changeDirLight();
		});

	m_lineEditDirLightZ = new QLineEdit(m_dockWidget);
	m_sliderDirLightZ = new QSlider(Qt::Horizontal, m_dockWidget);
	connect(m_sliderDirLightZ, &QSlider::valueChanged, this,
		[=]
		{
			m_lineEditDirLightZ->setText(std::to_string(m_sliderDirLightZ->value() / 1000.0f).c_str());
			changeDirLight();
		});

	m_buttonReset = new QPushButton(u8"重置(0,0,0)", m_dockWidget);
	
	connect(m_buttonReset, &QPushButton::clicked, this,
		[=]()
		{
			Chapter5Scene* chapter5Scene = (Chapter5Scene*)m_renderWidget->m_gameApp->getScene();
			if (chapter5Scene)
			{
				m_lineEditDirLightX->setText("0.0");
				m_sliderDirLightX->setValue(0);
				m_lineEditDirLightY->setText("0.0");
				m_sliderDirLightY->setValue(0);
				m_lineEditDirLightZ->setText("0.0");
				m_sliderDirLightZ->setValue(0);
				chapter5Scene->setDirLight(0.0f, 0.0f, 0.0f);
			}
		});
}

Chapter5DockWidget::~Chapter5DockWidget()
{
	SAFE_RELEASE_SET_NULL(m_labelCamProperty);

	SAFE_RELEASE_SET_NULL(m_labelDirLightDir);

	SAFE_RELEASE_SET_NULL(m_lineEditDirLightX);
	SAFE_RELEASE_SET_NULL(m_sliderDirLightX);

	SAFE_RELEASE_SET_NULL(m_lineEditDirLightY);
	SAFE_RELEASE_SET_NULL(m_sliderDirLightY);

	SAFE_RELEASE_SET_NULL(m_lineEditDirLightZ);
	SAFE_RELEASE_SET_NULL(m_sliderDirLightZ);

	SAFE_RELEASE_SET_NULL(m_buttonReset);

}

void Chapter5DockWidget::init()
{
	m_dockWidget->show();

	m_labelCamProperty->setText(u8"相机属性:");
	m_labelCamProperty->setFixedHeight(200);

	m_labelDirLightDir->move(0, 200);

	m_lineEditDirLightX->setPlaceholderText("x");
	m_lineEditDirLightX->setText("0.5");
	m_lineEditDirLightX->move(0, 230);
	m_lineEditDirLightX->setObjectName("lineDirLightX");
	m_lineEditDirLightX->setReadOnly(true);
	m_sliderDirLightX->move(0, 260);
	m_sliderDirLightX->setMinimum(-1000);
	m_sliderDirLightX->setMaximum(1000);
	m_sliderDirLightX->setSingleStep(1);
	m_sliderDirLightX->setValue(500);

	m_lineEditDirLightY->setPlaceholderText("y");
	m_lineEditDirLightY->setText("-1.0");
	m_lineEditDirLightY->move(0, 290);
	m_lineEditDirLightY->setObjectName("lineDirLightY");
	m_lineEditDirLightY->setReadOnly(true);
	m_sliderDirLightY->move(0, 320);
	m_sliderDirLightY->setMinimum(-1000);
	m_sliderDirLightY->setMaximum(1000);
	m_sliderDirLightY->setSingleStep(1);
	m_sliderDirLightY->setValue(-1000);

	m_lineEditDirLightZ->setPlaceholderText("z");
	m_lineEditDirLightZ->setText("0.0");
	m_lineEditDirLightZ->move(0, 350);
	m_lineEditDirLightZ->setObjectName("lineDirLightZ");
	m_lineEditDirLightZ->setReadOnly(true);
	m_sliderDirLightZ->move(0, 380);
	m_sliderDirLightZ->setMinimum(-1000);
	m_sliderDirLightZ->setMaximum(1000);
	m_sliderDirLightZ->setSingleStep(1);
	m_sliderDirLightZ->setValue(0);

	m_buttonReset->move(0, 420);
}

void Chapter5DockWidget::onCameraMove(const std::string& msg)
{
	m_labelCamProperty->setText(("相机属性:\n" + msg).c_str());
}

void Chapter5DockWidget::changeDirLight()
{
	bool bX, bY, bZ;
	float x, y, z;
	x = m_lineEditDirLightX->text().toFloat(&bX);
	y = m_lineEditDirLightY->text().toFloat(&bY);
	z = m_lineEditDirLightZ->text().toFloat(&bZ);

	Chapter5Scene* chapter5Scene = (Chapter5Scene*)m_renderWidget->m_gameApp->getScene();
	if (chapter5Scene && bX && bY &&bZ)
	{
		chapter5Scene->setDirLight(x, y, z);
	}
}