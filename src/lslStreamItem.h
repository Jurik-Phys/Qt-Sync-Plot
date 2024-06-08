// Begin lslStreamItem.h
#ifndef LSLSTREAMITEM_H
#define LSLSTREAMITEM_H 1

#include <QString>
class LSLStreamItem {

public:
    LSLStreamItem(std::string stream_name, std::string stream_type, std::string source_id,
        std::string hostname, bool required)
        : name(stream_name), type(stream_type), id(source_id), host(hostname), selected(required)
        {}

    QString listName() { return QString::fromStdString(name + " (" + host + ")"); }
    std::string name;
    std::string type;
    std::string id;
    std::string host;
    bool        selected;
};

#endif
// End lslStreamItem.h
