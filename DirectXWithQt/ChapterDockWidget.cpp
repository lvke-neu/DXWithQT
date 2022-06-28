#include "ChapterDockWidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QColorDialog>

ChapterDockWidget::ChapterDockWidget(QMainWindow* parent, D3d11RenderWidget* widget): m_parent(parent), m_RenderWidget(widget)
{

}

ChapterDockWidget::~ChapterDockWidget()
{

}


void ChapterDockWidget::generateDockWidget(std::string chapterType)
{
	QDockWidget* m_ChapterDockWidget = new QDockWidget(m_parent);
	m_ChapterDockWidget->setFixedWidth(115);
	m_ChapterDockWidget->setTitleBarWidget(new QWidget);

	QLabel* label = new QLabel("show something", m_ChapterDockWidget);
	label->setStyleSheet("QLabel{font:13px;color:red;background-color:rgb(f9,f9,f9);}");

	QPushButton* button = new QPushButton("Color", m_ChapterDockWidget);
	button->move(0, 30);

	m_parent->addDockWidget(Qt::RightDockWidgetArea, m_ChapterDockWidget);

	QWidget::connect(button, &QPushButton::clicked, this, &ChapterDockWidget::selectRenderViewColor);
}


void ChapterDockWidget::selectRenderViewColor()
{
	QColorDialog dlg(m_parent);

	dlg.setWindowTitle("Color Editor");
	dlg.setCurrentColor(QColor(100, 111, 222));


	QWidget::connect(&dlg, &QColorDialog::currentColorChanged, this, &ChapterDockWidget::confirmRenderViewColor);

	if (dlg.exec() == QColorDialog::Accepted)
	{
		QColor color = dlg.selectedColor();
		m_RenderWidget->m_gameApp->setRenderTargetViewColor(color.red() / 255.0f, color.green() / 255.0f, color.blue() / 255.0f, 1.0f);
	}

}

void ChapterDockWidget::confirmRenderViewColor(const QColor& qColor)
{
	m_RenderWidget->m_gameApp->setRenderTargetViewColor(qColor.red() / 255.0f, qColor.green() / 255.0f, qColor.blue() / 255.0f, 1.0f);
}