// Begin fakeData.cpp

#include "fakeData.h"

FakeData::FakeData(QObject *parent): QObject(parent){
    QRandomGenerator::system()->generate();
    m_initPhase     = new QVector<double>(m_channelsCount, 0);

    for (int chIdx = 0; chIdx < m_channelsCount; ++chIdx){
        double phase  = 2*M_PI*QRandomGenerator::system()->generateDouble();
        (*m_initPhase)[chIdx] = phase;
    }

}

void FakeData::genRawData(){
    QVector<double> rawData(m_channelsCount, 0);

    // Loop over all channels
    for (int chIdx = 0; chIdx < m_channelsCount; ++chIdx){

        double noise  = m_noiseAmpl*QRandomGenerator::system()->generateDouble() - m_noiseAmpl*0.5;
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
    emit genRawDataDone(rawData);
}
// End fakeData.cpp
