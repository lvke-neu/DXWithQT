#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "d3d11renderwidget.h"
#include <qlistwidget.h>

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
	void selectRenderViewColor();
	void confirmRenderViewColor(const QColor& qColor);

private:
    Ui::MainWindow *ui;
	D3d11RenderWidget *m_widget{ nullptr };
};

#endif // MAINWINDOW_H
