#pragma once

#include <QDialog>

namespace Ui {
class SkyBoxForm;
}

class SkyBoxForm : public QDialog
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


