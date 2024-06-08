// Begin qRootWindow.h
#ifndef QROOTWINDOW_H
#define QROOTWINDOW_H 1

#include <memory> // std::unique_ptr
#include <QApplication>
#include <QWidget>
#include <QDebug>
#include <QLayout>
#include <QComboBox>
#include <QLabel>
#include <QStatusBar>
#include <QPushButton>

#include "pltCartesian.h"
#include "pltPolarian.h"
#include "aleDataProvider.h"
#include "pltDataProvider.h"
#include "lslFindWindow.h"
#include "lslStreamItem.h"

// LSL
#include <lsl_cpp.h>

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
        QVBoxLayout   *graphLayout;
        QPushButton   *lslFindBtn;
        QPushButton   *runPlotting;
        QStatusBar    *statusBar;
        PltCartesian  *pltCartesian;
        PltPolarian   *pltPolarian;
        QLSLFindWindow *qLSLFindWindow;

    signals:
        void aleDataProviderStart();
        void aleDataProviderStop();
        void pltDataProviderStart();
        void pltDataProviderStop();

    private slots:
        void resolveStreams();

    private:
        void initialSrcSelector();
        void initialLiveStreamFindBtn();
        void initialLiveStreamFindWin();
        void initialStatusLine();
        void initialPltSelector();
        void initialRunPlotting();
        void initialAllPlot();

        AleDataProvider *aleDataProvider;
        PltDataProvider *pltDataProvider;

        QList<LSLStreamItem> knownStreams;
};


#endif
// End qRootWindow.h
