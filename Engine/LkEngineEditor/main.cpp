#include "LkEngineEditor.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);


	LkEngine::LkEngineEditor edt;
	edt.show();

    return app.exec();
}
