#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QWidget>

namespace Ui {
class ToolBox;
}

class QVBoxLayout;

class ToolBox : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBox(QWidget *parent = nullptr);
    ~ToolBox();

    void addWidget(const std::string &title, QWidget *widget);
	void deleteWidget(const std::string &title);

private:
    Ui::ToolBox *ui;

    QVBoxLayout *m_pContentVBoxLayout;

	std::map<std::string, QWidget *> m_pWidget;
};

#endif // TOOLBOX_H
