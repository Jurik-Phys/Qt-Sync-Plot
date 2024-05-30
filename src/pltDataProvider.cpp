// Begin pltDataProvider.cpp

#include "pltDataProvider.h"

PltDataProvider::PltDataProvider(QObject *parent) : QObject(parent){
    m_pltRawDataBufferA = new QVector<QVector<double>>(m_channelsCount);
    m_pltRawDataBufferB = new QVector<QVector<double>>(m_channelsCount);
    m_cartesianPlotData = new QVector<QVector<double>>(m_channelsCount);

    m_plotTimer.setInterval(1000/m_pltRate); // 100 ms => FPS = 10 Hz
    QObject::connect(&m_plotTimer, &QTimer::timeout, this, &PltDataProvider::pltPointProduce);

    // Cartesian plot collect data
    QObject::connect(this, &PltDataProvider::pltPointReady, this, &PltDataProvider::pltCartesianProduce);
}

// Fill m_pltRawDataBufferA or m_pltRawDataBufferB
// with input raw data depending on pushToPltRawDataBufferA status
void PltDataProvider::collectData(QVector<double> rawData){

    if (pushToPltRawDataBufferA){
        // qDebug() << "[*] Buffer \"A\"";
        for (int chIdx = 0; chIdx < m_channelsCount; chIdx++){
            (*m_pltRawDataBufferA)[chIdx].push_back(rawData[chIdx]);
        }
    }
    else {
        // qDebug() << "[*] Buffer \"B\"";
        for (int chIdx = 0; chIdx < m_channelsCount; chIdx++){
            (*m_pltRawDataBufferB)[chIdx].push_back(rawData[chIdx]);
        }
    }
}

void PltDataProvider::pltPointProduce(){
    QVector<QVector<double>> *pltRawDataBuffer = nullptr;
    QVector<double> pltPointData;

    if (pushToPltRawDataBufferA){
        pltRawDataBuffer = m_pltRawDataBufferA;
        pushToPltRawDataBufferA = false;
    }
    else {
        pltRawDataBuffer = m_pltRawDataBufferB;
        pushToPltRawDataBufferA = true;
    }

    int chIdxMax = (*pltRawDataBuffer).size();
    for (int chIdx = 0; chIdx < chIdxMax; chIdx++){
        qDebug() << "[*] Channel" << chIdx << "Raw data count: " << (*pltRawDataBuffer)[chIdx].size();
        pltPointData.push_back(processingChannelData((*pltRawDataBuffer)[chIdx]));
        // Reset index data after channel processed
        (*pltRawDataBuffer)[chIdx].resize(0);
    }

    // >> >> Debug pltPointProduce
    switch (m_pltPointProduceAnimate){
        case 0: qDebug() << "[/] Point produce [/]";
                m_pltPointProduceAnimate++;
                break;
        case 1:
                qDebug() << "[-] Point produce [-]";
                m_pltPointProduceAnimate++;
                break;
        case 2: qDebug() << "[\\] Point produce [\\]";
                m_pltPointProduceAnimate = 0;
                break;
    }
    emit pltPointReady(pltPointData);
}

double PltDataProvider::processingChannelData(QVector<double> channelRawData){
    double sum = std::accumulate(channelRawData.begin(), channelRawData.end(), 0.0);
    return sum / channelRawData.size();
}

void PltDataProvider::pltCartesianProduce(QVector<double> data){
    if ( m_cartesianPointIdx < m_cartesianMaxPointIdx ){
        for (int chIdx = 0; chIdx < data.size(); chIdx++){
            (*m_cartesianPlotData)[chIdx].push_back(data[chIdx]);
        }
        m_cartesianPointIdx++;

        emit pltCartesianReady(*m_cartesianPlotData);
    }
    else {
        for (int chIdx = 0; chIdx < data.size(); chIdx++){
            (*m_cartesianPlotData)[chIdx].removeFirst();
            (*m_cartesianPlotData)[chIdx].push_back(data[chIdx]);
        }
        emit pltCartesianReady(*m_cartesianPlotData);
    }
}

void PltDataProvider::toggle(){
    if (!m_plotTimer.isActive()){
        m_plotTimer.start();
    }
    else {
        m_plotTimer.stop();
    }
}

// End pltDataProvider.cpp
