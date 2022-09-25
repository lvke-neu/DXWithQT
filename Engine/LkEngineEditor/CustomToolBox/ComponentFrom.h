#pragma once

#include <QWidget>

namespace Ui {
class ComponentFrom;
}

class ComponentFrom : public QWidget
{
    Q_OBJECT

public:
    explicit ComponentFrom(QWidget *parent = nullptr);
    ~ComponentFrom();

private:
    Ui::ComponentFrom *ui;
};

