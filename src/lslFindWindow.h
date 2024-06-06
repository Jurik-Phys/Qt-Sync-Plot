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

class QLSLFindWindow : public QWidget
{
    Q_OBJECT

    public:
        QLSLFindWindow(QWidget *parent=nullptr);
        ~QLSLFindWindow();

    signals:
        void lslSourceSelected();

    private slots:
        void selectClicked();
        void cancelClicked();

    private:
        QListView        *lslSourceList;
        QPushButton      *selectButton;
        QPushButton      *cancelButton;
        QStringListModel *model;
};

#endif
// End lslFindWindow.h
