#include "Chapter2DockWidget.h"
#include "Reflection.h"


REGISTER_CLASS(IChapterDockWidget, "Chapter2DockWidget", Chapter2DockWidget)


Chapter2DockWidget::Chapter2DockWidget(void* parent) :
	IChapterDockWidget((QMainWindow*)parent)
{
	m_label = new QLabel(u8" 222222", m_dockWidget);

}

Chapter2DockWidget::Chapter2DockWidget(QMainWindow* parent) :
	IChapterDockWidget(parent)
{


}

Chapter2DockWidget::~Chapter2DockWidget()
{

	SAFE_RELEASE_SET_NULL(m_label);

	IChapterDockWidget::~IChapterDockWidget();
}

void Chapter2DockWidget::init()
{
	m_dockWidget->show();
	m_label->setStyleSheet("QLabel{font:13px;color:red;background-color:rgb(f9,f9,f9);}");

}