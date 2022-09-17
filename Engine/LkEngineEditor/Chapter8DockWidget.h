#pragma once 

#include "ChapterDockWidgetInterface.h"
#include <Qlabel>
#include <QPushButton>
#include <QLineEdit>

class Chapter8DockWidget : public IChapterDockWidget
{

public:
	Chapter8DockWidget() = default;
	Chapter8DockWidget(void** parameters);
	virtual ~Chapter8DockWidget();

	/*override IScen*/
	virtual void init() override;
	/*override CameraMoveEvent*/
	virtual void onCameraMove(const std::string& msg) override;
	/*override PickEvent*/
	virtual void onPickGameObject(GameObject& go) override;
	virtual void onMouseLocateGo(const std::string& msg) override;

	void connectSignalAndSlots();
	void disConnectSignalAndSlots();
	void showTransform();
	void showTexture();
	void showShader();
public slots:
	void changeTransform();
	void changeTexture();
	void changeShader();
private:
	QLabel* m_labelCamProperty{ nullptr };

	QLabel* m_labelPickedGoProperty{ nullptr };

	QLabel* m_labelScale{ nullptr };
	QLineEdit* m_lineEditScaleX;
	QLineEdit* m_lineEditScaleY;
	QLineEdit* m_lineEditScaleZ;

	QLabel* m_labelRotation{ nullptr };
	QLineEdit* m_lineEditRotationX;
	QLineEdit* m_lineEditRotationY;
	QLineEdit* m_lineEditRotationZ;

	QLabel* m_labelPosition{ nullptr };
	QLineEdit* m_lineEditPositionX;
	QLineEdit* m_lineEditPositionY;
	QLineEdit* m_lineEditPositionZ;

	QLabel* m_labelTexture{ nullptr };
	QLineEdit* m_lineEditTexture;

	QLabel* m_labelShader{ nullptr };
	QLineEdit* m_lineEditVsShader{ nullptr };
	QLineEdit* m_lineEditPsShader{ nullptr };

	
private:
	GameObject* m_pickedGameObject{ nullptr };
};