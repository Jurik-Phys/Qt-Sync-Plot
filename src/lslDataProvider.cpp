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
    // https://labstreaminglayer.readthedocs.io/projects/liblsl/ref/streaminfo.html
    qDebug() << "[*] Stream info [*]";
    qDebug() << "    > name:  " << QString::fromStdString(m_stream.name());
    qDebug() << "    > type:  " << QString::fromStdString(m_stream.type());
    qDebug() << "    > count: " << m_stream.channel_count();
    qDebug() << "    > srate: " << m_stream.nominal_srate();
    qDebug() << "    > format:" << m_stream.channel_format();

    lsl::stream_inlet tempInlet(m_stream);

    // Get detail infromation from inlet
    lsl::stream_info info = tempInlet.info();

    // Get channel labels
    lsl::xml_element ch = info.desc().child("channels").child("channel");
    for (int k = 0; k < m_stream.channel_count(); k++) {
        qDebug() << "      > channel" << k << "label is" << ch.child_value("label");
 		ch = ch.next_sibling();
 	}

    // Close information tempInlet
    tempInlet.close_stream();
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

    QThread *m_thread = new QThread(nullptr);
    QObject::connect(m_thread, &QThread::started, this, &LslDataProvider::threadRun);

    this->moveToThread(m_thread);
    m_thread->start();
}

void LslDataProvider::threadRun(){
    qDebug() << "[*] threadRun";
    lsl::stream_inlet inlet(m_stream);
    QVector<double> rawData(m_channelsCount, 0);
    std::vector<double> sample;
    while(m_active){
        inlet.pull_sample(sample);
        QVector<double> rawData(sample.begin(), sample.end());
        emit lslDataReady(rawData);
        QCoreApplication::processEvents();
    }
    inlet.close_stream();

    // No needed destroy objects
    // emit finished();
}

void LslDataProvider::stop(){
    qDebug() << "[>] lslDataProvider thread ID: " << QThread::currentThreadId();
    m_active = false;
}

bool LslDataProvider::isActive(){
   return m_active;
}

// End lslDataProvider.cpp
