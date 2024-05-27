// Begin fakeData.h
#ifndef FAKEDATA_H
#define FAKEDATA_H 1

#include <QVector>
#include <QObject>
#include <QRandomGenerator>
#include <QDebug>
#include <cmath>

class FakeData : public QObject {

    Q_OBJECT

    public:
        FakeData(QObject *parent = nullptr);

    public slots:
        void genRawData();

    signals:
        void genRawDataDone(QVector<double>);

    private:
        // Count of eeg channels
        int          m_channelsCount = 20;
        // Maximum value of clean fake signal
        double       m_dataAmpl      = 1.0;
        // Maximum value of noise of fake signal
        double       m_noiseAmpl     = 0.5;
        // Initial phase for each channel
        QVector<double> *m_initPhase;
        // Generated signal frequency
        double       m_dataFreq      = 0.4;
        // Generated points index
        double m_pointIndex = 0;

        // Fake signal (source) frequency
        int          m_srcRate = 500;
        // Plot time (Time for draw full plot field)
        int          m_pltTime = 15;
};

#endif
// End fakeData.h
