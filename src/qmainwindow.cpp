// Begin qmainwindow.cpp

#include <QDebug>
#include "qmainwindow.h"
#include "eegLocalRawData.h"

#include <QLabel>

QAppMainWindow::QAppMainWindow(QWidget *parent) : QWidget(parent){
    LocalRawData localRawData;
    QObject::connect(&localRawData, &LocalRawData::valueChanged, this, &QAppMainWindow::CatchValueChanged);

    // Fill local raw data
    for (int i = 0; i < localRawData.getChannels(); i++){
        localRawData[i].setName("new "+localRawData[i].getName());
        localRawData.updateValue(i, 2.2*(i+i));
    }

    // Output localRawData
    for (int i = 0; i < localRawData.getChannels(); i++){
        qDebug() << "[*] id =" << localRawData[i].getId() << "; Name: " << localRawData[i].getName() << " Value: " << localRawData[i].getValue();
    }

    // Generate full data //
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
        x[i] = i/50.0 - 1; // x goes from -1 to 1
        y[i] = x[i]*x[i]; // let's plot a quadratic function
    }

    this->resize(960,1040);
    this->setWindowTitle("Qt sync plot");

    QHBoxLayout *hLayout = new QHBoxLayout;
    QVBoxLayout *vLayoutLeft  = new QVBoxLayout;
    QVBoxLayout *vLayoutRight = new QVBoxLayout;

    hLayout->addLayout(vLayoutLeft);
    hLayout->addSpacing(25);
    hLayout->addLayout(vLayoutRight);

    QFrame *tempFrame;
    QWidget *tempPlotWidget;
    QCustomPlot *tempPlot;
    QHBoxLayout *tempHLayout;
    // Prepare cut data //

    for (int i = 0; i < 10; i++){
        float sizeDivisor = 2.5;
        float frameWidth  = this->size().width() / sizeDivisor;
        float frameHeight = this->size().height() / sizeDivisor;
        tempFrame = new QFrame();
        tempFrame->setFrameShape(QFrame::StyledPanel);
        tempFrame->resize(frameWidth, frameHeight);
        tempPlot = new QCustomPlot(tempFrame);

        tempFrame->installEventFilter(this);

        // Begin plot //
        // create graph and assign data to it:
        tempPlot->addGraph();
        tempPlot->graph(0)->setData(x, y);
        // give the axes some labels:
        tempPlot->xAxis->setLabel("x");
        tempPlot->yAxis->setLabel("y");
        // set axes ranges, so we see all data:
        tempPlot->xAxis->setRange(-1, 1);
        tempPlot->yAxis->setRange(0, 1);
        // End plot //

        if ( i < 5){
            leftFrameList.push_back(tempFrame);
            m_leftPlotList.push_back(tempPlot);
            vLayoutLeft->addWidget(tempFrame);
        }
        else {
            rightFrameList.push_back(tempFrame);
            vLayoutRight->addWidget(tempFrame);
            m_rightPlotList.push_back(tempPlot);
        }
    }
    this->setLayout(hLayout);
}

QAppMainWindow::~QAppMainWindow(){
}

bool QAppMainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::Resize) {
        // Resize left plots
        for (int i = 0; i < m_leftPlotList.size(); i++){
            // "-4" for draw frame border
            m_leftPlotList[i]->setGeometry(2, 2, leftFrameList[i]->size().width() - 4, leftFrameList[i]->size().height() - 4);
        }

        // Resize right plots
        for (int i = 0; i < m_rightPlotList.size(); i++){
            // "-4" for draw frame border
            m_rightPlotList[i]->setGeometry(2, 2, rightFrameList[i]->size().width() - 4, rightFrameList[i]->size().height() - 4);
        }
        return true;
    }
    return false;
}

void QAppMainWindow::CatchValueChanged(unsigned int id){
    qDebug() << "[*] Changed channel №" << id;
}

void QAppMainWindow::updateDecartPlot(QVector<QVector<double>> plotData){
    qDebug() << "[*] Update decart plot!";
    size_t plotCount = m_leftPlotList.size() + m_rightPlotList.size();

    QVector<double> x(plotData[0].size(), 0);
    QVector<double> y(plotData[0].size(), 0);
    for (int chIdx = 0; chIdx < plotCount; chIdx++){
        if ( chIdx < plotCount/2 ){
            // Left plots
            for (int i = 0; i < plotData[chIdx].size(); i++){
                x[i] = i;
                y[i] = plotData[chIdx][i];
            }
            m_leftPlotList[chIdx]->xAxis->setRange(0, 175);
            m_leftPlotList[chIdx]->yAxis->setRange(-1.5, 1.5);
            m_leftPlotList[chIdx]->graph(0)->setData(x, y);
            m_leftPlotList[chIdx]->replot();
        }
        else {
            // Right plots
            for (int i = 0; i < plotData[chIdx].size(); i++){
                x[i] = i;
                y[i] = plotData[chIdx][i];
            }
            m_rightPlotList[chIdx - plotCount/2]->xAxis->setRange(0, 175);
            m_rightPlotList[chIdx - plotCount/2]->yAxis->setRange(-1.5, 1.5);
            m_rightPlotList[chIdx - plotCount/2]->graph(0)->setData(x, y);
            m_rightPlotList[chIdx - plotCount/2]->replot();
        }
    }

}
// End qmainwindow.cpp
