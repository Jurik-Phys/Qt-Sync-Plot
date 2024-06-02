// Begin polarian.h
#ifndef POLARIAN_H
#define POLARIAN_H 1

#include "qcustomplot/qcustomplot.h"

class PltPolarian : public QWidget {
    Q_OBJECT

    public:
        PltPolarian(QWidget *parent=nullptr);
        ~PltPolarian();

    public slots:
        void replot(QVector<double>);

    private:
        QCustomPlot *polarPlot;
        QVBoxLayout *plotLayout;
};


#endif
// End polarian.h
