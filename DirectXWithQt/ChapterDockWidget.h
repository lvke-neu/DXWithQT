#pragma once 

#include <QObject>
#include <QMainWindow>
#include <QDockWidget>
#include <string>
#include <vector>
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
	void chapter1_setColor();
	void chapter1_confirmColor(const QColor& color);

	void chapter2_changeTexture();

private:
	QMainWindow* m_parent{ nullptr };
	D3d11RenderWidget* m_RenderWidget{ nullptr };
	std::vector<QDockWidget*> m_cptDockWidget;

};