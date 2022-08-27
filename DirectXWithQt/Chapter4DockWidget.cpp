#include "Chapter4DockWidget.h"
#include "Reflection.h"

REGISTER_CLASS(IChapterDockWidget, "Chapter4DockWidget", Chapter4DockWidget)

Chapter4DockWidget::Chapter4DockWidget(void** parameters) :
	IChapterDockWidget(parameters)
{


	m_labelCamProperty = new QLabel(u8"相机属性:", m_dockWidget);

	m_labelView = new QLabel(u8"切换视角:", m_dockWidget);
	m_buttonFirstPerson = new QPushButton("第一人称视角", m_dockWidget);
	m_buttonFreePerson  = new QPushButton("自由视角", m_dockWidget);
	connect(m_buttonFirstPerson, &QPushButton::clicked, this,
		[=]()
		{
			Chapter4Scene* chapter4Scene = (Chapter4Scene*)m_renderWidget->m_gameApp->getScene();
			if (chapter4Scene)
			{
				chapter4Scene->setFirstPerson(true);
			}
		});
	connect(m_buttonFreePerson, &QPushButton::clicked, this,
		[=]()
		{
			Chapter4Scene* chapter4Scene = (Chapter4Scene*)m_renderWidget->m_gameApp->getScene();
			if (chapter4Scene)
			{
				chapter4Scene->setFirstPerson(false);
			}
		});

	m_labelTransparency = new QLabel(u8"修改镜面透明度:", m_dockWidget);
	m_sliderTransparency = new QSlider(Qt::Horizontal, m_dockWidget);
	connect(m_sliderTransparency, &QSlider::valueChanged, this,
		[=]
		{
			Chapter4Scene* chapter3Scene = (Chapter4Scene*)m_renderWidget->m_gameApp->getScene();
			if (chapter3Scene)
			{
				float transparency = m_sliderTransparency->value() / 1000.0f;
				chapter3Scene->setMirrorTransparency(transparency);
			}
		});
}

Chapter4DockWidget::~Chapter4DockWidget()
{
	SAFE_RELEASE_SET_NULL(m_labelCamProperty);
	
	SAFE_RELEASE_SET_NULL(m_labelView);
	SAFE_RELEASE_SET_NULL(m_buttonFirstPerson);
	SAFE_RELEASE_SET_NULL(m_buttonFreePerson);
	
	SAFE_RELEASE_SET_NULL(m_labelTransparency);
	SAFE_RELEASE_SET_NULL(m_sliderTransparency);
}

void Chapter4DockWidget::init()
{
	m_dockWidget->show();

	m_labelCamProperty->setText(u8"相机属性:");
	m_labelCamProperty->setFixedHeight(200);

	m_labelView->move(0, 200);
	m_buttonFirstPerson->move(0, 230);
	m_buttonFreePerson->move(0, 260);

	m_labelTransparency->move(0, 290);
	m_sliderTransparency->move(0, 320);
	m_sliderTransparency->setMinimum(0);
	m_sliderTransparency->setMaximum(1000);
	m_sliderTransparency->setSingleStep(1);
	m_sliderTransparency->setValue(500);
}

void Chapter4DockWidget::onCameraMove(const std::string& msg)
{
	m_labelCamProperty->setText(("相机属性:\n" + msg).c_str());
}