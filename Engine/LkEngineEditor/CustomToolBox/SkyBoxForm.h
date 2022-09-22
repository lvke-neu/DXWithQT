#pragma once

#include <QWidget>

namespace Ui {
class SkyBoxForm;
}

class SkyBoxForm : public QWidget
{
    Q_OBJECT

public:
	explicit SkyBoxForm(QWidget *parent = nullptr);
	~SkyBoxForm();
public slots:
	void setSkyBoxTexture(QString skyBoxTexture);
private:
    Ui::SkyBoxForm *ui;
};


