#ifndef EXTENTQTHREAD_H
#define EXTENTQTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QDateTime>

#include "extentqobject.h"

class ExtentQThread : public QThread
{
    Q_OBJECT

    QString name = "";
    long loopTimeoutMsec = -1;

public:
    ExtentQThread(QString name_, long loopTimeoutMsec_);

protected:
    void run();

Q_SIGNALS:
    void runFirstSlot();

public Q_SLOTS:
    void onExtentQThreadFirstSlot();
};

#endif // EXTENTQTHREAD_H
