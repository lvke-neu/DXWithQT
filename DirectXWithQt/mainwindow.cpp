#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qdebug.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	m_widget = new D3d11RenderWidget(this);
	setCentralWidget(m_widget);

	ui->dockWidget->setFixedWidth(120);
	ui->dockWidget->setTitleBarWidget(new QWidget);

	connect(ui->pushButtonRed, &QPushButton::clicked, this, &MainWindow::changeRenderViewColor);
	connect(ui->pushButtonGreen, &QPushButton::clicked, this, &MainWindow::changeRenderViewColor);
	connect(ui->pushButtonBlue, &QPushButton::clicked, this, &MainWindow::changeRenderViewColor);
	

}

MainWindow::~MainWindow()
{
	SAFERELEASE(ui);
	SAFERELEASE(m_widget);
}

void MainWindow::changeRenderViewColor()
{

	QPushButton* button = (QPushButton*)sender();

	if (button->text() == "Red")
	{
		m_widget->m_gameApp->setRenderTargetViewColor(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else if (button->text() == "Green")
	{
		m_widget->m_gameApp->setRenderTargetViewColor(0.0f, 1.0f, 0.0f, 1.0f);
	}
	else
	{
		m_widget->m_gameApp->setRenderTargetViewColor(0.0f, 0.0f, 1.0f, 1.0f);
	}
}