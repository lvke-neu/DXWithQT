
#include "ChapterDockWidgetInterface.h"


IChapterDockWidget::IChapterDockWidget(void** parameters) 
{
	m_parentWindow = (QMainWindow*)parameters[0];
	m_renderWidget = (D3d11RenderWidget*)parameters[1];

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

void IChapterDockWidget::hide()
{
	m_dockWidget->hide();
}
