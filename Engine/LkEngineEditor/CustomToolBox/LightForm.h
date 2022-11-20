#pragma once

#include <QDialog>

namespace Ui {
	class LightForm;
}

class LightForm : public QDialog
{
	Q_OBJECT

public:
	explicit LightForm(QWidget *parent = nullptr);
	~LightForm();

	void initLightProperty();
public slots:
	void setLightProperty();
	void setLightColor();
	void setShadowOrthographicProjMat();
	void onButtonClicked(bool flag);
private:
	Ui::LightForm *ui;

};




