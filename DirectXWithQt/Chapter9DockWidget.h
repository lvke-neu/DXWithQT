#pragma once 

#include "ChapterDockWidgetInterface.h"
#include <Qlabel>
#include <QSlider>
#include <QPushButton>

class Chapter9DockWidget : public IChapterDockWidget
{
public:
	Chapter9DockWidget() = default;
	Chapter9DockWidget(void** parameters);
	virtual ~Chapter9DockWidget();

	/*override IScen*/
	virtual void init() override;
	/*override Listening*/
	virtual void onCameraMove(const std::string& msg) override;
private:
	QLabel* m_labelCamProperty{ nullptr };

};