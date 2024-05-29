#include "src/qRootWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QRootWindow rootWindow;
    rootWindow.show();

    return app.exec();
}
