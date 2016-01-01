/****************************************************************
 * timer.h
 * GrblHoming - zapmaker fork on github
 *
 * 15 Nov 2012
 * GPL License (see LICENSE file)
 * Software is provided AS-IS
 ****************************************************************/

#ifndef TIMER_H
#define TIMER_H

#include <QTime>
#include <QObject>

class Timer : public QObject
{
    Q_OBJECT

public:
    explicit Timer(QObject *parent = 0);

signals:
    void setRuntime(QString timestr);

public slots:
    void resetTimer(bool timeIt);

protected:
    void timerEvent(QTimerEvent *event);

private:
    QTime timer;
    bool timing;
};

#endif // TIMER_H
