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

        // Plot channels map
        // - - - - - - - - - - -
        // | 3 (FP1) | 2 (FP2) |
        // - - - - - - - - - - -
        // | 4 (F7)  | 1 (F8)  |
        // - - - - - - - - - - -
        // | 5 (T3)  | 0 (T4)  |
        // - - - - - - - - - - -
        // | 6 (T5)  | 9 (T6)  |
        // - - - - - - - - - - -
        // | 7 (O1)  | 8  (O2) |
        // - - - - - - - - - - -

        // Plot draw steps
        //  from A to J
        // | LFT | RGT |
        // -------------
        // |  A  |  F  |
        // - - - - - - -
        // |  B  |  G  |
        // - - - - - - -
        // |  C  |  H  |
        // - - - - - - -
        // |  D  |  I  |
        // - - - - - - -
        // |  E  |  J  |
        // - - - - - - -

        QVector<int> m_leftChIdxMap = {3, 4, 5, 6, 7};
        QVector<int> m_rightChIdxMap = {2, 1, 0, 9, 8};

        QVector<QString> m_leftChNameMap = {"FP1", "F7", "T3", "T5", "O1"};
        QVector<QString> m_rightChNameMap = {"FP2", "F8", "T4", "T6", "O2"};

        void syncYAxisRange(bool);
};

#endif
// End file pltCartesian.h

