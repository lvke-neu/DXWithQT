#pragma once 

#include "ChapterDockWidgetInterface.h"
#include <Qlabel>
#include <QSlider>


class Chapter3DockWidget : public IChapterDockWidget
{
public:
	Chapter3DockWidget() = default;
	Chapter3DockWidget(void** parameters);
	virtual ~Chapter3DockWidget();

	/*override IScen*/
	virtual void init() override;
	/*override Listening*/
	virtual void onCameraMove(const std::string& msg) override;
private:
	QLabel* m_labelCamProperty{ nullptr };

	QLabel* m_labelTransparency{ nullptr };
	QSlider* m_sliderTransparency{ nullptr };
};