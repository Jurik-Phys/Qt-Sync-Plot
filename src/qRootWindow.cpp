// Begin qRootWindow.cpp

#include "qRootWindow.h"

QRootWindow::QRootWindow(QWidget *parent) : QWidget(parent){
    this->resize(983,1050);
    this->setWindowTitle("Qt sync plot");

    initialSrcSelector();
    initialLiveStreamFinderBtn();
    initialPltSelector();
    initialRunPlotting();
    initialStatusLine();

    // Frame for plot & layout on it for children widget
    graphCanvas = new QFrame;
    graphLayout = new QVBoxLayout(graphCanvas);

    // Set graph canvas style
    graphCanvas->setFrameShape(QFrame::StyledPanel);
    graphCanvas->setFrameShadow(QFrame::Raised);
    // graphCanvas->setStyleSheet("background-color: purple;");

    // Cartesian plot
    // pltCartesian = new PltCartesian();
    // graphLayout->addWidget(pltCartesian);

    // Polar plot
    pltPolarian = new PltPolarian();
    graphLayout->addWidget(pltPolarian);

    initialAllPlot();

    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(srcSelector);
    hLayout->addWidget(lslFinderBtn);
    hLayout->addWidget(pltSelector);
    hLayout->addWidget(runPlotting);

    vLayout->addLayout(hLayout);
    vLayout->addWidget(graphCanvas);
    vLayout->addWidget(statusBar);

    // Apply layout
    this->setLayout(vLayout);

}

QRootWindow::~QRootWindow(){
}

void QRootWindow::initialSrcSelector(){
    srcSelector = new QComboBox();
    srcSelector->addItem("RND generator");
    srcSelector->addItem("LSL source server");
}

void QRootWindow::initialPltSelector(){
    pltSelector = new QComboBox();
    pltSelector->addItem("Cartesian graph");
    pltSelector->addItem("Polar graph");
}

void QRootWindow::initialLiveStreamFinderBtn(){
    lslFinderBtn = new QPushButton("Find LSL");
    lslFinderBtn->setEnabled(false);

    // Enable lslFinderBtn to search LSL Server when lsl source was selected
    connect(srcSelector, &QComboBox::currentIndexChanged, this, [this](int index){
        if (index == 0) {
            lslFinderBtn->setEnabled(false);
        }
        else {
            lslFinderBtn->setEnabled(true);
        }
    });
}

void QRootWindow::initialRunPlotting(){
    runPlotting = new QPushButton("Try to plotting");

    connect(runPlotting, &QPushButton::clicked, this, [this](){
        if (!aleDataProvider->isActive()){
            aleDataProvider->start();
        }
        else {
            aleDataProvider->stop();
        }
        pltDataProvider->toggle();
    });
}

void QRootWindow::initialStatusLine(){
    statusBar = new QStatusBar();
    statusBar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    statusBar->showMessage("Qt-Sync-Plot started...");
    statusBar->setFixedHeight(20);

    // Show actual source
    connect(srcSelector, &QComboBox::currentIndexChanged, this, [this](int index){
        if (index == 0) {
            statusBar->showMessage("Data source from random number generator");
        }
        else {
            statusBar->showMessage("Data source from LSL server. Try to find it!");
        }
    });

    // Show actual plot type
    connect(pltSelector, &QComboBox::currentIndexChanged, this, [this](int index){
        if (index == 0) {
            statusBar->showMessage("Cartesian graph selected for plotting");
        }
        else {
            statusBar->showMessage("Ploar graph selected for plotting");
        }
    });

    // Try to plotting
    connect(runPlotting, &QPushButton::clicked, this, [this](){
        statusBar->showMessage("Try to plotting source data");
    });

    // Try to find LSL Server
    connect(lslFinderBtn, &QPushButton::clicked, this, [this](){
        statusBar->showMessage("Try to find LSL source server");
    });
}

void QRootWindow::initialAllPlot(){
    aleDataProvider = new AleDataProvider;
    pltDataProvider = new PltDataProvider;

    // "AleDataProvider::aleDataReady" is the signal with aleatory /random/ raw data from fake EEG
    // "PltDataProvider::collectData"  is collecting input EEG data from EEG (20 channels by default)
    QObject::connect(aleDataProvider, &AleDataProvider::aleDataReady, pltDataProvider, &PltDataProvider::collectData);

    // QObject::connect(pltDataProvider, &PltDataProvider::pltCartesianReady, pltCartesian, &PltCartesian::replot);
}

// End qRootWindow.cpp
