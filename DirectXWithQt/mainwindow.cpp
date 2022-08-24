#include "mainwindow.h"
#include <QLabel>
#include "Reflection.h"

#define CHAPTER_COUNT 2

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


	for (UINT i = 1; i <= CHAPTER_COUNT; i++)
	{
		m_chapterDockWidgets.insert
		(
			std::pair<std::string, IChapterDockWidget*>
			(
				"Chapter " + std::to_string(i), 
				Reflection<IChapterDockWidget>::getInstance().createObject("Chapter" + std::to_string(i) + "DockWidget", this)
			)
		);

	}
	


	QLabel* introductionLabel = new QLabel(this);
	introductionLabel->hide();
	introductionLabel->setObjectName("introductionLabel");
	introductionLabel->setAutoFillBackground(true);
	introductionLabel->move(120, 23);
	introductionLabel->setStyleSheet("QLabel{font:13px;color:red;background-color:rgb(f9,f9,f9);}");

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


}


void MainWindow::changeChapter(QListWidgetItem* item)
{

	auto iter_find = m_chapterDockWidgets.find(item->text().toStdString());
	if (iter_find != m_chapterDockWidgets.end())
	{
		iter_find->second->init();
		for (auto iter = m_chapterDockWidgets.begin(); iter != m_chapterDockWidgets.end() && iter != iter_find; iter++)
		{
			iter->second->hide();
		}
	}

	m_RenderWidget->m_gameApp->setScene(item->text().toStdString());



	if (item->text().toStdString() == "Chapter 2" || item->text().toStdString() == "Chapter 7")
	{
		m_RenderWidget->m_gameApp->setRenderTargetViewColor(0.752941251f, 0.752941251f, 0.752941251f, 1.000000000f);
	}
	else
	{
		m_RenderWidget->m_gameApp->setRenderTargetViewColor(0.0f, 0.0f, 0.0f, 1.000000000f);
	}

	setIntroduction(item);
}

void MainWindow::setIntroduction(QListWidgetItem* item)
{
	QLabel* introductionLabel = findChild<QLabel*>("introductionLabel");
	if (introductionLabel)
	{
		introductionLabel->show();

		if (item->text().toStdString() == "Chapter 1")
		{
			introductionLabel->setText(u8"简单的三角形可以调整其颜色");
			introductionLabel->setFixedWidth(180);
		}
		else if (item->text().toStdString() == "Chapter 2")
		{
			introductionLabel->setText(u8"简单场景框架，带相机交互、光照、贴图、材质\n点击右侧更换贴图、设置光照方向以及设置线框模式和背面裁剪");
			introductionLabel->setFixedWidth(400);
		}
		else if (item->text().toStdString() == "Chapter 3")
		{
			introductionLabel->setText(u8"通过混合模式实现透明效果、立方体的六个面贴不同的贴图、立方体的一个面同时贴两张图\n通过动态的修改贴图坐标让贴图动起来、滑动右侧滑动条来调整水的透明度");
			introductionLabel->setFixedWidth(550);
		}
		else if (item->text().toStdString() == "Chapter 4")
		{
			introductionLabel->setText(u8"通过混合+反射矩阵实现镜面效果、滑动右侧滑动条来调整镜面的透明度\n点击右侧按钮切换第一人称与自由相机");
			introductionLabel->setFixedWidth(430);
		}
		else if (item->text().toStdString() == "Chapter 5")
		{
			introductionLabel->setText(u8"光照（目前只实现方向光）+ 阴影(阴影通过阴影矩阵实现）\n注意阴影矩阵第二个参数的w为零表示方向光、为1表示点光，滑动右侧滑动条来调整方向光的方向");
			introductionLabel->setFixedWidth(600);
		}
		else if (item->text().toStdString() == "Chapter 6")
		{
			introductionLabel->setText(u8"实现了几个类似的序列图效果\n按1切换火焰、按2切换闪电");
			introductionLabel->setFixedWidth(250);
		}
		else if (item->text().toStdString() == "Chapter 7")
		{
			introductionLabel->setText(u8"基于X-jun的ObjReader进行修改，读取模型文件生成模型\n进行视锥体裁剪");
			introductionLabel->setFixedWidth(400);
		}
		else if (item->text().toStdString() == "Chapter 8")
		{
			introductionLabel->setText(u8"鼠标点选");
			introductionLabel->setFixedWidth(200);
		}
		else if (item->text().toStdString() == "Chapter 9")
		{
			introductionLabel->setText(u8"静态天空盒，按1白天、按2沙漠、按3日落\n按R开启球面反射、按F关闭球面反射");
			introductionLabel->setFixedWidth(400);
		}
		else
		{
			introductionLabel->setText(u8"");
			introductionLabel->setFixedWidth(200);
		}
	}
}