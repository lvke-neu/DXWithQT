#pragma once 

#include <QObject>
#include <QMainWindow>
#include <QDockWidget>
#include <string>
#include "d3d11renderwidget.h"

class ChapterDockWidget : public QObject
{
	Q_OBJECT
public:
	ChapterDockWidget(QMainWindow* parent, D3d11RenderWidget* widget);
	virtual ~ChapterDockWidget();
public:
	void generateDockWidget(std::string chapterType);

public slots:
	void selectRenderViewColor();
	void confirmRenderViewColor(const QColor& qColor);

private:
	QMainWindow* m_parent{ nullptr };
	D3d11RenderWidget* m_RenderWidget{ nullptr };

};