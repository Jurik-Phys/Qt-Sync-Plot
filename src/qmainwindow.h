// Begin file qmainwindow.h
#ifndef QMAINWINDOW_H
#define QMAINWINDOW_H 1

#include <QApplication>
#include <QTimer>
#include <QWidget>

#include "qcustomplot/qcustomplot.h"

class QAppMainWindow : public QWidget
{
    Q_OBJECT

    public:
        QAppMainWindow(QWidget *parent=0);
        ~QAppMainWindow();

    public slots:
        void CatchValueChanged(unsigned int);
        void updateDecartPlot(QVector<QVector<double>>);

    private:
        bool eventFilter(QObject *obj, QEvent *event);

        QList<QFrame*> leftFrameList;
        QList<QFrame*> rightFrameList;

        QList<QCustomPlot*> m_leftPlotList;
        QList<QCustomPlot*> m_rightPlotList;
};

#endif
// End file qmainwindow.h

