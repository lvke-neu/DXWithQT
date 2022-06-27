#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "d3d11renderwidget.h"


#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	D3d11RenderWidget *widget = new D3d11RenderWidget(this);
	setCentralWidget(widget);


	ui->dockWidget->setFixedWidth(120);
	ui->dockWidget->setTitleBarWidget(new QWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
