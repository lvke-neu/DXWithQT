#pragma once 

#include "ChapterDockWidgetInterface.h"
#include <Qlabel>
#include <QSlider>
#include <QPushButton>

class Chapter4DockWidget : public IChapterDockWidget
{
public:
	Chapter4DockWidget() = default;
	Chapter4DockWidget(void** parameters);
	virtual ~Chapter4DockWidget();

	/*override IScen*/
	virtual void init() override;
	/*override CameraMoveEvent*/
	virtual void onCameraMove(const std::string& msg) override;
private:
	QLabel* m_labelCamProperty{ nullptr };

	QLabel* m_labelView{ nullptr };
	QPushButton* m_buttonFirstPerson{ nullptr };
	QPushButton* m_buttonFreePerson{ nullptr };

	QLabel* m_labelTransparency{ nullptr };
	QSlider* m_sliderTransparency{ nullptr };
};