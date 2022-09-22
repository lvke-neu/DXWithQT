#pragma once

#include <QWidget>

namespace Ui {
class CameraForm;
}

class CameraForm : public QWidget
{
    Q_OBJECT

public:
	explicit CameraForm(QWidget *parent = nullptr);
	~CameraForm();
public slots:
	void setWireFrame(bool b);
private:
    Ui::CameraForm *ui;
};


