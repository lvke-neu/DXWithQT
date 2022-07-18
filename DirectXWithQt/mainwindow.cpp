#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	m_RenderWidget = new D3d11RenderWidget(this);
	setCentralWidget(m_RenderWidget);

	ui->dockWidget->setFixedWidth(115);
	ui->dockWidget->setTitleBarWidget(new QWidget);


	connect(ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::changeChapter);

	m_ChapterDockWidget = new ChapterDockWidget(this, m_RenderWidget);

}

MainWindow::~MainWindow()
{
	if (ui)
	{
		delete ui;
		ui = nullptr;
	}

	if (m_RenderWidget)
	{
		delete m_RenderWidget;
		m_RenderWidget = nullptr;
	}

	if (m_ChapterDockWidget)
	{
		delete m_ChapterDockWidget;
		m_ChapterDockWidget = nullptr;
	}
}


void MainWindow::changeChapter(QListWidgetItem* item)
{
	m_RenderWidget->m_gameApp->setScene(item->text().toStdString());
	m_ChapterDockWidget->generateDockWidget(item->text().toStdString());
}

