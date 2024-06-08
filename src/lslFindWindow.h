// Begin lslFindWindow.h
#ifndef LSLFINDWINDOW_H
#define LSLFINDWINDOW_H 1

#include <QDebug>
#include <QWidget>
#include <QListView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStringListModel>
#include "lslStreamItem.h"

class QLSLFindWindow : public QWidget
{
    Q_OBJECT

    public:
        QLSLFindWindow(QWidget *parent=nullptr);
        ~QLSLFindWindow();

        void drawLSLStreamsList(QList<LSLStreamItem>&);

    signals:
        void lslSourceSelected();

    private slots:
        void selectClicked();
        void cancelClicked();
        void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    private:
        QListView        *lslSourceList;
        QPushButton      *selectButton;
        QPushButton      *cancelButton;
        QString          selectedString;
        QStringList      *sources;
        QStringListModel *model;

        QList<LSLStreamItem> *lslStreamList;
};

#endif
// End lslFindWindow.h
