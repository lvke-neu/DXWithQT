#pragma once 

#include "ChapterDockWidgetInterface.h"
#include <Qlabel>
#include <QPushButton>

class Chapter1DockWidget : public IChapterDockWidget
{
public:
	Chapter1DockWidget() = default;
	Chapter1DockWidget(void* parent);
	Chapter1DockWidget(QMainWindow* parent);
	virtual ~Chapter1DockWidget();

	virtual void init() override;

private:
	QLabel* m_label{ nullptr };
	QPushButton* m_button{ nullptr };
};