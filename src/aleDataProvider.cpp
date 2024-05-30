// Begin aleDataProvider.cpp

#include "aleDataProvider.h"

AleDataProvider::AleDataProvider(QObject *parent): QObject(parent){
    initialInitPhaseOfData();
    initialDataProviderTimer();
}

void AleDataProvider::initialInitPhaseOfData(){
    QRandomGenerator::system()->generate();
    m_initPhase     = new QVector<double>(m_channelsCount, 0);

    for (int chIdx = 0; chIdx < m_channelsCount; ++chIdx){
        double phase  = 2*M_PI*QRandomGenerator::system()->generateDouble();
        (*m_initPhase)[chIdx] = phase;
    }
}

void AleDataProvider::initialDataProviderTimer(){
    m_timer = new QTimer();
    m_timer->setInterval(1000.0/m_srcRate);
    QObject::connect(m_timer, &QTimer::timeout, this, &AleDataProvider::aleDataProduce);
}

void AleDataProvider::aleDataProduce(){
    QVector<double> rawData(m_channelsCount, 0);

    // Loop over all channels
    for (int chIdx = 0; chIdx < m_channelsCount; ++chIdx){

        double noise  = m_noiseAmpl*(QRandomGenerator::system()->generateDouble() - 0.5);
        double signal = m_dataAmpl*std::sin(2*M_PI*m_dataFreq * (1.0/m_srcRate)*m_pointIndex + (*m_initPhase)[chIdx]);
        rawData[chIdx] = signal + noise;

        // qDebug() << "[*] Point index:" << m_pointIndex << "; Channel №" << chIdx << "; Value" << rawData[chIdx];
        // Increase current point index
        if (chIdx == m_channelsCount - 1){
            m_pointIndex++;
            if ( m_pointIndex > m_srcRate*m_pltTime - 1) {
                m_pointIndex = 0;
            }
        }
    }
    emit aleDataReady(rawData);
}

bool AleDataProvider::isActive(){
    return m_timer->isActive();
}

void AleDataProvider::start(){
    m_timer->start();
}

void AleDataProvider::stop(){
    m_timer->stop();
}
// End aleDataProvider.cpp
