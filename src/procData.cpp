// Begin procData.cpp

#include "procData.h"

ProcData::ProcData(QObject *parent) : QObject(parent){
    m_onePointPlotRawData.resize(m_channelsCount);
    m_decartPlotData.resize(m_channelsCount);
    m_procDataTimer.setInterval(1000/m_pltRate); // 100 ms => FPS = 10 Hz
    m_procDataTimer.start();
    // Take snapshot data by timer event
    QObject::connect(&m_procDataTimer, &QTimer::timeout, this, &ProcData::snapCollectedRawData);
    // Snapshot data transformation to one point data for each channel
    QObject::connect(this, &ProcData::snapCollectedRawDataDone, this, &ProcData::averageProcessingData);

    // Decart plot. Update data
    QObject::connect(this, &ProcData::averageProcessingDataDone, this, &ProcData::updDecPlotData);

}

void ProcData::recieveRawData(QVector<double> rawData){
    // qDebug() << "[*] ProcData::recieveRawData. Variable <rawData>:" << rawData;

    // Collect recievd raw data
    collectRawData(rawData);
}


void ProcData::collectRawData(QVector<double> rawData){

    for (int chIdx = 0; chIdx < m_channelsCount; chIdx++){
        m_onePointPlotRawData[chIdx].push_back(rawData[chIdx]);
    }

    // >> Debug all output <m_onePointPlotRawData>
    // for (int chIdx = 0; chIdx < m_channelsCount; chIdx++){
    //     qDebug().nospace() << "[*] Channel №" << chIdx;
    //     for (int rawDataIdx = 0; rawDataIdx < m_onePointPlotRawData[chIdx].size(); rawDataIdx++){
    //         qDebug() << "    > rawDataIdx" << rawDataIdx << "Data:" << m_onePointPlotRawData[chIdx][rawDataIdx];
    //     }
    // }
    // >> Debug only one channel output of <m_onePointPlotRawData>
    //    int chIdx = 0;
    //    qDebug().nospace() << "[*] Channel №" << chIdx;
    //    for (int rawDataIdx = 0; rawDataIdx < m_onePointPlotRawData[chIdx].size(); rawDataIdx++){
    //        qDebug() << "    > rawDataIdx" << rawDataIdx << "Data:" << m_onePointPlotRawData[chIdx][rawDataIdx];
    //    }
    // <<
}

void ProcData::snapCollectedRawData(){
    size_t chIdxMax = m_onePointPlotRawData.size();

    QVector<QVector<double>> snap_onePointPlotRawData;
    snap_onePointPlotRawData.resize(chIdxMax);

    for (int chIdx = 0; chIdx < chIdxMax; chIdx++){
        // Copy data to snapshot variable;
        for (int rawDataIdx = 0; rawDataIdx < m_onePointPlotRawData[chIdx].size(); rawDataIdx++){
            double value = m_onePointPlotRawData[chIdx][rawDataIdx];
            snap_onePointPlotRawData[chIdx].push_back(value);
        }

        // Reset collected data
        m_onePointPlotRawData[chIdx].resize(0);
    }

    // >> >> Debug output snap_onePointPlotRawData
    switch (m_snapAnimate){
        case 0: qDebug() << "[/] Snapshot rawData [/]";
                m_snapAnimate++;
                break;
        case 1:
                qDebug() << "[-] Snapshot rawData [-]";
                m_snapAnimate++;
                break;
        case 2: qDebug() << "[\\] Snapshot rawData [\\]";
                m_snapAnimate = 0;
                break;
    }

    for (int chIdx = 0; chIdx < chIdxMax; chIdx++){
        qDebug().nospace() << "[*] Channel №" << chIdx << "; Raw values count:" << snap_onePointPlotRawData[chIdx].size();
        // for (int rawDataIdx = 0; rawDataIdx < snap_onePointPlotRawData[chIdx].size(); rawDataIdx++){
        //     qDebug() << "    > snap > rawDataIdx" << rawDataIdx << "Data:" << snap_onePointPlotRawData[chIdx][rawDataIdx];
        // }
    }
    // << <<

    // Raise signal with data for plot one point of graph
    emit snapCollectedRawDataDone(snap_onePointPlotRawData);
}

void ProcData::averageProcessingData(QVector<QVector<double>> onePointPlotRawData){
    qDebug().nospace() << "[>] ProcData::averageProcessingData";

    QVector<double> result(onePointPlotRawData.size(), 0);

    for (int chIdx = 0; chIdx < onePointPlotRawData.size(); chIdx++){
        double sum = std::accumulate(onePointPlotRawData[chIdx].begin(), onePointPlotRawData[chIdx].end(), 0.0);
        double avg = sum / onePointPlotRawData[chIdx].size();
        // qDebug() << "[*] Channel:" << chIdx << "; Sum:" << sum << ";Average value:" << avg;
        result[chIdx] = avg;
    }
    emit averageProcessingDataDone(result);
}

void ProcData::updDecPlotData(QVector<double> data){

    if ( m_decartPointIdx < m_decartMaxPointIdx ){
        for (int chIdx = 0; chIdx < data.size(); chIdx++){
            m_decartPlotData[chIdx].push_back(data[chIdx]);
        }
        m_decartPointIdx++;
        emit updateDecartPlotData(m_decartPlotData);
    }
    else {
        for (int chIdx = 0; chIdx < data.size(); chIdx++){
            m_decartPlotData[chIdx].removeFirst();
            m_decartPlotData[chIdx].push_back(data[chIdx]);
        }
        emit updateDecartPlotData(m_decartPlotData);
    }
}

// End procData.cpp
