#pragma once 

#include "ChapterDockWidgetInterface.h"
#include <Qlabel>
#include <QPushButton>
#include <QColorDialog>

class Chapter1DockWidget : public IChapterDockWidget
{

public:
	Chapter1DockWidget() = default;
	Chapter1DockWidget(void** parameters);
	virtual ~Chapter1DockWidget();

	virtual void init() override;
slots
	void setColor();
	void confirmColor(const QColor& color);

private:
	QLabel* m_label{ nullptr };
	QPushButton* m_button{ nullptr };
	QColorDialog* m_qColorDialog{ nullptr };
};