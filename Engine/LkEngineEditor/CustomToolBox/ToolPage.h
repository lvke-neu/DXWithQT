#ifndef TOOLPAGE_H
#define TOOLPAGE_H

#include <QWidget>

namespace Ui {
class ToolPage;
}

class QFormLayout;
class QLabel;
class ToolPage : public QWidget
{
    Q_OBJECT

public:
    explicit ToolPage(QWidget *parent = nullptr);
    ~ToolPage();

public slots:
    void addWidget(const QString &title, QWidget *widget);
    void expand();
    void collapse();

private slots:
    void onPushButtonFoldClicked();

private:
    Ui::ToolPage *ui;

   
    QLabel *m_pLabel;
public:
	static bool m_bIsExpanded;
};

#endif // TOOLPAGE_H
