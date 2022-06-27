#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "d3d11renderwidget.h"

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
	void changeRenderViewColor();
	void showRenderViewColor(const QColor& qColor);

private:
    Ui::MainWindow *ui;
	D3d11RenderWidget *m_widget{ nullptr };
};

#endif // MAINWINDOW_H
