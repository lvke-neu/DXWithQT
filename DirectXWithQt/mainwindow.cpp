#include "mainwindow.h"
#include "Reflection.h"

#define CHAPTER_COUNT 10

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

	void* parameters[2];
	parameters[0] = this;
	parameters[1] = m_RenderWidget;

	for (UINT i = 1; i <= CHAPTER_COUNT; i++)
	{
		m_chapterDockWidgets.insert
		(
			std::pair<std::string, IChapterDockWidget*>
			(
				"Chapter " + std::to_string(i), 
				Reflection<IChapterDockWidget>::getInstance().createObject("Chapter" + std::to_string(i) + "DockWidget", parameters)
			)
		);

	}
	


	m_labelIntroduction = new QLabel(this);
	m_labelIntroduction->hide();
	m_labelIntroduction->setAutoFillBackground(true);
	m_labelIntroduction->move(120, 23);
	m_labelIntroduction->setStyleSheet("QLabel{font:13px;color:red;background-color:rgb(f9,f9,f9);}");

}

MainWindow::~MainWindow()
{
	SAFE_RELEASE_SET_NULL(ui);
	SAFE_RELEASE_SET_NULL(m_RenderWidget);
	SAFE_RELEASE_SET_NULL(m_labelIntroduction);
}


void MainWindow::changeChapter(QListWidgetItem* item)
{
	/*设置场景*/
	m_RenderWidget->m_gameApp->setScene(item->text().toStdString());
	
	/*dockwidget初始化，注册各种事件*/
	auto iter_find = m_chapterDockWidgets.find(item->text().toStdString());
	if (iter_find != m_chapterDockWidgets.end())
	{
		iter_find->second->init();

		EventManager::getInstance().registerCameraMoveEvent(iter_find->second);

		if(iter_find->first == "Chapter 8")
			EventManager::getInstance().registerPickEveent(((PickEvent*)iter_find->second));

		for (auto iter = m_chapterDockWidgets.begin(); iter != m_chapterDockWidgets.end(); iter++)
		{
			if (iter != iter_find)
			{
				iter->second->hide();
				EventManager::getInstance().unregisterCameraMoveEvent(iter->second);

				if (iter->first == "Chapter 8")
					EventManager::getInstance().registerPickEveent(((PickEvent*)iter->second));
			}
				
		}
	}

	/*第一次进入场景回调一下相机移动事件*/
	m_RenderWidget->m_gameApp->getScene()->notifyCameraMove();



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

	if (m_labelIntroduction)
	{
		m_labelIntroduction->show();

		if (item->text().toStdString() == "Chapter 1")
		{
			m_labelIntroduction->setText(u8"简单的三角形可以调整其颜色");
			m_labelIntroduction->setFixedWidth(180);
		}
		else if (item->text().toStdString() == "Chapter 2")
		{
			m_labelIntroduction->setText(u8"简单场景框架，带相机交互、光照、贴图、材质\n点击右侧更换贴图、设置光照方向以及设置线框模式和背面裁剪");
			m_labelIntroduction->setFixedWidth(400);
		}
		else if (item->text().toStdString() == "Chapter 3")
		{
			m_labelIntroduction->setText(u8"通过混合模式实现透明效果、立方体的六个面贴不同的贴图、立方体的一个面同时贴两张图\n通过动态的修改贴图坐标让贴图动起来、滑动右侧滑动条来调整水的透明度");
			m_labelIntroduction->setFixedWidth(550);
		}
		else if (item->text().toStdString() == "Chapter 4")
		{
			m_labelIntroduction->setText(u8"通过混合+反射矩阵实现镜面效果、滑动右侧滑动条来调整镜面的透明度\n点击右侧按钮切换第一人称与自由相机");
			m_labelIntroduction->setFixedWidth(430);
		}
		else if (item->text().toStdString() == "Chapter 5")
		{
			m_labelIntroduction->setText(u8"光照（目前只实现方向光）+ 阴影(阴影通过阴影矩阵实现）\n注意阴影矩阵第二个参数的w为零表示方向光、为1表示点光，滑动右侧滑动条来调整方向光的方向");
			m_labelIntroduction->setFixedWidth(600);
		}
		else if (item->text().toStdString() == "Chapter 6")
		{
			m_labelIntroduction->setText(u8"实现了几个类似的序列图效果\n按1切换火焰、按2切换闪电");
			m_labelIntroduction->setFixedWidth(250);
		}
		else if (item->text().toStdString() == "Chapter 7")
		{
			m_labelIntroduction->setText(u8"基于X-jun的ObjReader进行修改，读取模型文件生成模型\n进行视锥体裁剪");
			m_labelIntroduction->setFixedWidth(400);
		}
		else if (item->text().toStdString() == "Chapter 8")
		{
			m_labelIntroduction->setText(u8"鼠标点选，鼠标悬停到物体上会提示选取到对应物体\n点击左键会反射出选中物体的各个属性");
			m_labelIntroduction->setFixedWidth(400);
		}
		else if (item->text().toStdString() == "Chapter 9")
		{
			m_labelIntroduction->setText(u8"静态天空盒，按1白天、按2沙漠、按3日落\n按R开启球面反射、按F关闭球面反射");
			m_labelIntroduction->setFixedWidth(400);
		}
		else if (item->text().toStdString() == "Chapter 10")
		{
			m_labelIntroduction->setText(u8"法线贴图，按c关闭法线贴图，按n开启法线贴图\n同时实现使用assimp库来读取模型文件");
			m_labelIntroduction->setFixedWidth(400);
		}
		else
		{
			m_labelIntroduction->setText(u8"");
			m_labelIntroduction->setFixedWidth(200);
		}
	}
}