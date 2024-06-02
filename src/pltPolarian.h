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
        QCustomPlot   *polarPlot;
        QCPPolarGraph *m_g2;
        // Set count of angular axis to 10 (every 36 angels)
        int         m_tickStep = 36;
};

class QCPAxisCustomTickerFixed : public QCPAxisTickerFixed {
public:
    QCPAxisCustomTickerFixed();
    ~QCPAxisCustomTickerFixed();
    virtual void generate(const QCPRange &range,
                    const QLocale &locale,
                    QChar formatChar,
                    int precision,
                    QVector< double > &ticks,
                    QVector< double > *subTicks,
                    QVector< QString > *tickLabels) override;
};


#endif
// End polarian.h
