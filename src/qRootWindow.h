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

#include "pltCartesian.h"
#include "aleDataProvider.h"
#include "pltDataProvider.h"

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
        PltCartesian  *pltCartesian;

    private:
        void initialSrcSelector();
        void initialLiveStreamFinderBtn();
        void initialStatusLine();
        void initialPltSelector();
        void initialRunPlotting();
        void initialAllPlot();

        AleDataProvider *aleDataProvider;
        PltDataProvider *pltDataProvider;
};


#endif
// End qRootWindow.h
