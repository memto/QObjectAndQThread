#ifndef EXTENTQOBJECT_H
#define EXTENTQOBJECT_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QDateTime>

class ExtentQObject : public QObject
{
    Q_OBJECT

    QString name;

public:
    ExtentQObject(QString name_);

public Q_SLOTS:
    void onExtentQObjectFirstSlot();
};

#endif // EXTENTQOBJECT_H
