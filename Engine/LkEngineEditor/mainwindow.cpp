#include "mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	setWindowIcon(QIcon("EngineLogo/logo.png"));

}

MainWindow::~MainWindow()
{

}


