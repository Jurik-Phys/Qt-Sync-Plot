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

// LSL
#include <lsl_cpp.h>

class StreamItem {

public:
    StreamItem(std::string stream_name, std::string stream_type, std::string source_id,
        std::string hostname, bool required)
        : name(stream_name), type(stream_type), id(source_id), host(hostname), checked(required)
        {}

    QString listName() { return QString::fromStdString(name + " (" + host + ")"); }
    std::string name;
    std::string type;
    std::string id;
    std::string host;
    bool checked;
};

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
        std::vector<lsl::stream_info> refreshStreams();

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

        QList<StreamItem> knownStreams;
        QSet<QString> missingStreams;
};


#endif
// End qRootWindow.h
