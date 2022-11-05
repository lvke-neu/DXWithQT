#pragma once

#include <QDialog>

namespace Ui {
class ComponentForm;
}

class ComponentForm : public QDialog
{
    Q_OBJECT

public:
    explicit ComponentForm(QWidget *parent = nullptr);
    ~ComponentForm();

private:
    Ui::ComponentForm *ui;
};

