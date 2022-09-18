#include "LkEngineEditor.h"
#include <QtWidgets/QApplication>

#include "../LkEngineRuntime/Core/base/Utility.h"

int main(int argc, char *argv[])
{
	LOG_INFO("engine start");
	LOG_DEBUG("engine start");



	LOG_WARN("engine start");

	LOG_ERROR("engine start");



    if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

	

	LkEngine::LkEngineEditor edt;
	edt.show();

    return app.exec();
}
