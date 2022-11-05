#pragma once

#include <QDialog>
#include "../../LkEngineRuntime/Core/Event/CameraChangedManager.h"


namespace Ui {
	class CameraForm;
}



class CameraForm : public QDialog, public LkEngine::CameraMoveEvent, public LkEngine::CameraFrustumChangedEvent
{
	Q_OBJECT

public:
	explicit CameraForm(QWidget *parent = nullptr);
	~CameraForm();
	virtual void onCameraMove() override;
	virtual void onCameraFrustumChanged() override;

public slots:
	void setWireFrame(bool b);
	void setCameraTransform();
	void setCameraFrustum();
	void setCameraMoveSpeed();
private:
	Ui::CameraForm *ui;
};




