#include "extentqthread.h"

extern long baseMSecsSinceEpoch;

ExtentQThread::ExtentQThread(QString name_, long loopTimeoutMsec_)
{
    name = name_;
    loopTimeoutMsec = loopTimeoutMsec_;

    qDebug() << QDateTime::currentMSecsSinceEpoch() - baseMSecsSinceEpoch << Q_FUNC_INFO
             << "instance" << name
             << "loopTimeoutMsec" << loopTimeoutMsec
             << "created on thread" << QThread::currentThreadId();
}

void ExtentQThread::run() {
    qDebug() << QDateTime::currentMSecsSinceEpoch() - baseMSecsSinceEpoch << Q_FUNC_INFO
             << "instance" << name
             << "STARTED on thread" << QThread::currentThreadId();

    ExtentQObject extQObject("extQObject created from (" + name + ")");
    connect(this, &ExtentQThread::runFirstSlot, &extQObject, &ExtentQObject::onExtentQObjectFirstSlot);

    if (loopTimeoutMsec < 0) {
        while(1) {};
    } else {
        QThread::msleep(loopTimeoutMsec);
    }

    qDebug() << QDateTime::currentMSecsSinceEpoch() - baseMSecsSinceEpoch << Q_FUNC_INFO
             << "instance" << name
             << "before exec() on thread" << QThread::currentThreadId();

    exec();

    qDebug() << QDateTime::currentMSecsSinceEpoch() - baseMSecsSinceEpoch << Q_FUNC_INFO
             << "instance" << name
             << "after exec() on thread" << QThread::currentThreadId();

    if (loopTimeoutMsec < 0) {
        while(1) {};
    } else {
        QThread::msleep(loopTimeoutMsec);
    }

    qDebug() << QDateTime::currentMSecsSinceEpoch() - baseMSecsSinceEpoch << Q_FUNC_INFO
             << "instance" << name
             << "STOPPED on thread" << QThread::currentThreadId();
}

void ExtentQThread::onExtentQThreadFirstSlot() {
    qDebug() << QDateTime::currentMSecsSinceEpoch() - baseMSecsSinceEpoch << Q_FUNC_INFO
             << "instance" << name
             << "run on thread" << QThread::currentThreadId();

    Q_EMIT runFirstSlot();
}
