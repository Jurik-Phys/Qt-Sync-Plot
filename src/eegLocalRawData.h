// Begin eegLocalRawData.h
#ifndef LOCALRAWDATA_H
#define LOCALRAWDATA_H 1

#include <QVector>
#include <QObject>

// Class for one channel data
class Channel {
    public:
        unsigned int getId();
        QString      getName();
        double       getValue();

        void setId(unsigned int);
        void setName(QString);
        void setValue(double);

    private:
        unsigned int m_id;
        QString      m_name;
        double       m_value;
};

// Class for actual data into local app format
class LocalRawData : public QObject {

    Q_OBJECT

    public:
        LocalRawData();
        // ~LocalRawData();

        Channel& operator[](unsigned int);
        int getChannels() const;
        void updateValue(unsigned int, double);

    signals:
        void valueChanged(unsigned int);

    private:
        QVector<Channel> m_eegChannels;
        unsigned int channelCount = 20;
};


// class ArrayRawData {
//
//     public:
//         void push(LocalRawData);
//         int  getTickCount();
//
//     private:
//         QVector<LocalRawData> m_arrayRawData;
//         unsigned int m_arrayTickCount = 7500;
// };

#endif
// End eegLocalRawData.h
