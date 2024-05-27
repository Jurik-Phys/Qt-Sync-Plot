// Begin procData.h
#ifndef PROCDATA_H
#define PROCDATA_H 1

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <numeric>

class ProcData : public QObject {

    Q_OBJECT

    public:
        ProcData(QObject *parent = nullptr);

    public slots:
        void recieveRawData(QVector<double>);

    signals:
        void snapCollectedRawDataDone(QVector<QVector<double>>);
        void averageProcessingDataDone(QVector<double>);
        void updateDecartPlotData(QVector<QVector<double>>);

    private:
        // Raw data storage for plot one point on graph
        QVector<QVector<double>> m_onePointPlotRawData;

        QTimer m_procDataTimer;
        void snapCollectedRawData();

        // Collect recievd raw data
        void collectRawData(QVector<double>);
        void updDecPlotData(QVector<double>);

        // Count of eeg channels
        int          m_channelsCount = 20;
        // Plot signal frequency (Hz)
        int          m_pltRate = 10;

        // Average processing data for plot one point of graph
        void averageProcessingData(QVector<QVector<double>>);

        // Animate debug output
        int m_snapAnimate = 0;

        // Plot time (Time for draw all plot field)
        int          m_pltTime = 15;

        // Constant & variable for decart data plot
        int m_decartPointIdx = 0;
        int m_decartMaxPointIdx = m_pltTime*m_pltRate;
        QVector<QVector<double>> m_decartPlotData;
};
#endif
// End procData.h
