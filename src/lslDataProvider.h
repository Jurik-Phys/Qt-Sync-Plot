// Begin lslDataProvider.h
#ifndef LSLDATAPROVIDER_H
#define LSLDATAPROVIDER_H 1

#include <QObject>
#include <QCoreApplication>
#include <QThread>
#include <iostream>
#include <lsl_cpp.h>
#include "lslStreamItem.h"

class LslDataProvider : public QObject
{
    Q_OBJECT

    public:
        LslDataProvider(QObject *parent = nullptr);
        ~LslDataProvider();
        void setActiveStream(QList<LSLStreamItem>&);
        QString getStreamName();
        bool checkStream();
        bool isActive();

    public slots:
        void start();
        void stop();

    signals:
        void lslDataReady(QVector<double>);

    private slots:
        void threadRun();

    private:
        lsl::stream_info m_stream;
        bool m_active;

        // Count of eeg channels
        int          m_channelsCount = 20;

        // Thread for data manipulation
        // QThread *m_thread;
};

#endif
// End lslDataProvider.h
