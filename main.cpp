// #include <QApplication>
// #include <QScreen>
// #include "lib/lib.h"
#include "src/qmainwindow.h"
#include "src/clkTimer.h"
#include "src/fakeData.h"
#include "src/procData.h"
#include "src/qRootWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    // QAppMainWindow appWindow;
    // appWindow.show();

    QRootWindow rootWindow;
    rootWindow.show();

//    ClkTimer clkTimer;
//    FakeData srcData;
//    ProcData prcData;

    // Visualise Timer event
    // QObject::connect(&clkTimer, &ClkTimer::clkEvent, []() { qDebug() << "[>] Timer clock up"; });
    // Generate fake data for each point
//    QObject::connect(&clkTimer, &ClkTimer::clkEvent, &srcData, &FakeData::genRawData);
    // Processing input data
//    QObject::connect(&srcData, &FakeData::genRawDataDone, &prcData, &ProcData::recieveRawData);
    // Processing data done & update plot
//    QObject::connect(&prcData, &ProcData::updateDecartPlotData, &appWindow, &QAppMainWindow::updateDecartPlot);

//    clkTimer.start();
    return app.exec();
}
