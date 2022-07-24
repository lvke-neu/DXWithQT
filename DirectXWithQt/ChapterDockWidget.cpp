#include "ChapterDockWidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QColorDialog>
#include <qslider.h>

ChapterDockWidget::ChapterDockWidget(QMainWindow* parent, D3d11RenderWidget* widget): m_parent(parent), m_RenderWidget(widget)
{
	initChpa1DockWidget();
	initChpa2DockWidget();
	initChpa3DockWidget();
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
		m_cptDockWidget[2]->hide();
	}
	else if (chapterType == "Chapter 2")
	{
		m_cptDockWidget[0]->hide();
		m_cptDockWidget[1]->show();
		m_cptDockWidget[2]->hide();

		Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_RenderWidget->m_gameApp->getScene();
		if(chapter2Scene)
			chapter2Scene->registerListeningEvent(this);
	}
	else if (chapterType == "Chapter 3")
	{
		m_cptDockWidget[0]->hide();
		m_cptDockWidget[1]->hide();
		m_cptDockWidget[2]->show();

		Chapter3Scene* chapter3Scene = (Chapter3Scene*)m_RenderWidget->m_gameApp->getScene();
		if (chapter3Scene)
			chapter3Scene->registerListeningEvent(this);

	}
}



void ChapterDockWidget::initChpa1DockWidget()
{
	//************************************ Chapter 1 *****************************************
	QDockWidget* dockWidget = new QDockWidget(m_parent);
	dockWidget->setFixedWidth(115);
	dockWidget->setTitleBarWidget(new QWidget);


	QLabel* label = new QLabel(u8" Change Color", dockWidget);
	label->setStyleSheet("QLabel{font:13px;color:red;background-color:rgb(f9,f9,f9);}");

	QPushButton* button = new QPushButton("Color", dockWidget);
	button->move(0, 50);
	QWidget::connect(button, &QPushButton::clicked, this, &ChapterDockWidget::chapter1_setColor);


	m_parent->addDockWidget(Qt::RightDockWidgetArea, dockWidget);
	dockWidget->hide();
	m_cptDockWidget.push_back(dockWidget);
}

void ChapterDockWidget::initChpa2DockWidget()
{
	//************************************ Chapter 2 *****************************************

	QDockWidget* dockWidget2 = new QDockWidget(m_parent);
	dockWidget2->setFixedWidth(115);
	dockWidget2->setTitleBarWidget(new QWidget);



	//change texture
	QLabel* labelTexture = new QLabel("换贴图", dockWidget2);

	QPushButton* texture_button1 = new QPushButton("Box1", dockWidget2);
	texture_button1->move(0, 30);
	QWidget::connect(texture_button1, &QPushButton::clicked, this,
		[=]()
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_RenderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				chapter2Scene->changeBox1Texture();
			}
		});

	QPushButton* texture_button2 = new QPushButton("Box2", dockWidget2);
	texture_button2->move(0, 60);
	QWidget::connect(texture_button2, &QPushButton::clicked, this,
		[=]()
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_RenderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				chapter2Scene->changeBox2Texture();
			}
		});

	QPushButton* texture_button3 = new QPushButton("Floor", dockWidget2);
	texture_button3->move(0, 90);
	QWidget::connect(texture_button3, &QPushButton::clicked, this,
		[=]()
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_RenderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				chapter2Scene->changeFloorTexture();
			}
		});



	QLabel* labelLight = new QLabel("改光的方向", dockWidget2);
	labelLight->move(0, 180);
	QSlider* qSlider = new QSlider(Qt::Horizontal, dockWidget2);
	qSlider->move(0, 210);
	qSlider->setMinimum(0);
	qSlider->setMaximum(1000);
	qSlider->setSingleStep(1);
	qSlider->setValue(0);

	QWidget::connect(qSlider, &QSlider::valueChanged, this,
		[=]
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_RenderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				float y = qSlider->value() / 1000.0f - 0.5f;
				XMFLOAT3 dirLight_dir = chapter2Scene->get_dirLight_dir();
				dirLight_dir.y = y;
				chapter2Scene->setDirLight(dirLight_dir);
			}
		});


	QLabel* labelCamProperty = new QLabel(dockWidget2);
	labelCamProperty->setObjectName("CameraProperty");
	labelCamProperty->move(0, 250);
	labelCamProperty->setFixedHeight(200);

	QPushButton* button_wireframe = new QPushButton("开启线框模式", dockWidget2);
	button_wireframe->move(0, 460);
	QWidget::connect(button_wireframe, &QPushButton::clicked, this,
		[=]
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_RenderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				chapter2Scene->setWireframe(true);
			}
		});

	QPushButton* button_wireframe_cancel = new QPushButton("关闭线框模式", dockWidget2);
	button_wireframe_cancel->move(0, 490);
	QWidget::connect(button_wireframe_cancel, &QPushButton::clicked, this,
		[=]
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_RenderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				chapter2Scene->setWireframe(false);
			}
		});


	QPushButton* button_nocull = new QPushButton("无背面裁剪", dockWidget2);
	button_nocull->move(0, 520);
	QWidget::connect(button_nocull, &QPushButton::clicked, this,
		[=]
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_RenderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				chapter2Scene->setNoCull(true);
			}
		});

	QPushButton* button_nocull_cancel = new QPushButton("背面裁剪", dockWidget2);
	button_nocull_cancel->move(0, 550);
	QWidget::connect(button_nocull_cancel, &QPushButton::clicked, this,
		[=]
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_RenderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				chapter2Scene->setNoCull(false);
			}
		});



	dockWidget2->setObjectName("dockWidget2");
	m_parent->addDockWidget(Qt::RightDockWidgetArea, dockWidget2);

	dockWidget2->hide();
	m_cptDockWidget.push_back(dockWidget2);

}

void ChapterDockWidget::initChpa3DockWidget()
{
	//************************************ Chapter 3 *****************************************
	QDockWidget* dockWidget3 = new QDockWidget(m_parent);
	dockWidget3->setFixedWidth(115);
	dockWidget3->setTitleBarWidget(new QWidget);


	QLabel* labelCamProperty = new QLabel(dockWidget3);
	labelCamProperty->setObjectName("CameraProperty");
	labelCamProperty->setFixedHeight(200);


	QLabel* labelTransparency = new QLabel(u8"改水的透明度", dockWidget3);
	labelTransparency->move(0, 220);
	QSlider* qSlider = new QSlider(Qt::Horizontal, dockWidget3);
	qSlider->move(0, 250);
	qSlider->setMinimum(0);
	qSlider->setMaximum(1000);
	qSlider->setSingleStep(1);
	qSlider->setValue(500);

	QWidget::connect(qSlider, &QSlider::valueChanged, this,
		[=]
		{
			Chapter3Scene* chapter3Scene = (Chapter3Scene*)m_RenderWidget->m_gameApp->getScene();
			if (chapter3Scene)
			{
				float transparency = qSlider->value() / 1000.0f;
				chapter3Scene->setWaterTransparency(transparency);
			}
		});



	dockWidget3->setObjectName("dockWidget3");
	m_parent->addDockWidget(Qt::RightDockWidgetArea, dockWidget3);
	dockWidget3->hide();
	m_cptDockWidget.push_back(dockWidget3);
}



void ChapterDockWidget::chapter1_setColor()
{
	QColorDialog dlg(m_parent);

	dlg.setWindowTitle("Color Editor");
	dlg.setCurrentColor(QColor(100, 111, 222));


	QWidget::connect(&dlg, &QColorDialog::currentColorChanged, this, &ChapterDockWidget::chapter1_confirmColor);

	if (dlg.exec() == QColorDialog::Accepted)
	{
		QColor color = dlg.selectedColor();
		Chapter1Scene* chapter1Scene = (Chapter1Scene*)m_RenderWidget->m_gameApp->getScene();
		if (chapter1Scene)
		{
			chapter1Scene->setColor(color.red() / 255.0f, color.green() / 255.0f, color.blue() / 255.0f, 1.0f);
		}
		
	}

}

void ChapterDockWidget::chapter1_confirmColor(const QColor& color)
{
	Chapter1Scene* chapter1Scene = (Chapter1Scene*)m_RenderWidget->m_gameApp->getScene();
	if (chapter1Scene)
	{
		chapter1Scene->setColor(color.red() / 255.0f, color.green() / 255.0f, color.blue() / 255.0f, 1.0f);
	}
}


void ChapterDockWidget::callback(const std::string& msg)
{
	QDockWidget* dockWidget2 = m_parent->findChild<QDockWidget*>("dockWidget2");
	if (dockWidget2)
	{
		QLabel* labelCamProperty = dockWidget2->findChild<QLabel*>("CameraProperty");
		if(labelCamProperty)
			labelCamProperty->setText(QString(msg.c_str()));
	}
		
	QDockWidget* dockWidget3 = m_parent->findChild<QDockWidget*>("dockWidget3");
	if (dockWidget3)
	{
		QLabel* labelCamProperty = dockWidget3->findChild<QLabel*>("CameraProperty");
		if (labelCamProperty)
			labelCamProperty->setText(QString(msg.c_str()));
	}
}