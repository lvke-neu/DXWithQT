#pragma once

#include <QWidget>
#include "../../LkEngineRuntime/Scene/Component/Interface/ComponentInterface.h"


namespace Ui {
	class PickInfoForm;
}



class PickInfoForm : public QWidget
{
	Q_OBJECT

public:
	explicit PickInfoForm(LkEngine::IComponent* pComponent, QWidget *parent = nullptr);
	~PickInfoForm();

public slots:
	void setComponentPorperty();
	LkEngine::Transform  getComponentTransform() { if (m_pComponent) return m_pComponent->getTransform(); return LkEngine::Transform(); }

private:
	Ui::PickInfoForm *ui;
	LkEngine::IComponent* m_pComponent{ nullptr };
};




