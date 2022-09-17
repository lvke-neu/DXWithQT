#include "Chapter10DockWidget.h"
#include "Reflection.h"

REGISTER_CLASS(IChapterDockWidget, "Chapter10DockWidget", Chapter10DockWidget)

Chapter10DockWidget::Chapter10DockWidget(void** parameters) :
	IChapterDockWidget(parameters)
{
	

	m_labelCamProperty = new QLabel(u8"相机属性:", m_dockWidget);

}

Chapter10DockWidget::~Chapter10DockWidget()
{
	SAFE_RELEASE_SET_NULL(m_labelCamProperty);

}

void Chapter10DockWidget::init()
{
	m_dockWidget->show();

	m_labelCamProperty->setText(u8"相机属性:");
	m_labelCamProperty->setFixedHeight(200);
	
}

void Chapter10DockWidget::onCameraMove(const std::string& msg)
{
	m_labelCamProperty->setText( ("相机属性:\n"+ msg).c_str());
}