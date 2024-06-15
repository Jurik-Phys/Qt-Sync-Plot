// Begin pltCartesian.cpp

#include <QDebug>
#include "pltCartesian.h"

#include <QLabel>

PltCartesian::PltCartesian(QWidget *parent) : QWidget(parent){
    this->resize(960,975);
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
        tempFrame->installEventFilter(this);

        tempPlot = new QCustomPlot(tempFrame);
        // Range zoom & range drag for vertical axis
        tempPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
        tempPlot->axisRect()->setRangeDrag(Qt::Vertical);
        tempPlot->axisRect()->setRangeZoom(Qt::Vertical);

        // >> Begin plot >> //
        // Create graph and assign data to it:
        tempPlot->addGraph();
        // Set the axes labels:
        tempPlot->xAxis->setLabel("x");
        tempPlot->yAxis->setLabel("y");
        // Set axes ranges:
        tempPlot->xAxis->setRange(0, 175);
        tempPlot->yAxis->setRange(-1.5, 1.5);
        // << End plot << //

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
    syncYAxisRange(true);
    this->setLayout(hLayout);
}

void PltCartesian::syncYAxisRange(bool isSync){
    if (isSync){
        for (int i = 0; i < m_leftPlotList.size(); i++){
            for ( int j = 0; j < m_rightPlotList.size(); j++){
                // Left => Right
                QObject::connect(m_leftPlotList[i]->yAxis, QOverload<const QCPRange &>::of(&QCPAxis::rangeChanged),
                        [this,j](const QCPRange &newRange) {
                        m_rightPlotList[j]->yAxis->setRange(newRange);
                        m_rightPlotList[j]->replot();
                        });

                // Right => Left
                QObject::connect(m_rightPlotList[j]->yAxis, QOverload<const QCPRange &>::of(&QCPAxis::rangeChanged),
                        [this,i](const QCPRange &newRange) {
                        m_leftPlotList[i]->yAxis->setRange(newRange);
                        m_leftPlotList[i]->replot();
                        });
            }
        }
    }
}

PltCartesian::~PltCartesian(){
}

bool PltCartesian::eventFilter(QObject *obj, QEvent *event) {
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

void PltCartesian::replot(QVector<QVector<double>> plotData){
    //qDebug() << "[*] Cartesian replot now!";

    // Plot channels map
    // - - - - - - - - - - -
    // | 3 (FP1) | 2 (FP2) |
    // - - - - - - - - - - -
    // | 4 (F7)  | 1 (F8)  |
    // - - - - - - - - - - -
    // | 5 (T3)  | 0 (T4)  |
    // - - - - - - - - - - -
    // | 6 (T5)  | 9 (T6)  |
    // - - - - - - - - - - -
    // | 7 (O1)  | 8  (O2) |
    // - - - - - - - - - - -

    // Plot sequence
    // | LFT | RGT |
    // -------------
    // | A.0 | F.5 |
    // - - - - - - -
    // | B.1 | G.6 |
    // - - - - - - -
    // | C.2 | H.7 |
    // - - - - - - -
    // | D.3 | I.8 |
    // - - - - - - -
    // | E.4 | K.9 |
    // - - - - - - -

    QVector<int> leftChIdxMap = {3, 4, 5, 6, 7};
    QVector<int> rightChIdxMap = {2, 1, 0, 9, 8};

    size_t plotCount = m_leftPlotList.size() + m_rightPlotList.size();

    QVector<double> x(plotData[0].size(), 0);
    QVector<double> y(plotData[0].size(), 0);
    for (int pltIdx = 0; pltIdx < plotCount; pltIdx++){
        if ( pltIdx < plotCount/2 ){
            // Left plots
            int chIdx = leftChIdxMap[pltIdx];
            for (int i = 0; i < plotData[chIdx].size(); i++){
                x[i] = i;
                y[i] = plotData[chIdx][i];
            }
            m_leftPlotList[pltIdx]->graph(0)->setData(x, y);
            m_leftPlotList[pltIdx]->replot();
        }
        else {
            // Right plots
            int chIdx = rightChIdxMap[pltIdx - plotCount/2];
            for (int i = 0; i < plotData[chIdx].size(); i++){
                x[i] = i;
                y[i] = plotData[chIdx][i];
            }
            m_rightPlotList[pltIdx - plotCount/2]->graph(0)->setData(x, y);
            m_rightPlotList[pltIdx - plotCount/2]->replot();
        }
    }
}
// End pltCartesian.cpp
