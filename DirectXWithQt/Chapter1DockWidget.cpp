#include "Chapter1DockWidget.h"
#include "Reflection.h"
#include "mainwindow.h"

REGISTER_CLASS(IChapterDockWidget, "Chapter1DockWidget", Chapter1DockWidget)


Chapter1DockWidget::Chapter1DockWidget(void* parent) :
	IChapterDockWidget((QMainWindow*)parent)
{
	m_label = new QLabel(u8" Change Color", m_dockWidget);
	m_button = new QPushButton("Color", m_dockWidget);
}

Chapter1DockWidget::Chapter1DockWidget(QMainWindow* parent) :
	IChapterDockWidget(parent)
{
	m_label = new QLabel(u8" Change Color", m_dockWidget);
	m_button = new QPushButton("Color", m_dockWidget);

}

Chapter1DockWidget::~Chapter1DockWidget()
{
	SAFE_RELEASE_SET_NULL(m_label);
	SAFE_RELEASE_SET_NULL(m_button);

	IChapterDockWidget::~IChapterDockWidget();
}

void Chapter1DockWidget::init()
{

	m_dockWidget->show();
	m_label->setStyleSheet("QLabel{font:13px;color:red;background-color:rgb(f9,f9,f9);}");
	m_button->move(0, 50);


}