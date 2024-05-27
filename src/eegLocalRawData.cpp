// Begin eegLocalRawData.cpp

#include "eegLocalRawData.h"
#include <QDebug>

// <Channel>
unsigned int Channel::getId(){
    return m_id;
}

QString Channel::getName(){
    return m_name;
}

double Channel::getValue(){
    return m_value;
}

void Channel::setId(unsigned int id){
    m_id = id;
}

void Channel::setName(QString name){
    m_name = name;
}

void Channel::setValue(double value){
    m_value = value;
}

// <LocalRawData>
LocalRawData::LocalRawData(){
    for (int i = 0; i < channelCount; i++){
        Channel tmpChannel;
        tmpChannel.setId(i);
        tmpChannel.setValue(0);
        switch(i){
            case 0:
                tmpChannel.setName("FP1");
                break;
            case 1:
                tmpChannel.setName("FP2");
                break;
            case 2:
                tmpChannel.setName("F3");
                break;
            case 3:
                tmpChannel.setName("F4");
                break;
            case 4:
                tmpChannel.setName("C3");
                break;
            case 5:
                tmpChannel.setName("C4");
                break;
            case 6:
                tmpChannel.setName("P3");
                break;
            case 7:
                tmpChannel.setName("P4");
                break;
            case 8:
                tmpChannel.setName("O1");
                break;
            case 9:
                tmpChannel.setName("O2");
                break;
            case 10:
                tmpChannel.setName("F7");
                break;
            case 11:
                tmpChannel.setName("F8");
                break;
            case 12:
                tmpChannel.setName("T3");
                break;
            case 13:
                tmpChannel.setName("T4");
                break;
            case 14:
                tmpChannel.setName("T5");
                break;
            case 15:
                tmpChannel.setName("T6");
                break;
            case 16:
                tmpChannel.setName("FZ");
                break;
            case 17:
                tmpChannel.setName("CZ");
                break;
            case 18:
                tmpChannel.setName("PZ");
                break;
            case 19:
                tmpChannel.setName("E1");
                break;
        }
        m_eegChannels.push_back(tmpChannel);
    }
}

Channel& LocalRawData::operator[](unsigned int index) {
    return m_eegChannels[index];
}

int LocalRawData::getChannels() const {
    return m_eegChannels.size();
}

void LocalRawData::updateValue(unsigned int id, double value){
    m_eegChannels[id].setValue(value);
    emit valueChanged(id);
}

// // <ArrayRawData>
// int ArrayRawData::getTickCount() {
//     return m_arrayTickCount;
// }
//
// void ArrayRawData::push(LocalRawData data){
//     if (m_arrayRawData.size() < m_arrayTickCount){
//         m_arrayRawData.push_back(data);
//     }
// }


// End eegLocalRawData.cpp
