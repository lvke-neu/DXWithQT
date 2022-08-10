#include "ChapterDockWidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QColorDialog>
#include <qslider.h>
#include <qlineedit.h>
#include <QRegExpValidator>

ChapterDockWidget::ChapterDockWidget(QMainWindow* parent, D3d11RenderWidget* widget): m_parent(parent), m_RenderWidget(widget)
{
	initChpa1DockWidget();
	initChpa2DockWidget();
	initChpa3DockWidget();
	initChpa4DockWidget();
	initChpa5DockWidget();
	initChpa6DockWidget();
	initChpa7DockWidget();
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
		m_cptDockWidget[3]->hide();
		m_cptDockWidget[4]->hide();
		m_cptDockWidget[5]->hide();
		m_cptDockWidget[6]->hide();
	}
	else if (chapterType == "Chapter 2")
	{
		m_cptDockWidget[0]->hide();
		m_cptDockWidget[1]->show();
		m_cptDockWidget[2]->hide();
		m_cptDockWidget[3]->hide();
		m_cptDockWidget[4]->hide();
		m_cptDockWidget[5]->hide();
		m_cptDockWidget[6]->hide();

		Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_RenderWidget->m_gameApp->getScene();
		if(chapter2Scene)
			chapter2Scene->registerListeningEvent(this);
	}
	else if (chapterType == "Chapter 3")
	{
		m_cptDockWidget[0]->hide();
		m_cptDockWidget[1]->hide();
		m_cptDockWidget[2]->show();
		m_cptDockWidget[3]->hide();
		m_cptDockWidget[4]->hide();
		m_cptDockWidget[5]->hide();
		m_cptDockWidget[6]->hide();

		Chapter3Scene* chapter3Scene = (Chapter3Scene*)m_RenderWidget->m_gameApp->getScene();
		if (chapter3Scene)
			chapter3Scene->registerListeningEvent(this);

	}
	else if(chapterType == "Chapter 4")
	{
		m_cptDockWidget[0]->hide();
		m_cptDockWidget[1]->hide();
		m_cptDockWidget[2]->hide();
		m_cptDockWidget[3]->show();
		m_cptDockWidget[4]->hide();
		m_cptDockWidget[5]->hide();
		m_cptDockWidget[6]->hide();

		Chapter4Scene* chapter4Scene = (Chapter4Scene*)m_RenderWidget->m_gameApp->getScene();
		if (chapter4Scene)
			chapter4Scene->registerListeningEvent(this);
	}
	else if (chapterType == "Chapter 5")
	{
		Chapter5Scene* chapter5Scene = (Chapter5Scene*)m_RenderWidget->m_gameApp->getScene();
		if (chapter5Scene)
			chapter5Scene->registerListeningEvent(this);

		m_cptDockWidget[0]->hide();
		m_cptDockWidget[1]->hide();
		m_cptDockWidget[2]->hide();
		m_cptDockWidget[3]->hide();
		m_cptDockWidget[4]->show();
		m_cptDockWidget[5]->hide();
		m_cptDockWidget[6]->hide();
	}
	else if (chapterType == "Chapter 6")
	{
		m_cptDockWidget[0]->hide();
		m_cptDockWidget[1]->hide();
		m_cptDockWidget[2]->hide();
		m_cptDockWidget[3]->hide();
		m_cptDockWidget[4]->hide();
		m_cptDockWidget[5]->hide();
		m_cptDockWidget[6]->hide();
	}
	else if (chapterType == "Chapter 7")
	{
		Chapter7Scene* chapter7Scene = (Chapter7Scene*)m_RenderWidget->m_gameApp->getScene();
		if (chapter7Scene)
			chapter7Scene->registerListeningEvent(this);

		m_cptDockWidget[0]->hide();
		m_cptDockWidget[1]->hide();
		m_cptDockWidget[2]->hide();
		m_cptDockWidget[3]->hide();
		m_cptDockWidget[4]->hide();
		m_cptDockWidget[5]->hide();
		m_cptDockWidget[6]->show();
	}
	else
	{
		m_cptDockWidget[0]->hide();
		m_cptDockWidget[1]->hide();
		m_cptDockWidget[2]->hide();
		m_cptDockWidget[3]->hide();
		m_cptDockWidget[4]->hide();
		m_cptDockWidget[5]->hide();
		m_cptDockWidget[6]->hide();
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


	QPushButton* button_fog_open = new QPushButton("开启雾效果", dockWidget2);
	button_fog_open->move(0, 580);
	QWidget::connect(button_fog_open, &QPushButton::clicked, this,
		[=]
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_RenderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				chapter2Scene->setFogEnabled(true);
			}
		});


	QPushButton* button_fog_close = new QPushButton("关闭雾效果", dockWidget2);
	button_fog_close->move(0, 610);
	QWidget::connect(button_fog_close, &QPushButton::clicked, this,
		[=]
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_RenderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				chapter2Scene->setFogEnabled(false);
			}
		});

	QLabel* labelFogRange = new QLabel("改变雾的range", dockWidget2);
	labelFogRange->move(0, 640);
	QSlider* qSliderFogRange = new QSlider(Qt::Horizontal, dockWidget2);
	qSliderFogRange->move(0, 670);
	qSliderFogRange->setMinimum(15);
	qSliderFogRange->setMaximum(190);
	qSliderFogRange->setSingleStep(1);
	qSliderFogRange->setValue(75);
	connect(qSliderFogRange, &QSlider::valueChanged, this,
		[=]
		{
			Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_RenderWidget->m_gameApp->getScene();
			if (chapter2Scene)
			{
				chapter2Scene->setFogRange(qSliderFogRange->value());
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

void ChapterDockWidget::initChpa4DockWidget()
{
	//************************************ Chapter 4 *****************************************
	QDockWidget* dockWidget4 = new QDockWidget(m_parent);
	dockWidget4->setFixedWidth(115);
	dockWidget4->setTitleBarWidget(new QWidget);

	QLabel* labelCamProperty = new QLabel(dockWidget4);
	labelCamProperty->setObjectName("CameraProperty");
	labelCamProperty->setFixedHeight(200);


	QPushButton* firstPerson = new QPushButton("第一人称", dockWidget4);
	firstPerson->move(0, 170);
	connect(firstPerson, &QPushButton::clicked, this,
		[=]()
		{
			Chapter4Scene* chapter4Scene = (Chapter4Scene*)m_RenderWidget->m_gameApp->getScene();
			if (chapter4Scene)
			{
				chapter4Scene->setFirstPerson(true);
			}
		});

	QPushButton* freePerson = new QPushButton("自由相机", dockWidget4);
	freePerson->move(0, 200);
	connect(freePerson, &QPushButton::clicked, this,
		[=]()
		{
			Chapter4Scene* chapter4Scene = (Chapter4Scene*)m_RenderWidget->m_gameApp->getScene();
			if (chapter4Scene)
			{
				chapter4Scene->setFirstPerson(false);
			}
		});


	QLabel* labelTransparency = new QLabel(u8"改镜面的透明度", dockWidget4);
	labelTransparency->move(0, 230);
	QSlider* qSlider = new QSlider(Qt::Horizontal, dockWidget4);
	qSlider->move(0, 260);
	qSlider->setMinimum(0);
	qSlider->setMaximum(1000);
	qSlider->setSingleStep(1);
	qSlider->setValue(500);

	QWidget::connect(qSlider, &QSlider::valueChanged, this,
		[=]
		{
			Chapter4Scene* chapter3Scene = (Chapter4Scene*)m_RenderWidget->m_gameApp->getScene();
			if (chapter3Scene)
			{
				float transparency = qSlider->value() / 1000.0f;
				chapter3Scene->setMirrorTransparency(transparency);
			}
		});



	dockWidget4->setObjectName("dockWidget4");
	m_parent->addDockWidget(Qt::RightDockWidgetArea, dockWidget4);
	dockWidget4->hide();
	m_cptDockWidget.push_back(dockWidget4);
}

void ChapterDockWidget::initChpa5DockWidget()
{
	//************************************ Chapter 5 *****************************************
	QDockWidget* dockWidget5 = new QDockWidget(m_parent);
	dockWidget5->setFixedWidth(115);
	dockWidget5->setTitleBarWidget(new QWidget);


	QLabel* labelCamProperty = new QLabel(dockWidget5);
	labelCamProperty->setObjectName("CameraProperty");
	labelCamProperty->setFixedHeight(200);


	QLabel* labelDirLight = new QLabel(u8"方向光方向(x,y,z)：", dockWidget5);
	labelDirLight->move(0, 200);
	
	QSlider* qSliderX;
	QLineEdit* lineDirLightX = new QLineEdit(dockWidget5);
	lineDirLightX->setPlaceholderText("x");
	lineDirLightX->setText("0.5");
	lineDirLightX->move(0, 230);
	lineDirLightX->setObjectName("lineDirLightX");
	lineDirLightX->setReadOnly(true);

	qSliderX = new QSlider(Qt::Horizontal, dockWidget5);
	qSliderX->move(0, 260);
	qSliderX->setMinimum(-1000);
	qSliderX->setMaximum(1000);
	qSliderX->setSingleStep(1);
	qSliderX->setValue(500);
	connect(qSliderX, &QSlider::valueChanged, this,
		[=]
		{
			lineDirLightX->setText( std::to_string(qSliderX->value() / 1000.0f).c_str() );
			chapter5_changeDirLight();
		});

	QSlider* qSliderY;
	QLineEdit* lineDirLightY = new QLineEdit(dockWidget5);
	lineDirLightY->setPlaceholderText("y");
	lineDirLightY->setText("-1.0");
	lineDirLightY->move(0, 290);
	lineDirLightY->setObjectName("lineDirLightY");
	lineDirLightY->setReadOnly(true);

	qSliderY = new QSlider(Qt::Horizontal, dockWidget5);
	qSliderY->move(0, 320);
	qSliderY->setMinimum(-1000);
	qSliderY->setMaximum(1000);
	qSliderY->setSingleStep(1);
	qSliderY->setValue(-1000);
	connect(qSliderY, &QSlider::valueChanged, this,
		[=]
		{
			lineDirLightY->setText(std::to_string(qSliderY->value() / 1000.0f).c_str());
			chapter5_changeDirLight();
		});


	QSlider* qSliderZ;
	QLineEdit* lineDirLightZ = new QLineEdit(dockWidget5);
	lineDirLightZ->setPlaceholderText("z");
	lineDirLightZ->setText("0.0");
	lineDirLightZ->move(0, 350);
	lineDirLightZ->setObjectName("lineDirLightZ");
	lineDirLightZ->setReadOnly(true);

	qSliderZ = new QSlider(Qt::Horizontal, dockWidget5);
	qSliderZ->move(0, 380);
	qSliderZ->setMinimum(-1000);
	qSliderZ->setMaximum(1000);
	qSliderZ->setSingleStep(1);
	qSliderZ->setValue(0);
	connect(qSliderZ, &QSlider::valueChanged, this,
		[=]
		{
			lineDirLightZ->setText(std::to_string(qSliderZ->value() / 1000.0f).c_str());
			chapter5_changeDirLight();
		});


	QPushButton* resetDir = new QPushButton("重置", dockWidget5);
	resetDir->move(0, 420);
	connect(resetDir, &QPushButton::clicked, this,
		[=]()
		{
			Chapter5Scene* chapter5Scene = (Chapter5Scene*)m_RenderWidget->m_gameApp->getScene();
			if (chapter5Scene )
			{
				lineDirLightX->setText("0.0");
				qSliderX->setValue(0);
				lineDirLightY->setText("0.0");	
				qSliderY->setValue(0);
				lineDirLightZ->setText("0.0");
				qSliderZ->setValue(0);
				chapter5Scene->setDirLight(0.0f, 0.0f, 0.0f);
			}
		});

	dockWidget5->setObjectName("dockWidget5");
	m_parent->addDockWidget(Qt::RightDockWidgetArea, dockWidget5);
	dockWidget5->hide();
	m_cptDockWidget.push_back(dockWidget5);
}

void ChapterDockWidget::initChpa6DockWidget()
{
	//************************************ Chapter 7 *****************************************
	QDockWidget* dockWidget6 = new QDockWidget(m_parent);
	dockWidget6->hide();
	m_cptDockWidget.push_back(dockWidget6);
}

void ChapterDockWidget::initChpa7DockWidget()
{
	//************************************ Chapter 7 *****************************************
	QDockWidget* dockWidget7 = new QDockWidget(m_parent);
	dockWidget7->setFixedWidth(115);
	dockWidget7->setTitleBarWidget(new QWidget);

	QLabel* labelCamProperty = new QLabel(dockWidget7);
	labelCamProperty->setObjectName("CameraProperty");
	labelCamProperty->setFixedHeight(200);

	QPushButton* enableFC = new QPushButton("开启视锥体裁剪", dockWidget7);
	enableFC->move(0, 280);
	connect(enableFC, &QPushButton::clicked, this,
		[=]()
		{
			Chapter7Scene* chapter7Scene = (Chapter7Scene*)m_RenderWidget->m_gameApp->getScene();
			if (chapter7Scene)
			{
				chapter7Scene->set_enableFrustumCulling(true);
			}
		});
	
	QPushButton* disableFC = new QPushButton("关闭视锥体裁剪", dockWidget7);
	disableFC->move(0, 310);
	connect(disableFC, &QPushButton::clicked, this,
		[=]()
		{
			Chapter7Scene* chapter7Scene = (Chapter7Scene*)m_RenderWidget->m_gameApp->getScene();
			if (chapter7Scene)
			{
				chapter7Scene->set_enableFrustumCulling(false);
			}
		});

	dockWidget7->setObjectName("dockWidget7");
	m_parent->addDockWidget(Qt::RightDockWidgetArea, dockWidget7);
	dockWidget7->hide();
	m_cptDockWidget.push_back(dockWidget7);
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

void ChapterDockWidget::chapter5_changeDirLight()
{
	QDockWidget* dockWidget5 = m_parent->findChild<QDockWidget*>("dockWidget5");
	if (dockWidget5)
	{
		QLineEdit* lineDirLightX = dockWidget5->findChild<QLineEdit*>("lineDirLightX");
		QLineEdit* lineDirLightY = dockWidget5->findChild<QLineEdit*>("lineDirLightY");
		QLineEdit* lineDirLightZ = dockWidget5->findChild<QLineEdit*>("lineDirLightZ");
		if (lineDirLightX && lineDirLightY && lineDirLightZ)
		{

			bool bX, bY, bZ;
			float x, y, z;
			x = lineDirLightX->text().toFloat(&bX);
			y = lineDirLightY->text().toFloat(&bY);
			z = lineDirLightZ->text().toFloat(&bZ);

			Chapter5Scene* chapter5Scene = (Chapter5Scene*)m_RenderWidget->m_gameApp->getScene();
			if (chapter5Scene && bX && bY &&bZ)
			{
				chapter5Scene->setDirLight(x, y, z);
			}
		}
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

	QDockWidget* dockWidget4 = m_parent->findChild<QDockWidget*>("dockWidget4");
	if (dockWidget4)
	{
		QLabel* labelCamProperty = dockWidget4->findChild<QLabel*>("CameraProperty");
		if (labelCamProperty)
			labelCamProperty->setText(QString(msg.c_str()));
	}

	QDockWidget* dockWidget5 = m_parent->findChild<QDockWidget*>("dockWidget5");
	if (dockWidget5)
	{
		QLabel* labelCamProperty = dockWidget5->findChild<QLabel*>("CameraProperty");
		if (labelCamProperty)
			labelCamProperty->setText(QString(msg.c_str()));
	}

	QDockWidget* dockWidget7 = m_parent->findChild<QDockWidget*>("dockWidget7");
	if (dockWidget7)
	{
		QLabel* labelCamProperty = dockWidget7->findChild<QLabel*>("CameraProperty");
		if (labelCamProperty)
			labelCamProperty->setText(QString(msg.c_str()));
	}
}