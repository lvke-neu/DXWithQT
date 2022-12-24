//#include <QtWidgets/QApplication>
//#include "window/EditorWindow.h"
//
//
//int main(int argc, char *argv[])
//{
//    if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
//        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//
//    QApplication app(argc, argv);
//
//    Twinkle::EditorWindow editorWindow;
//    editorWindow.show();
//
//    return app.exec();
//}


#include "Window/NativeWindow.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevInstance,
	_In_ LPSTR cmdLine, _In_ int showCmd)
{

	AllocConsole();

	Twinkle::NativeWindow nativeWindow(hInstance);

	return Twinkle::NativeWindow::Run();
}
