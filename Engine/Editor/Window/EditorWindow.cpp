#include "EditorWindow.h"
#include "RenderWindow.h"
#include "Runtime/Core/Utility/Utility.h"
#include "Runtime/Core/Log/LogManager.h"
#include "Runtime/Core/Engine/Engine.h"

namespace Twinkle
{
	EditorWindow::EditorWindow(QWidget* parent) :
		QMainWindow(parent),
		ui(new Ui::EditorWindow)
	{
		ui->setupUi(this);
		m_renderWindow = new RenderWindow(this);
		setCentralWidget(m_renderWindow);

		startTimer(1000);
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

		QString fps = (" FPS:" + std::to_string(Singleton<Engine>::GetInstance().getFps())).c_str();
		setWindowTitle("Twinkle-v0.002" + fps);
	}
}