#include "Chapter3DockWidget.h"
#include "Reflection.h"

REGISTER_CLASS(IChapterDockWidget, "Chapter3DockWidget", Chapter3DockWidget)

Chapter3DockWidget::Chapter3DockWidget(void** parameters) :
	IChapterDockWidget(parameters)
{


	m_labelCamProperty = new QLabel(u8"相机属性:", m_dockWidget);

	m_labelTransparency = new QLabel(u8"修改水的透明度:", m_dockWidget);
	m_sliderTransparency =  new QSlider(Qt::Horizontal, m_dockWidget);

	connect(m_sliderTransparency, &QSlider::valueChanged, this,
		[=]
		{
			Chapter3Scene* chapter3Scene = (Chapter3Scene*)m_renderWidget->m_gameApp->getScene();
			if (chapter3Scene)
			{
				float transparency = m_sliderTransparency->value() / 1000.0f;
				chapter3Scene->setWaterTransparency(transparency);
			}
		});
}

Chapter3DockWidget::~Chapter3DockWidget()
{
	SAFE_RELEASE_SET_NULL(m_labelCamProperty);

	SAFE_RELEASE_SET_NULL(m_labelTransparency);
	

	IChapterDockWidget::~IChapterDockWidget();
}

void Chapter3DockWidget::init()
{
	m_dockWidget->show();

	m_labelCamProperty->setText(u8"相机属性:");
	m_labelCamProperty->setFixedHeight(200);

	m_labelTransparency->move(0, 200);
	m_sliderTransparency->move(0, 230);
	m_sliderTransparency->setMinimum(0);
	m_sliderTransparency->setMaximum(1000);
	m_sliderTransparency->setSingleStep(1);
	m_sliderTransparency->setValue(500);

}

void Chapter3DockWidget::onCameraMove(const std::string& msg)
{
	m_labelCamProperty->setText(("相机属性:\n" + msg).c_str());
}