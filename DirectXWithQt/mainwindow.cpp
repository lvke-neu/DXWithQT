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

	QDockWidget *dock_widget = new QDockWidget("浮动窗口", this);    
	this->addDockWidget(Qt::LeftDockWidgetArea, dock_widget);     
	dock_widget->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);


}

MainWindow::~MainWindow()
{
    delete ui;
}
