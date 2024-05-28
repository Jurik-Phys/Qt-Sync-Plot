// Begin qRootWindow.h
#ifndef QROOTWINDOW_H
#define QROOTWINDOW_H 1

#include <QApplication>
#include <QWidget>
#include <QDebug>
#include <QLayout>
#include <QComboBox>
#include <QLabel>
#include <QStatusBar>
#include <QPushButton>

#include "qmainwindow.h"
#include "clkTimer.h"
#include "fakeData.h"
#include "procData.h"

class QRootWindow : public QWidget
{
    Q_OBJECT

    public:
        QRootWindow(QWidget *parent=0);
        ~QRootWindow();

        // Application settings
        QComboBox     *srcSelector;
        QComboBox     *pltSelector;
        QFrame        *graphCanvas;
        QPushButton   *lslFinderBtn;
        QPushButton   *runPlotting;
        QStatusBar    *statusBar;
        // TODO rename this graph
        QAppMainWindow *appWindow;

    private:
        void initialSrcSelector();
        void initialLiveStreamFinderBtn();
        void initialStatusLine();
        void initialPltSelector();
        void initialRunPlotting();
        void initialAllPlot();

        ClkTimer *clkTimer;
        FakeData *srcData;
        ProcData *prcData;
};


#endif
// End qRootWindow.h
