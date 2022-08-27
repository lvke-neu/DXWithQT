#pragma once 

#include "ChapterDockWidgetInterface.h"
#include <Qlabel>
#include <QSlider>
#include <QPushButton>

class Chapter6DockWidget : public IChapterDockWidget
{
public:
	Chapter6DockWidget() = default;
	Chapter6DockWidget(void** parameters);
	virtual ~Chapter6DockWidget();

	/*override IScen*/
	virtual void init() override;
	/*override Listening*/
	void onCameraMove(const std::string& msg)
	{

	}

};