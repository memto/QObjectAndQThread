#include "extentqobject.h"

extern long baseMSecsSinceEpoch;

ExtentQObject::ExtentQObject(QString name_)
{
    name = name_;
    qDebug() << QDateTime::currentMSecsSinceEpoch() - baseMSecsSinceEpoch << Q_FUNC_INFO
             << "instance" << name
             << "created on thread" << QThread::currentThreadId();
}

void ExtentQObject::onExtentQObjectFirstSlot() {
    qDebug() << QDateTime::currentMSecsSinceEpoch() - baseMSecsSinceEpoch << Q_FUNC_INFO
             << "instance" << name
             << "run on thread" << QThread::currentThreadId();
}
