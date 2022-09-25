#pragma once

#include <QWidget>

namespace Ui {
class ComponentForm;
}

class ComponentForm : public QWidget
{
    Q_OBJECT

public:
    explicit ComponentForm(QWidget *parent = nullptr);
    ~ComponentForm();

private:
    Ui::ComponentForm *ui;
};

