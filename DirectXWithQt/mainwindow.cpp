#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
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

	connect(ui->pushButtonColor, &QPushButton::clicked, this, &MainWindow::changeRenderViewColor);

	

}

MainWindow::~MainWindow()
{
	SAFERELEASE(ui);
	SAFERELEASE(m_widget);
}

void MainWindow::changeRenderViewColor()
{

	QPushButton* button = (QPushButton*)sender();

	if (button->text() == "Color")
	{
		
		QColorDialog dlg(this);

		dlg.setWindowTitle("Color Editor");         
		dlg.setCurrentColor(QColor(100, 111, 222)); 

	
		connect(&dlg, &QColorDialog::currentColorChanged, this, &MainWindow::showRenderViewColor);

		if (dlg.exec() == QColorDialog::Accepted)
		{
			QColor color = dlg.selectedColor();
			m_widget->m_gameApp->setRenderTargetViewColor(color.red() / 255.0f, color.green() / 255.0f, color.blue() / 255.0f, 1.0f);
		}



	}
}

void MainWindow::showRenderViewColor(const QColor& qColor)
{
	m_widget->m_gameApp->setRenderTargetViewColor(qColor.red() / 255.0f, qColor.green() / 255.0f, qColor.blue() / 255.0f, 1.0f);
}