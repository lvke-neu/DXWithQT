#include "EditorWindow.h"
#include "RenderWindow.h"
#include "Runtime/Core/Log/LogManager.h"
#include "Runtime/Core/Engine/Engine.h"
#include "Runtime/Utility/Utility.h"

namespace Twinkle
{
	EditorWindow::EditorWindow(QWidget* parent) :
		QMainWindow(parent),
		ui(new Ui::EditorWindow)
	{
		ui->setupUi(this);
		setWindowIcon(QIcon(":/logo/TwinkleLogo.jpeg"));
		m_renderWindow = new RenderWindow(this);
		setCentralWidget(m_renderWindow);

		startTimer(0);
		LOG_INFO("Window initialization is complete");
	}

	EditorWindow::~EditorWindow()
	{
		SAFE_DELETE_SETNULL(m_renderWindow);
		SAFE_DELETE_SETNULL(ui);
	}

	void EditorWindow::timerEvent(QTimerEvent* event)
	{
		float a = 1;

		QString fps = (" FPS:" + std::to_string(Singleton<Engine>::GetInstance().GetFps())).c_str();
		setWindowTitle("Twinkle-v0.002 " + fps);
	}
}