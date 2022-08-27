#include "Chapter8DockWidget.h"
#include "Reflection.h"

REGISTER_CLASS(IChapterDockWidget, "Chapter8DockWidget", Chapter8DockWidget)

Chapter8DockWidget::Chapter8DockWidget(void** parameters) :
	IChapterDockWidget(parameters)
{


	m_labelCamProperty = new QLabel(u8"相机属性:", m_dockWidget);

	

}

Chapter8DockWidget::~Chapter8DockWidget()
{
	SAFE_RELEASE_SET_NULL(m_labelCamProperty);


	IChapterDockWidget::~IChapterDockWidget();
}

void Chapter8DockWidget::init()
{
	m_dockWidget->show();

	m_labelCamProperty->setText(u8"相机属性:");
	m_labelCamProperty->setFixedHeight(200);



}

void Chapter8DockWidget::onCameraMove(const std::string& msg)
{
	m_labelCamProperty->setText(("相机属性:\n" + msg).c_str());
}