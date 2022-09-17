#pragma once 

#include "ChapterDockWidgetInterface.h"
#include <Qlabel>
#include <QSlider>
#include <QPushButton>

class Chapter10DockWidget : public IChapterDockWidget
{
public:
	Chapter10DockWidget() = default;
	Chapter10DockWidget(void** parameters);
	virtual ~Chapter10DockWidget();

	/*override IScen*/
	virtual void init() override;
	/*override CameraMoveEvent*/
	virtual void onCameraMove(const std::string& msg) override;
private:
	QLabel* m_labelCamProperty{ nullptr };

};