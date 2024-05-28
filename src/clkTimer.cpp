// Begin clkTimer.cpp

#include "clkTimer.h"

ClkTimer::ClkTimer(QObject *parent): QObject (parent) {
    m_timer.setInterval(2); // 2 ms => 500 Hz
    QObject::connect(&m_timer, &QTimer::timeout, this, &ClkTimer::clkEventGen);
}

void ClkTimer::start(){
    m_timer.start();
}

void ClkTimer::clkEventGen(){
    emit clkEvent();
}

// End clkTimer.cpp