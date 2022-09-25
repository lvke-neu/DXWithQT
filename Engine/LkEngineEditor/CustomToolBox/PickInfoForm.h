#pragma once

#include <QWidget>
#include "../../LkEngineRuntime/Core/Event/PickEventManager.h"


namespace Ui {
	class PickInfoForm;
}



class PickInfoForm : public QWidget, public LkEngine::PickEvent
{
	Q_OBJECT

public:
	explicit PickInfoForm(QWidget *parent = nullptr);
	~PickInfoForm();
	virtual void onPickComponent(LkEngine::IComponent* component) override;
public slots:
	void setComponentPorperty();

private:
	LkEngine::IComponent* m_pickedComponent{ nullptr };
private:
	Ui::PickInfoForm *ui;
};




