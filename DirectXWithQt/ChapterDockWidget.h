#pragma once 

#include <QObject>
#include <QMainWindow>
#include <QDockWidget>
#include <qmessagebox.h>
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
	void initChpa8DockWidget();
	void initChpa9DockWidget();

	void callback(const std::string& msg);
	void messaegeBox(const std::string& msg) 
	{ 
		QMessageBox::information(m_RenderWidget, QStringLiteral("Info!"), QString(msg.c_str()), QMessageBox::Ok);
	}
	void stopTimer() { m_RenderWidget->m_Timer.Stop(); }
	void startTimer() { m_RenderWidget->m_Timer.Start(); }
private:
	QMainWindow* m_parent{ nullptr };
	D3d11RenderWidget* m_RenderWidget{ nullptr };
	std::vector<QDockWidget*> m_cptDockWidget;

};