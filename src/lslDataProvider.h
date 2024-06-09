// Begin lslDataProvider.h
#ifndef LSLDATAPROVIDER_H
#define LSLDATAPROVIDER_H 1

#include <QObject>
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
        // void lslDataProduce();
        void start();
        void stop();

signals:
        void lslDataReady(QVector<double>);
        void finished(bool);

//    private slots:
//        void threadRun();

    private:
        lsl::stream_info m_stream;
        bool m_active;
};

#endif
// End lslDataProvider.h
