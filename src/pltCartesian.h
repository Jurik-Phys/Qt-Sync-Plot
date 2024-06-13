// Begin file pltCartesian.h
#ifndef PLTCARTESIAN_H
#define PLTCARTESIAN_H 1

#include <QApplication>
#include <QTimer>
#include <QWidget>

#include "qcustomplot/qcustomplot.h"

class PltCartesian : public QWidget
{
    Q_OBJECT

    public:
        PltCartesian(QWidget *parent=0);
        ~PltCartesian();

    public slots:
        void replot(QVector<QVector<double>>);

    private:
        bool eventFilter(QObject *obj, QEvent *event);

        QList<QFrame*> leftFrameList;
        QList<QFrame*> rightFrameList;

        QList<QCustomPlot*> m_leftPlotList;
        QList<QCustomPlot*> m_rightPlotList;

        void syncYAxisRange(bool);
};

#endif
// End file pltCartesian.h

