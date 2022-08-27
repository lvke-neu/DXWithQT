#include "Chapter7DockWidget.h"
#include "Reflection.h"

REGISTER_CLASS(IChapterDockWidget, "Chapter7DockWidget", Chapter7DockWidget)

Chapter7DockWidget::Chapter7DockWidget(void** parameters) :
	IChapterDockWidget(parameters)
{


	m_labelCamProperty = new QLabel(u8"相机属性:", m_dockWidget);

	m_labelFrustumCull = new QLabel(u8"视锥体裁剪:", m_dockWidget);
	m_buttonStartFrustumCull = new QPushButton("开启", m_dockWidget);
	m_buttonCloseFrustumCull = new QPushButton("关闭", m_dockWidget);
	connect(m_buttonStartFrustumCull, &QPushButton::clicked, this,
		[=]()
		{
			Chapter7Scene* chapter7Scene = (Chapter7Scene*)m_renderWidget->m_gameApp->getScene();
			if (chapter7Scene)
			{
				chapter7Scene->set_enableFrustumCulling(true);
			}
		});
	connect(m_buttonCloseFrustumCull, &QPushButton::clicked, this,
		[=]()
		{
			Chapter7Scene* chapter7Scene = (Chapter7Scene*)m_renderWidget->m_gameApp->getScene();
			if (chapter7Scene)
			{
				chapter7Scene->set_enableFrustumCulling(false);
			}
		});



	m_labelChangeFog = new QLabel(u8"雾效果:", m_dockWidget);
	m_buttonStartFog = new QPushButton(u8"开启", m_dockWidget);
	m_buttonCloseFog = new QPushButton(u8"关闭", m_dockWidget);
	m_sliderFogRange = new QSlider(Qt::Horizontal, m_dockWidget);

	connect(m_buttonStartFog, &QPushButton::clicked, this,
		[=]()
		{
			Chapter7Scene* chapter7Scene = (Chapter7Scene*)m_renderWidget->m_gameApp->getScene();
			if (chapter7Scene)
			{
				chapter7Scene->setFogEnabled(true);
			}
		});
	connect(m_buttonCloseFog, &QPushButton::clicked, this,
		[=]()
		{
			Chapter7Scene* chapter7Scene = (Chapter7Scene*)m_renderWidget->m_gameApp->getScene();
			if (chapter7Scene)
			{
				chapter7Scene->setFogEnabled(false);
			}
		});
	connect(m_sliderFogRange, &QSlider::valueChanged, this,
		[=]
		{
			Chapter7Scene* chapter7Scene = (Chapter7Scene*)m_renderWidget->m_gameApp->getScene();
			if (chapter7Scene)
			{
				chapter7Scene->setFogRange(m_sliderFogRange->value());
			}
		});
}

Chapter7DockWidget::~Chapter7DockWidget()
{
	SAFE_RELEASE_SET_NULL(m_labelCamProperty);

	SAFE_RELEASE_SET_NULL(m_labelFrustumCull);
	SAFE_RELEASE_SET_NULL(m_buttonStartFrustumCull);
	SAFE_RELEASE_SET_NULL(m_buttonCloseFrustumCull);
		
	SAFE_RELEASE_SET_NULL(m_labelChangeFog);
	SAFE_RELEASE_SET_NULL(m_buttonStartFog);
	SAFE_RELEASE_SET_NULL(m_buttonCloseFog);

}

void Chapter7DockWidget::init()
{
	m_dockWidget->show();

	m_labelCamProperty->setText(u8"相机属性:");
	m_labelCamProperty->setFixedHeight(200);

	m_labelFrustumCull->move(0, 200);
	m_buttonStartFrustumCull->move(0, 230);
	m_buttonCloseFrustumCull->move(0, 260);

	m_labelChangeFog->move(0, 290);
	m_buttonStartFog->move(0, 320);
	m_buttonCloseFog->move(0, 350);
	m_sliderFogRange->move(0, 380);
	m_sliderFogRange->setMinimum(15);
	m_sliderFogRange->setMaximum(1900);
	m_sliderFogRange->setSingleStep(1);
	m_sliderFogRange->setValue(1500);
}

void Chapter7DockWidget::onCameraMove(const std::string& msg)
{
	m_labelCamProperty->setText(("相机属性:\n" + msg).c_str());
}