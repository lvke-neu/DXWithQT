#include "ChapterDockWidgetInterface.h"

IChapterDockWidget::IChapterDockWidget(QMainWindow* parent) :
	m_parentWindow(parent)
{
	if (m_parentWindow)
	{
		m_dockWidget = new QDockWidget(m_parentWindow);
		m_dockWidget->setFixedWidth(115);
		m_dockWidget->setTitleBarWidget(new QWidget);
		m_parentWindow->addDockWidget(Qt::RightDockWidgetArea, m_dockWidget);
		m_dockWidget->hide();
	}
}

IChapterDockWidget::~IChapterDockWidget()
{
	SAFE_RELEASE_SET_NULL(m_dockWidget);
}
