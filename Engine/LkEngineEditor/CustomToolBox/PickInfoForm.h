#pragma once

#include <QDialog>
#include "../../LkEngineRuntime/Core/Event/PickEventManager.h"

namespace Ui {
	class PickInfoForm;
}

class ApplyMatDlg;
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
	ApplyMatDlg* m_applyMatDlg{ nullptr };
	LkEngine::IComponent* m_pComponent{ nullptr };
};




