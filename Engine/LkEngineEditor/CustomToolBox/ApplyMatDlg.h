 #pragma once

#include <QDialog>
#include <QCombobox>
#include "../../LkEngineRuntime/Scene/Component/Common/Material.h"

namespace Ui {
	class ApplyMatDlg;
}


class ApplyMatDlg : public QDialog
{
	Q_OBJECT

public:
	explicit ApplyMatDlg(QWidget *parent = nullptr);
	~ApplyMatDlg();

	void setAllComponet(const std::vector<std::string>& uuids);
	void setCurrentMat(const LkEngine::Material& mat) { m_currentMat = mat; }
public slots:
	void showComponentAxis(QString uuid);
	void confirmMat();
private:
	Ui::ApplyMatDlg *ui;
	LkEngine::Material m_currentMat;
	QString m_currentUuid;
};




