#pragma once 

#include "ChapterDockWidgetInterface.h"
#include <Qlabel>


class Chapter6DockWidget : public IChapterDockWidget
{
public:
	Chapter6DockWidget() = default;
	Chapter6DockWidget(void** parameters);
	virtual ~Chapter6DockWidget();

	/*override IScen*/
	virtual void init() override;
};