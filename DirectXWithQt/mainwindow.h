#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QLabel>
#include <QDialog>
#include <QPushbutton>
#include <QTextEdit>
#include "ui_mainwindow.h"
#include "d3d11renderwidget.h"
#include "ChapterDockWidgetInterface.h"
#include "Service.h"

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
	QLabel* m_labelIntroduction{ nullptr };

	std::map<std::string, IChapterDockWidget*> m_chapterDockWidgets;

};

#endif // MAINWINDOW_H
