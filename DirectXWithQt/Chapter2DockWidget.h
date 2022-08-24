#pragma once 

#include "ChapterDockWidgetInterface.h"
#include <Qlabel>
#include <QSlider>

class Chapter2DockWidget : public IChapterDockWidget
{
public:
	Chapter2DockWidget() = default;
	Chapter2DockWidget(void* parent);
	Chapter2DockWidget(QMainWindow* parent);
	virtual ~Chapter2DockWidget();

	virtual void init() override;

private:
	QLabel* m_label{ nullptr };

};