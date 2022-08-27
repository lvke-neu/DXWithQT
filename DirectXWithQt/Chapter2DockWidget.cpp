#include "Chapter2DockWidget.h"
#include "Reflection.h"

REGISTER_CLASS(IChapterDockWidget, "Chapter2DockWidget", Chapter2DockWidget)

Chapter2DockWidget::Chapter2DockWidget(void** parameters) :
	IChapterDockWidget(parameters)
{
	

	m_labelCamProperty = new QLabel(u8"相机属性:", m_dockWidget);

	m_labelChangeTexture = new QLabel(u8"换贴图:", m_dockWidget);
	m_buttonChangeBox1Texture = new QPushButton("Box1", m_dockWidget);
	m_buttonChangeBox2Texture = new QPushButton("Box2", m_dockWidget);
	m_buttonChangeFloorTexture = new QPushButton("Floor", m_dockWidget);
	connect(m_buttonChangeBox1Texture, &QPushButton::clicked, this,
		[=]()
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_renderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				chapter2Scene->changeBox1Texture();
			}
		});
	connect(m_buttonChangeBox2Texture, &QPushButton::clicked, this,
		[=]()
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_renderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				chapter2Scene->changeBox2Texture();
			}
		});
	connect(m_buttonChangeFloorTexture, &QPushButton::clicked, this,
		[=]()
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_renderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				chapter2Scene->changeFloorTexture();
			}
		});

	m_labelChangeWireframe = new QLabel(u8"开启/关闭线框模式:", m_dockWidget);
	m_buttonStartWireframe = new QPushButton(u8"开启", m_dockWidget);
	m_buttonCloseWireframe = new QPushButton(u8"关闭", m_dockWidget);
	connect(m_buttonStartWireframe, &QPushButton::clicked, this,
		[=]()
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_renderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				chapter2Scene->setWireframe(true);
			}
		});
	connect(m_buttonCloseWireframe, &QPushButton::clicked, this,
		[=]()
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_renderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				chapter2Scene->setWireframe(false);
			}
		});

	m_labelChangeBackCull = new QLabel(u8"开启/关闭背面裁剪:", m_dockWidget);
	m_buttonStartBackCull = new QPushButton(u8"开启", m_dockWidget);
	m_buttonCloseBackCull = new QPushButton(u8"关闭", m_dockWidget);
	connect(m_buttonStartBackCull, &QPushButton::clicked, this,
		[=]()
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_renderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				chapter2Scene->setNoCull(false);
			}
		});
	connect(m_buttonCloseBackCull, &QPushButton::clicked, this,
		[=]()
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_renderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				chapter2Scene->setNoCull(true);
			}
		});

	m_labelChangeFog = new QLabel(u8"雾效果:", m_dockWidget);
	m_buttonStartFog = new QPushButton(u8"开启", m_dockWidget);
	m_buttonCloseFog = new QPushButton(u8"关闭", m_dockWidget);
	m_sliderFogRange = new QSlider(Qt::Horizontal, m_dockWidget);

	connect(m_buttonStartFog, &QPushButton::clicked, this,
		[=]()
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_renderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				chapter2Scene->setFogEnabled(true);
			}
		});
	connect(m_buttonCloseFog, &QPushButton::clicked, this,
		[=]()
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_renderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				chapter2Scene->setFogEnabled(false);
			}
		});
	connect(m_sliderFogRange, &QSlider::valueChanged, this,
		[=]
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_renderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				chapter2Scene->setFogRange(m_sliderFogRange->value());
			}
		});

}

Chapter2DockWidget::~Chapter2DockWidget()
{
	SAFE_RELEASE_SET_NULL(m_labelCamProperty);

	SAFE_RELEASE_SET_NULL(m_labelChangeTexture);
	SAFE_RELEASE_SET_NULL(m_buttonChangeBox1Texture);
	SAFE_RELEASE_SET_NULL(m_buttonChangeBox2Texture);
	SAFE_RELEASE_SET_NULL(m_buttonChangeFloorTexture);

	SAFE_RELEASE_SET_NULL(m_labelChangeWireframe);
	SAFE_RELEASE_SET_NULL(m_buttonStartWireframe);
	SAFE_RELEASE_SET_NULL(m_buttonCloseWireframe);
	
	SAFE_RELEASE_SET_NULL(m_labelChangeBackCull);
	SAFE_RELEASE_SET_NULL(m_buttonStartBackCull);
	SAFE_RELEASE_SET_NULL(m_buttonCloseBackCull);

	SAFE_RELEASE_SET_NULL(m_labelChangeFog);
	SAFE_RELEASE_SET_NULL(m_buttonStartFog);
	SAFE_RELEASE_SET_NULL(m_buttonCloseFog);

	IChapterDockWidget::~IChapterDockWidget();
}

void Chapter2DockWidget::init()
{
	m_dockWidget->show();

	m_labelCamProperty->setText(u8"相机属性:");
	m_labelCamProperty->setFixedHeight(200);

	m_labelChangeTexture->move(0, 200);
	m_buttonChangeBox1Texture->move(0, 230);
	m_buttonChangeBox2Texture->move(0, 260);
	m_buttonChangeFloorTexture->move(0, 290);

	m_labelChangeWireframe->setFixedWidth(115);
	m_labelChangeWireframe->move(0, 320);
	m_buttonStartWireframe->move(0, 350);
	m_buttonCloseWireframe->move(0, 380);


	m_labelChangeBackCull->setFixedWidth(115);
	m_labelChangeBackCull->move(0, 410);
	m_buttonStartBackCull->move(0, 440);
	m_buttonCloseBackCull->move(0, 470);
	
	m_labelChangeFog->move(0, 500);
	m_buttonStartFog->move(0, 530);
	m_buttonCloseFog->move(0, 560);
	m_sliderFogRange->move(0, 590);
	m_sliderFogRange->setMinimum(15);
	m_sliderFogRange->setMaximum(190);
	m_sliderFogRange->setSingleStep(1);
	m_sliderFogRange->setValue(75);
	
}

void Chapter2DockWidget::onCameraMove(const std::string& msg)
{
	m_labelCamProperty->setText( ("相机属性:\n"+ msg).c_str());
}