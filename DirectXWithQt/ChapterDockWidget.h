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

public slots:
	void chapter1_setColor();
	void chapter1_confirmColor(const QColor& color);
	void chapter5_changeDirLight();


public:
	void generateDockWidget(std::string chapterType);

	void initChpa1DockWidget();
	void initChpa2DockWidget();
	void initChpa3DockWidget();
	void initChpa4DockWidget();
	void initChpa5DockWidget();
	void initChpa6DockWidget();
	void initChpa7DockWidget();
	
	void callback(const std::string& msg);

private:
	QMainWindow* m_parent{ nullptr };
	D3d11RenderWidget* m_RenderWidget{ nullptr };
	std::vector<QDockWidget*> m_cptDockWidget;

};