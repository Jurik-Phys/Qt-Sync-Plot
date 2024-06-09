// Begin lslDataProvider.cpp

#include <QDebug>
#include "lslDataProvider.h"

LslDataProvider::LslDataProvider(QObject *parent) : QObject(parent){

}

LslDataProvider::~LslDataProvider(){
}

void LslDataProvider::setActiveStream(QList<LSLStreamItem>& streamList){

    const std::vector<lsl::stream_info> resolvedStreams = lsl::resolve_streams(1.0);

    for (const lsl::stream_info &s : resolvedStreams) {
        for (const LSLStreamItem &p : streamList) {
            if (s.name() == p.name && s.type() == p.type && s.source_id() == p.id && p.selected == true ){
                m_stream = s;
            };
        }
    }

    // Output information about selected stream
    // https://labstreaminglayer.readthedocs.io/projects/liblsl/ref/streaminfo.html#_CPPv4N3lsl11stream_infoE
    qDebug() << "[*] Stream info [*]";
    qDebug() << "    > name:  " << QString::fromStdString(m_stream.name());
    qDebug() << "    > type:  " << QString::fromStdString(m_stream.type());
    qDebug() << "    > count: " << m_stream.channel_count();
    qDebug() << "    > srate: " << m_stream.nominal_srate();
    qDebug() << "    > format:" << m_stream.channel_format();

    lsl::stream_inlet inlet(m_stream);

    // Get detail infromation from inlet
    lsl::stream_info info = inlet.info();
    // Out all info in XML
    // std::cout << info.as_xml() << std::endl;

    // Get channel labels
    lsl::xml_element ch = info.desc().child("channels").child("channel");
    for (int k = 0; k < m_stream.channel_count(); k++) {
        qDebug() << "      > channel" << k << "label is" << ch.child_value("label");
 		ch = ch.next_sibling();
 	}

    // Close information inlet
    inlet.close_stream();
}

bool LslDataProvider::checkStream(){
    const std::vector<lsl::stream_info> resolvedStreams = lsl::resolve_streams(1.0);

    bool okStream = false;
    for (const lsl::stream_info &s : resolvedStreams) {
        if (s.name() == m_stream.name() && s.type() == m_stream.type() && m_stream.source_id() == m_stream.source_id()){
            okStream = true;
            break;
        };
    }
    return okStream;
}

QString LslDataProvider::getStreamName(){
    return QString::fromStdString(m_stream.name() + " (" + m_stream.hostname() + ")");
}

void LslDataProvider::start(){
    qDebug() << "[*] lslDataProvider::start";
    m_active = true;
}

void LslDataProvider::stop(){
    qDebug() << "[*] lslDataProvider::stop";
    m_active = false;
}

bool LslDataProvider::isActive(){
   return m_active;
}

// void threadRun(){

// }
// End lslDataProvider.cpp
