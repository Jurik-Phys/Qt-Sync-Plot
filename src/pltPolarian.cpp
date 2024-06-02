// Begin polarian.cpp

#include "pltPolarian.h"

PltPolarian::PltPolarian(QWidget *parent): QWidget(parent) {
    // QFrame needs to draw border around plot
    QFrame      *pltFrame       = new QFrame(parent);
    QVBoxLayout *pltFrameLayout = new QVBoxLayout;

    pltFrameLayout->addWidget(pltFrame);

    pltFrame->setFrameShape(QFrame::StyledPanel);
    pltFrame->setFrameShadow(QFrame::Raised);
    // pltFrame->setStyleSheet("background-color: purple;");

    polarPlot = new QCustomPlot(pltFrame);
    QVBoxLayout *polarPlotLayout = new QVBoxLayout;
    polarPlotLayout->setContentsMargins(0, 0, 0, 0);
    polarPlotLayout->addWidget(polarPlot);
    pltFrame->setLayout(polarPlotLayout);

    polarPlot->plotLayout()->clear();
    QCPPolarAxisAngular *angularAxis = new QCPPolarAxisAngular(polarPlot);
    polarPlot->plotLayout()->addElement(0, 0, angularAxis);

    polarPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    angularAxis->setRangeDrag(false);
    // Counterclock-wise increase path
    angularAxis->setRangeReversed(true);
    // Set "Zero" angel axis to horizontal;
    angularAxis->setAngle(0);

    angularAxis->setTickLabelMode(QCPPolarAxisAngular::lmUpright);

    angularAxis->radialAxis()->setTickLabelMode(QCPPolarAxisRadial::lmUpright);
    angularAxis->radialAxis()->setTickLabelRotation(0);
    angularAxis->radialAxis()->setAngle(0);

    QSharedPointer<QCPAxisCustomTickerFixed> ticker(new QCPAxisCustomTickerFixed);
    ticker->setTickStep(m_tickStep);
    angularAxis->setTicker(ticker);
    angularAxis->setRange(-180, 180);

    angularAxis->grid()->setAngularPen(QPen(QColor(200, 200, 200), 0, Qt::SolidLine));
    angularAxis->grid()->setSubGridType(QCPPolarGrid::gtAll);

    // QCPPolarGraph *g1 = new QCPPolarGraph(angularAxis, angularAxis->radialAxis());
    m_g2 = new QCPPolarGraph(angularAxis, angularAxis->radialAxis());
    m_g2->setPen(QPen(QColor(255, 150, 20)));
    m_g2->setBrush(QColor(255, 150, 20, 50));
    // g1->setScatterStyle(QCPScatterStyle::ssDisc);
    for (int i=0; i<100; ++i)
    {
      // g1->addData(i/100.0*360.0, qSin(i/100.0*M_PI*8)*8+1);
      m_g2->addData(i/100.0*360.0, qSin(i/100.0*M_PI*6));
    }
    angularAxis->setRange(0, 360);
    angularAxis->radialAxis()->setRange(-4, 2);

    this->setLayout(pltFrameLayout);
}

PltPolarian::~PltPolarian(){
}

void PltPolarian::replot(QVector<double> channelsData){

    QVector<double> keys;
    QVector<double> vals;
    for (int i = 0; i <= 360.0/m_tickStep; i++){
        keys.push_back(static_cast<double>(1.0*i*m_tickStep));
    }

    vals = channelsData.mid(0, 360.0/m_tickStep);
    vals.push_back(channelsData[0]);

    m_g2->setData(keys, vals, true);
    polarPlot->replot();
}

QCPAxisCustomTickerFixed::QCPAxisCustomTickerFixed(){
}

QCPAxisCustomTickerFixed::~QCPAxisCustomTickerFixed(){
}

void QCPAxisCustomTickerFixed::generate(const QCPRange &range,
                                const QLocale &locale,
                                QChar formatChar,
                                int precision,
                               QVector<double> &ticks,
                               QVector<double> *subTicks,
                               QVector<QString> *tickLabels) {

    QCPAxisTickerFixed::generate(range, locale, formatChar, precision, ticks, subTicks, tickLabels);

    for (int i = 0; i < tickLabels->size(); i++) {
        switch (i){
            case 0:
                (*tickLabels)[i] = "T4";
                break;
            case 1:
                (*tickLabels)[i] = "F8";
                break;
            case 2:
                (*tickLabels)[i] = "Fp2";
                break;
            case 3:
                (*tickLabels)[i] = "Fp1";
                break;
            case 4:
                (*tickLabels)[i] = "F7";
                break;
            case 5:
                (*tickLabels)[i] = "T3";
                break;
            case 6:
                (*tickLabels)[i] = "T5";
                break;
            case 7:
                (*tickLabels)[i] = "O1";
                break;
            case 8:
                (*tickLabels)[i] = "O2";
                break;
            case 9:
                (*tickLabels)[i] = "T6";
                break;
        }
    }
}

// End polarian.cpp
