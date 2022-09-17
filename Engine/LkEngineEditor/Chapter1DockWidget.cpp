#include "Chapter1DockWidget.h"
#include "Reflection.h"


REGISTER_CLASS(IChapterDockWidget, "Chapter1DockWidget", Chapter1DockWidget)


Chapter1DockWidget::Chapter1DockWidget(void** parameters) :
	IChapterDockWidget(parameters)
{
	m_label = new QLabel(u8" Change Color", m_dockWidget);
	m_button = new QPushButton("Color", m_dockWidget);
	m_qColorDialog = new QColorDialog(m_parentWindow);
	connect(m_button, &QPushButton::clicked, this, &Chapter1DockWidget::setColor);
}


Chapter1DockWidget::~Chapter1DockWidget()
{
	SAFE_RELEASE_SET_NULL(m_label);
	SAFE_RELEASE_SET_NULL(m_button);
	SAFE_RELEASE_SET_NULL(m_qColorDialog);

}

void Chapter1DockWidget::init()
{
	m_dockWidget->show();
	m_label->setStyleSheet("QLabel{font:13px;color:red;background-color:rgb(f9,f9,f9);}");
	m_button->move(0, 50);
	m_qColorDialog->setWindowTitle("Color Editor");
	m_qColorDialog->setCurrentColor(QColor(0, 255, 0));
}

void Chapter1DockWidget::setColor()
{

	QColor beforeColor = m_qColorDialog->currentColor();


	connect(m_qColorDialog, &QColorDialog::currentColorChanged, this, &Chapter1DockWidget::confirmColor);

	if (m_qColorDialog->exec() == QColorDialog::Accepted)
	{
		QColor color = m_qColorDialog->selectedColor();
		Chapter1Scene* chapter1Scene = (Chapter1Scene*)m_renderWidget->m_gameApp->getScene();
		if (chapter1Scene)
		{
			chapter1Scene->setColor(color.red() / 255.0f, color.green() / 255.0f, color.blue() / 255.0f, 1.0f);
		}

	}
	else
	{
		Chapter1Scene* chapter1Scene = (Chapter1Scene*)m_renderWidget->m_gameApp->getScene();
		if (chapter1Scene)
		{
			chapter1Scene->setColor(beforeColor.red() / 255.0f, beforeColor.green() / 255.0f, beforeColor.blue() / 255.0f, 1.0f);
		}
	}

}

void Chapter1DockWidget::confirmColor(const QColor& color)
{
	Chapter1Scene* chapter1Scene = (Chapter1Scene*)m_renderWidget->m_gameApp->getScene();
	if (chapter1Scene)
	{
		chapter1Scene->setColor(color.red() / 255.0f, color.green() / 255.0f, color.blue() / 255.0f, 1.0f);
	}
}