#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <qdebug.h>
#include <qlabel.h>
#include <qpushbutton.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	m_widget = new D3d11RenderWidget(this);
	setCentralWidget(m_widget);

	ui->dockWidget->setFixedWidth(115);
	ui->dockWidget->setTitleBarWidget(new QWidget);


	connect(ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::changeChapter);
}

MainWindow::~MainWindow()
{
	SAFERELEASE(ui);
	SAFERELEASE(m_widget);
}


void MainWindow::changeChapter(QListWidgetItem* item)
{
	if (item->text() == "Chapter 1")
	{
		QDockWidget* dockWidget = new QDockWidget(this);
		dockWidget->setFixedWidth(115);
		dockWidget->setTitleBarWidget(new QWidget);
		dockWidget->setLayout(new QGridLayout());

		QLabel* label = new QLabel("show something", dockWidget);
		label->setStyleSheet("QLabel{font:13px;color:red;background-color:rgb(f9,f9,f9);}");

		QPushButton* button = new QPushButton("Color", dockWidget);
		button->move(0, 30);
		
		this->addDockWidget(Qt::RightDockWidgetArea, dockWidget);

		connect(button, &QPushButton::clicked, this, &MainWindow::selectRenderViewColor);

	}
}


void MainWindow::selectRenderViewColor()
{

	QPushButton* button = (QPushButton*)sender();

	if (button->text() == "Color")
	{
		
		QColorDialog dlg(this);

		dlg.setWindowTitle("Color Editor");         
		dlg.setCurrentColor(QColor(100, 111, 222)); 

	
		connect(&dlg, &QColorDialog::currentColorChanged, this, &MainWindow::confirmRenderViewColor);

		if (dlg.exec() == QColorDialog::Accepted)
		{
			QColor color = dlg.selectedColor();
			m_widget->m_gameApp->setRenderTargetViewColor(color.red() / 255.0f, color.green() / 255.0f, color.blue() / 255.0f, 1.0f);
		}

	}
}

void MainWindow::confirmRenderViewColor(const QColor& qColor)
{
	m_widget->m_gameApp->setRenderTargetViewColor(qColor.red() / 255.0f, qColor.green() / 255.0f, qColor.blue() / 255.0f, 1.0f);
}