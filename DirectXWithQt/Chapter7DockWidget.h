#pragma once 

#include "ChapterDockWidgetInterface.h"
#include <Qlabel>
#include <QSlider>
#include <QPushButton>

class Chapter7DockWidget : public IChapterDockWidget
{
public:
	Chapter7DockWidget() = default;
	Chapter7DockWidget(void** parameters);
	virtual ~Chapter7DockWidget();

	/*override IScen*/
	virtual void init() override;
	/*override Listening*/
	virtual void onCameraMove(const std::string& msg) override;
private:
	QLabel* m_labelCamProperty{ nullptr };

	QLabel* m_labelFrustumCull{ nullptr };
	QPushButton* m_buttonStartFrustumCull{ nullptr };
	QPushButton* m_buttonCloseFrustumCull{ nullptr };

	QLabel* m_labelChangeFog{ nullptr };
	QPushButton* m_buttonStartFog{ nullptr };
	QPushButton* m_buttonCloseFog{ nullptr };
	QSlider* m_sliderFogRange{ nullptr };
};