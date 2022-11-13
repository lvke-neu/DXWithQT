#include "ApplyMatDlg.h"
#include "ui_ApplyMatDlg.h"
#include "../../LkEngineRuntime/Core/engine/Engine.h"
#include "../../LkEngineRuntime/Scene/Pick/PickSystem.h"
#include "../../LkEngineRuntime/Core/base/Utility.h"
#include "../../LkEngineRuntime/Scene/Component/ModelComponent.h"

ApplyMatDlg::ApplyMatDlg(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ApplyMatDlg)
{
	ui->setupUi(this);
	setWindowTitle("Apply to which component");
	connect(ui->allComponetCBX, SIGNAL(activated(QString)), this, SLOT(showComponentAxis(QString)));
	connect(ui->applyMatPB, &QPushButton::clicked, this, &ApplyMatDlg::confirmMat);
}

ApplyMatDlg::~ApplyMatDlg()
{
	delete ui;
}

void ApplyMatDlg::setAllComponet(const std::vector<std::string>&  uuids)
{
	ui->allComponetCBX->clear();
	for (auto& uuid : uuids)
	{
		ui->allComponetCBX->addItem(uuid.c_str());
	}
	showComponentAxis(uuids[0].c_str());
}

void ApplyMatDlg::confirmMat()
{
	IComponent* component = LkEngine::Engine::getInstance().getComponentByUuid(m_currentUuid.toStdString());
	if (component)
	{
		if (component->getComponetType() == "ModelComponent")
			((LkEngine::ModelComponent*)component)->setAllModelCommonMat(m_currentMat);
		else
			component->setMaterial(m_currentMat);
	}
		
}

void ApplyMatDlg::showComponentAxis(QString uuid)
{
	m_currentUuid = uuid;
	LkEngine::PickSystem::getInstance().bindComponent(LkEngine::Engine::getInstance().getComponentByUuid(uuid.toStdString()));
	LkEngine::PickSystem::getInstance().enableShow(true);
}



