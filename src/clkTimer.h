// Begin clkTimer.h
#ifndef CLKTIMER_H
#define CLKTIMER_H 1

#include <QObject>
#include <QTimer>

class ClkTimer : public QObject {

    Q_OBJECT

    public:
        explicit ClkTimer(QObject *parent = nullptr);

        void start();

    signals:
        void clkEvent();

    private:
        QTimer m_timer;

    private slots:
        void clkEventGen();
};
#endif
// End clkTimer.h
