#include "Chapter6DockWidget.h"
#include "Reflection.h"

REGISTER_CLASS(IChapterDockWidget, "Chapter6DockWidget", Chapter6DockWidget)

Chapter6DockWidget::Chapter6DockWidget(void** parameters) :
	IChapterDockWidget(parameters)
{

}

Chapter6DockWidget::~Chapter6DockWidget()
{

	IChapterDockWidget::~IChapterDockWidget();
}

void Chapter6DockWidget::init()
{
	
}
