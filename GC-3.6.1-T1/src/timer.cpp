/****************************************************************
 * timer.cpp
 * GrblHoming - zapmaker fork on github
 *
 * 15 Nov 2012
 * GPL License (see LICENSE file)
 * Software is provided AS-IS
 ****************************************************************/
#include "timer.h"
Timer::Timer(QObject *parent) :
    QObject(parent), timing(false)
{
    startTimer(500);
}

void Timer::resetTimer(bool timeIt)
{
    timing = timeIt;
    if (timeIt)
        timer.start();
}

void Timer::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    if (timing)
    {
        int secs = timer.elapsed() / 1000;
        int mins = (secs / 60) % 60;
        int hours = (secs / 3600);
        secs = secs % 60;
        emit setRuntime(QString("%1:%2:%3").arg(hours, 2, 10, QLatin1Char('0')).arg(mins, 2, 10, QLatin1Char('0')).arg(secs, 2, 10, QLatin1Char('0')));
    }
}
