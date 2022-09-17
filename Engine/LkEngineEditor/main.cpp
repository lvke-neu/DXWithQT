#include "LkEngineEditor.h"
#include <QtWidgets/QApplication>
#include "../LkEngineRuntime/Core/core.h"

int main(int argc, char *argv[])
{
	A aa;
	aa.test();

    if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
	LkEngineEditor w;
    w.show();
    return a.exec();
}
