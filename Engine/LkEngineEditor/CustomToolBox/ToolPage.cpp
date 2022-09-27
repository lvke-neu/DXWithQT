#include "ToolPage.h"
#include "ui_ToolPage.h"

#include <QDebug>
#include <QFormLayout>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>
#include "PickInfoForm.h"
#include "../../LkEngineRuntime/Core/engine/Engine.h"

bool ToolPage::m_bIsExpanded = true;

ToolPage::ToolPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolPage),
    m_pLabel(nullptr)
{
    ui->setupUi(this);

    ui->widgetContent->setAttribute(Qt::WA_StyledBackground);

    m_pLabel = new QLabel(this);
    m_pLabel->setFixedSize(20, 20);
    m_pLabel->setPixmap(QPixmap(":/img/down-arrow.png").scaled(m_pLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    QHBoxLayout *layout = new QHBoxLayout(ui->pushButtonFold);
    layout->setContentsMargins(0, 0, 5, 0);
    layout->addStretch(1);
    layout->addWidget(m_pLabel);

    QFile file(":/qss/toolpage.qss");
    if (file.open(QIODevice::ReadOnly)) {
        setStyleSheet(file.readAll());
    }
    file.close();

    connect(ui->pushButtonFold, &QPushButton::clicked, this, &ToolPage::onPushButtonFoldClicked);

	collapse();
}

ToolPage::~ToolPage()
{
    delete ui;
}

void ToolPage::addWidget(const QString &title, QWidget *widget)
{
	if(title != "SkyBox" && title !="Camera" && title != "Add Component")
		m_PickInfoForm = (PickInfoForm*)widget;

    ui->pushButtonFold->setText(title);
    ui->verticalLayoutContent->addWidget(widget);
}

void ToolPage::expand()
{

	if (m_PickInfoForm)
	{
		LkEngine::Transform transform = m_PickInfoForm->getComponentTransform();
		transform.setPosition(DirectX::XMFLOAT3(transform.getPosition().x, transform.getPosition().y + 10, transform.getPosition().z));
		transform.setRotation(DirectX::XMFLOAT3(1.5f, 0.0f, 0.0f));

		LkEngine::Engine::getInstance().setCameraTransform(transform);
	}

    ui->widgetContent->show();
    m_bIsExpanded = true;

    m_pLabel->setPixmap(QPixmap(":/img/down-arrow.png").scaled(m_pLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void ToolPage::collapse()
{
    ui->widgetContent->hide();
    m_bIsExpanded = false;

    m_pLabel->setPixmap(QPixmap(":/img/left-arrow.png").scaled(m_pLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void ToolPage::onPushButtonFoldClicked()
{
    if (m_bIsExpanded) {
        collapse();
    } else {
        expand();
    }
}
