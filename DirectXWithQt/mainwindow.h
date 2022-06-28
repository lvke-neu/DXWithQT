#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "d3d11renderwidget.h"
#include "ChapterDockWidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



public slots:
    void changeChapter(QListWidgetItem* item);


private:
    Ui::MainWindow *ui;
	D3d11RenderWidget *m_RenderWidget{ nullptr };
    ChapterDockWidget* m_ChapterDockWidget{ nullptr };
};

#endif // MAINWINDOW_H
