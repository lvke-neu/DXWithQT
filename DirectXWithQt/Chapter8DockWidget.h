#pragma once 

#include "ChapterDockWidgetInterface.h"
#include <Qlabel>
#include <QSlider>
#include <QPushButton>

class Chapter8DockWidget : public IChapterDockWidget
{
public:
	Chapter8DockWidget() = default;
	Chapter8DockWidget(void** parameters);
	virtual ~Chapter8DockWidget();

	/*override IScen*/
	virtual void init() override;
	/*override Listening*/
	virtual void onCameraMove(const std::string& msg) override;
private:
	QLabel* m_labelCamProperty{ nullptr };

};