// Begin lslFindWindow.cpp

#include "lslFindWindow.h"

QLSLFindWindow::QLSLFindWindow(QWidget *parent) : QWidget(parent) {
    lslSourceList = new QListView(this);
    selectButton  = new QPushButton("Select", this);
    cancelButton  = new QPushButton("Cancel", this);

    model = new QStringListModel(this);
    QStringList sources = {"First", "Second", "Thread"};
    model->setStringList(sources);
    lslSourceList->setModel(model);

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->addWidget(lslSourceList);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(selectButton);
    hLayout->addWidget(cancelButton);

    vLayout->addLayout(hLayout);

    QObject::connect(selectButton, &QPushButton::clicked, this, &QLSLFindWindow::selectClicked);
    QObject::connect(cancelButton, &QPushButton::clicked, this, &QLSLFindWindow::cancelClicked);
}

QLSLFindWindow::~QLSLFindWindow(){
}

void QLSLFindWindow::selectClicked(){
    emit lslSourceSelected();
    qDebug() << "[*] <Select> button clicked";
    this->hide();
}

void QLSLFindWindow::cancelClicked(){
    qDebug() << "[*] <Cancel> button clicked";
    this->hide();
}

// End lslFindWindos.cpp
