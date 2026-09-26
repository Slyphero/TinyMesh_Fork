#include "qte.h"
#include <QtWidgets/qapplication.h>

int main(int argc, char *argv[])
{
    // COMPATIBILITE WAYLAND NVIDIA
    setenv("QT_QPA_PLATFORM", "xcb", 1);
    setenv("__GLX_VENDOR_LIBRARY_NAME", "nvidia", 1);

	QApplication app(argc, argv);

	MainWindow mainWin;
	mainWin.showMaximized();

	return app.exec();
}
