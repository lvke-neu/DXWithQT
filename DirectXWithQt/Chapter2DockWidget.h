#pragma once 

#include "ChapterDockWidgetInterface.h"
#include <Qlabel>
#include <QSlider>
#include <QPushButton>
class Chapter2DockWidget : public IChapterDockWidget
{
public:
	Chapter2DockWidget() = default;
	Chapter2DockWidget(void** parameters);
	virtual ~Chapter2DockWidget();

	virtual void init() override;

private:
	QLabel* m_labelCamProperty{ nullptr };

	QLabel* m_labelChangeTexture{ nullptr };
	QPushButton* m_buttonChangeBox1Texture{ nullptr };
	QPushButton* m_buttonChangeBox2Texture{ nullptr };
	QPushButton* m_buttonChangeFloorTexture{ nullptr };

	QLabel* m_labelChangeWireframe{ nullptr };
	QPushButton* m_buttonStartWireframe{ nullptr };
	QPushButton* m_buttonCloseWireframe{ nullptr };

	QLabel* m_labelChangeBackCull{ nullptr };
	QPushButton* m_buttonStartBackCull{ nullptr };
	QPushButton* m_buttonCloseBackCull{ nullptr };

	QLabel* m_labelChangeFog{ nullptr };
	QPushButton* m_buttonStartFog{ nullptr };
	QPushButton* m_buttonCloseFog{ nullptr };
	QSlider* m_sliderFogRange{ nullptr };
};