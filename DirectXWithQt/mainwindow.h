#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "ui_mainwindow.h"
#include "d3d11renderwidget.h"
#include "ChapterDockWidgetInterface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	//friend class IChapterDockWidget;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



public slots:
    void changeChapter(QListWidgetItem* item);

public:
	void setIntroduction(QListWidgetItem* item);
private:
    Ui::MainWindow *ui;
	D3d11RenderWidget *m_RenderWidget{ nullptr };
	std::map<std::string, IChapterDockWidget*> m_chapterDockWidgets;
};

#endif // MAINWINDOW_H
