#pragma once 

#include "ChapterDockWidgetInterface.h"
#include <Qlabel>
#include <QSlider>
#include <QPushButton>
#include <QLineEdit>

class Chapter5DockWidget : public IChapterDockWidget
{
public:
	Chapter5DockWidget() = default;
	Chapter5DockWidget(void** parameters);
	virtual ~Chapter5DockWidget();

	/*override IScen*/
	virtual void init() override;
	/*override CameraMoveEvent*/
	virtual void onCameraMove(const std::string& msg) override;

	void changeDirLight();
private:
	QLabel* m_labelCamProperty{ nullptr };

	QLabel* m_labelDirLightDir{ nullptr };

	QLineEdit* m_lineEditDirLightX;
	QSlider*  m_sliderDirLightX;

	QLineEdit* m_lineEditDirLightY{ nullptr };
	QSlider*  m_sliderDirLightY{ nullptr };

	QLineEdit* m_lineEditDirLightZ{ nullptr };
	QSlider*  m_sliderDirLightZ{ nullptr };

	QPushButton* m_buttonReset{ nullptr };
};