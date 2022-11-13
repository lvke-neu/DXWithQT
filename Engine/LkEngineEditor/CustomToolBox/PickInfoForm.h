#pragma once

#include <QDialog>
#include "../../LkEngineRuntime/Core/Event/PickEventManager.h"

namespace Ui {
	class PickInfoForm;
}

class PickInfoForm : public QDialog, public LkEngine::PickEvent, public LkEngine::DeleteComponentEvent
{
	Q_OBJECT

public:
	explicit PickInfoForm(QWidget *parent = nullptr);
	~PickInfoForm();

public slots:
	void setComponentPorperty();
	void setAxisPorperty();
	void setMaterialColor();
	void setMaterialColorDlg();
public:
	virtual void onPickComponent(LkEngine::IComponent* component) override;
	virtual void onDeleteComponent(LkEngine::IComponent* component) override;
private:
	Ui::PickInfoForm *ui;
	LkEngine::IComponent* m_pComponent{ nullptr };
};




