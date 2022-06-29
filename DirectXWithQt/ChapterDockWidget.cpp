#include "ChapterDockWidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QColorDialog>

ChapterDockWidget::ChapterDockWidget(QMainWindow* parent, D3d11RenderWidget* widget): m_parent(parent), m_RenderWidget(widget)
{
	QDockWidget* dockWidget = new QDockWidget(m_parent);
	dockWidget->setFixedWidth(115);
	dockWidget->setTitleBarWidget(new QWidget);

	QLabel* label = new QLabel("show something", dockWidget);
	label->setStyleSheet("QLabel{font:13px;color:red;background-color:rgb(f9,f9,f9);}");

	QPushButton* button = new QPushButton("Color", dockWidget);
	button->move(0, 30);

	m_parent->addDockWidget(Qt::RightDockWidgetArea, dockWidget);

	QWidget::connect(button, &QPushButton::clicked, this, &ChapterDockWidget::selectRenderViewColor);

	dockWidget->hide();

	m_cptDockWidget.push_back(dockWidget);

	//*****************************************************************************
	QDockWidget* dockWidget2 = new QDockWidget(m_parent);
	dockWidget2->setFixedWidth(115);
	dockWidget2->setTitleBarWidget(new QWidget);

	QLabel* label2 = new QLabel("show something2", dockWidget2);
	label2->setStyleSheet("QLabel{font:13px;color:red;background-color:rgb(f9,f9,f9);}");

	QPushButton* button2 = new QPushButton("Color2", dockWidget2);
	button2->move(0, 30);

	m_parent->addDockWidget(Qt::RightDockWidgetArea, dockWidget2);

	QWidget::connect(button2, &QPushButton::clicked, this, &ChapterDockWidget::selectRenderViewColor);

	dockWidget2->hide();

	m_cptDockWidget.push_back(dockWidget2);




}

ChapterDockWidget::~ChapterDockWidget()
{
	for (auto x : m_cptDockWidget)
	{
		if (x)
		{
			delete x;
			x = nullptr;
		}
	}
}


void ChapterDockWidget::generateDockWidget(std::string chapterType)
{
	if (chapterType == "Chapter 1")
	{
		m_cptDockWidget[0]->show();
		m_cptDockWidget[1]->hide();
	}
	else if (chapterType == "Chapter 2")
	{
		m_cptDockWidget[0]->hide();
		m_cptDockWidget[1]->show();
	}
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