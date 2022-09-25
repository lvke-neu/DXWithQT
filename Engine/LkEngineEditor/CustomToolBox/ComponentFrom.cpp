#include "ComponentFrom.h"
#include "ui_ComponentFrom.h"

ComponentFrom::ComponentFrom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComponentFrom)
{
    ui->setupUi(this);
}

ComponentFrom::~ComponentFrom()
{
    delete ui;
}
