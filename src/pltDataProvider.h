// Begin pltDataProvider.h
// Prepare raw data for plot
#ifndef PLTDATAPROVIDER_H
#define PLTDATAPROVIDER_H 1

#include <QApplication>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <numeric>
#include <iostream>

class PltDataProvider : public QObject {

    Q_OBJECT

    public:
        PltDataProvider(QObject *parent = nullptr);
        void toggle();

    public slots:
        void collectData(QVector<double>);
        void pltPointProduce();
        void pltCartesianProduce(QVector<double>);

    signals:
        void pltPointReady(QVector<double>);
        void pltCartesianReady(QVector<QVector<double>>);

    private:
        // Processing data event timer
        QTimer m_plotTimer;
        // Raw data storage for plot one point on graph
        QVector<QVector<double>> *m_pltRawDataBufferA;
        QVector<QVector<double>> *m_pltRawDataBufferB;
        // Active write buffer flag
        bool pushToPltRawDataBufferA = true;

        // N raw data converts to one value
        // for each EEG data channel (default 20);
        double processingChannelData(QVector<double>);

        // Count of eeg channels
        int          m_channelsCount = 20;
        // Plot signal frequency (Hz)
        int          m_pltRate = 10;

        // Average processing data for plot one point of graph
        void averageProcessingData(QVector<QVector<double>>);

        // Animate debug output
        int m_pltPointProduceAnimate = 0;

        // Plot time (Time for draw all plot field)
        int          m_pltTime = 15;

        // Cartesian plotting
        int m_cartesianPointIdx = 0;
        int m_cartesianMaxPointIdx = m_pltTime*m_pltRate;
        // Storage for plot data
        QVector<QVector<double>> *m_cartesianPlotData;
};
#endif
// End pltDataProvider.h
