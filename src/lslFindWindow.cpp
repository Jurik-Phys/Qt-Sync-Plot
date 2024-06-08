// Begin lslFindWindow.cpp

#include "lslFindWindow.h"

QLSLFindWindow::QLSLFindWindow(QWidget *parent) : QWidget(parent, Qt::Window | Qt::WindowStaysOnTopHint) {
    lslSourceList = new QListView(this);
    lslSourceList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    selectButton  = new QPushButton("Select", this);
    cancelButton  = new QPushButton("Cancel", this);

    model = new QStringListModel(this);
    sources = new QStringList();
    model->setStringList(*sources);
    lslSourceList->setModel(model);

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->addWidget(lslSourceList);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(selectButton);
    hLayout->addWidget(cancelButton);

    vLayout->addLayout(hLayout);

    QObject::connect(selectButton, &QPushButton::clicked, this, &QLSLFindWindow::selectClicked);
    QObject::connect(cancelButton, &QPushButton::clicked, this, &QLSLFindWindow::cancelClicked);
    QObject::connect(lslSourceList->selectionModel(), &QItemSelectionModel::selectionChanged, this, &QLSLFindWindow::selectionChanged);
}

QLSLFindWindow::~QLSLFindWindow(){
}

void QLSLFindWindow::selectClicked(){
    // Set "true" flag for selected steam
    for (LSLStreamItem &s : *lslStreamList){
        if (s.listName() == selectedString){
            s.selected = true;
        }
        else {
            s.selected = false;
        }
    }

    this->hide();
    emit lslSourceSelected();
}

void QLSLFindWindow::drawLSLStreamsList(QList<LSLStreamItem>& streamList){
    selectButton->setEnabled(false);
    lslStreamList = &streamList;
    sources->clear();

    QModelIndex index;
    int selectIndex = -1;
    for (LSLStreamItem &s : streamList){
        sources->push_back(s.listName());

        selectIndex++;
        if (s.selected) {
            index = model->index(selectIndex);
            selectButton->setEnabled(true);
        }
    }
    model->setStringList(*sources);

    // Set select state for stream that was previously selected
    lslSourceList->selectionModel()->select(index, QItemSelectionModel::Select);
    lslSourceList->selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
}

void QLSLFindWindow::cancelClicked(){
    this->hide();
}

void QLSLFindWindow::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected){
    QModelIndexList indexes = selected.indexes();
    if (!indexes.isEmpty()) {
        selectedString = model->data(indexes.first(), Qt::DisplayRole).toString();
        selectButton->setEnabled(true);
    } else {
        selectedString.clear();
    }
}

// End lslFindWindos.cpp
