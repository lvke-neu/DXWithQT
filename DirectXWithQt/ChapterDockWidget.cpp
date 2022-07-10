#include "ChapterDockWidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QColorDialog>

ChapterDockWidget::ChapterDockWidget(QMainWindow* parent, D3d11RenderWidget* widget): m_parent(parent), m_RenderWidget(widget)
{
	
	//************************************ Chapter 1 *****************************************
	QDockWidget* dockWidget = new QDockWidget(m_parent);
	dockWidget->setFixedWidth(115);
	dockWidget->setTitleBarWidget(new QWidget);


	QLabel* label = new QLabel(u8" Change Color", dockWidget);
	label->setStyleSheet("QLabel{font:13px;color:red;background-color:rgb(f9,f9,f9);}");

	QPushButton* button = new QPushButton("Color", dockWidget);
	button->move(0, 50);

	m_parent->addDockWidget(Qt::RightDockWidgetArea, dockWidget);

	QWidget::connect(button, &QPushButton::clicked, this, &ChapterDockWidget::chapter1_setColor);

	dockWidget->hide();

	m_cptDockWidget.push_back(dockWidget);


	//************************************ Chapter 2 *****************************************
	QDockWidget* dockWidget2 = new QDockWidget(m_parent);
	dockWidget2->setFixedWidth(115);
	dockWidget2->setTitleBarWidget(new QWidget);


	QPushButton* button_change_box_texture = new QPushButton("Change1", dockWidget2);
	QWidget::connect(button_change_box_texture, &QPushButton::clicked, this, &ChapterDockWidget::chapter2_change);
	

	QPushButton* button_change_floor_texture = new QPushButton("Change2", dockWidget2);
	button_change_floor_texture->move(0, 30);
	QWidget::connect(button_change_floor_texture, &QPushButton::clicked, this, &ChapterDockWidget::chapter2_change);



	/*
		Material
	*/
	QLabel *lael1 = new QLabel("Material", dockWidget2);
	lael1->move(0, 90);

	QPushButton* MatAmbient = new QPushButton("MatAmbient", dockWidget2);
	MatAmbient->move(0, 120);
	QWidget::connect(MatAmbient, &QPushButton::clicked, this, &ChapterDockWidget::chapter2_change);


	QPushButton* MatDiffuse = new QPushButton("MatDiffuse", dockWidget2);
	MatDiffuse->move(0, 150);
	QWidget::connect(MatDiffuse, &QPushButton::clicked, this, &ChapterDockWidget::chapter2_change);


	QPushButton* MatSpecular = new QPushButton("MatSpecular", dockWidget2);
	MatSpecular->move(0, 180);
	QWidget::connect(MatSpecular, &QPushButton::clicked, this, &ChapterDockWidget::chapter2_change);









	m_parent->addDockWidget(Qt::RightDockWidgetArea, dockWidget2);

	dockWidget2->hide();
	m_cptDockWidget.push_back(dockWidget2);




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
	}
	else if (chapterType == "Chapter 2")
	{
		m_cptDockWidget[0]->hide();
		m_cptDockWidget[1]->show();
	}
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



void ChapterDockWidget::chapter2_change()
{
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	//获取按钮显示文本
	QString text = btn->text();


	Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_RenderWidget->m_gameApp->getScene();
	if (text == "Change1")
	{
		if(chapter2Scene)
			chapter2Scene->changeBoxTexture();
	}
	else if (text == "Change2")
	{
		if (chapter2Scene)
			chapter2Scene->changeFloorTexture();
	}
	else if (text == "MatAmbient")
	{

		QColorDialog dlg(m_parent);

		dlg.setWindowTitle("MatAmbient");
		dlg.setCurrentColor(QColor(100, 111, 222));

		QWidget::connect(&dlg, &QColorDialog::currentColorChanged, this, &ChapterDockWidget::chapter2_change_ambient);

		dlg.exec();
	}
	else if (text == "MatDiffuse")
	{

		QColorDialog dlg(m_parent);

		dlg.setWindowTitle("MatDiffuse");
		dlg.setCurrentColor(QColor(100, 111, 222));

		QWidget::connect(&dlg, &QColorDialog::currentColorChanged, this, &ChapterDockWidget::chapter2_change_diffuse);

		dlg.exec();
	}
	else if (text == "MatSpecular")
	{

		QColorDialog dlg(m_parent);

		dlg.setWindowTitle("MatSpecular");
		dlg.setCurrentColor(QColor(100, 111, 222));

		QWidget::connect(&dlg, &QColorDialog::currentColorChanged, this, &ChapterDockWidget::chapter2_change_specular);

		dlg.exec();
	}

}

void ChapterDockWidget::chapter2_change_ambient(const QColor& color)
{
	Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_RenderWidget->m_gameApp->getScene();
	if (chapter2Scene)
	{
		chapter2Scene->setAmbient(XMFLOAT4(color.red() / 255.0f, color.green() / 255.0f, color.blue() / 255.0f, 1.0f));
	}
}
void ChapterDockWidget::chapter2_change_diffuse(const QColor& color)
{
	Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_RenderWidget->m_gameApp->getScene();
	if (chapter2Scene)
	{
		chapter2Scene->setDiffuse(XMFLOAT4(color.red() / 255.0f, color.green() / 255.0f, color.blue() / 255.0f, 1.0f));
	}
}
void ChapterDockWidget::chapter2_change_specular(const QColor& color)
{
	Chapter2Scene* chapter2Scene = (Chapter2Scene*)m_RenderWidget->m_gameApp->getScene();
	if (chapter2Scene)
	{
		chapter2Scene->setSpecula(XMFLOAT4(color.red() / 255.0f, color.green() / 255.0f, color.blue() / 255.0f, 5.0f));
	}
}

void ChapterDockWidget::callbackFromGameApp(float test)
{
	QDockWidget* dockWidget2 = m_parent->findChild<QDockWidget*>("dockWidget2");

	QLabel* label2 = dockWidget2->findChild<QLabel*>("CameraProperty");
	label2->setText(QString(std::to_string(test).c_str()));
}