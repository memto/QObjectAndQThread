#include <QCoreApplication>

#include <QTimer>
#include "extentqthread.h"

long baseMSecsSinceEpoch;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    baseMSecsSinceEpoch = QDateTime::currentMSecsSinceEpoch();

    qDebug() << QDateTime::currentMSecsSinceEpoch() - baseMSecsSinceEpoch << "Main thread 1" << QThread::currentThreadId();

    // === test1
    ExtentQThread extQThread1("extQThread1 created from main thread", 10000);

    ExtentQObject extQObject10("extQObject10 created from main thread then moved to extQThread1");
    extQObject10.moveToThread(&extQThread1);

    ExtentQObject extQObject11("extQObject11 created from main thread");

    extQThread1.start();

    // 1.0 to test signal of extQObject10 which is moved to extQThread1
    // and signal of extQObject11 which is not moved
    long timeout = 5000;
    QTimer::singleShot(timeout, [&extQThread1, &timeout]() {
        qDebug() << "\n==" << QDateTime::currentMSecsSinceEpoch() - baseMSecsSinceEpoch << "timeout" << timeout
                 << "\n>> To test signal of extQObject10 which is moved to extQThread1 and signal of extQObject11 which is not moved"
                 << "\n>> extQThread1.isRunning()" << extQThread1.isRunning();
    });
    QTimer::singleShot(timeout, &extQObject10, &ExtentQObject::onExtentQObjectFirstSlot);
    QTimer::singleShot(timeout, &extQObject11, &ExtentQObject::onExtentQObjectFirstSlot);

#if 0
    // 1.1 to test signal of extQThread1 which emit signal to an ExtentQObject created from it before extQThread1::quit
    timeout = 2000;
    QTimer::singleShot(timeout, [&extQThread1, &timeout]() {
        qDebug() << "\n==" << QDateTime::currentMSecsSinceEpoch() - baseMSecsSinceEpoch << "timeout" << timeout
                 << "\n>> To test signal of extQThread1 which emit signal to an ExtentQObject created from it BEFORE extQThread1::quit"
                 << "\n>> extQThread1.isRunning()" << extQThread1.isRunning();
    });
    QTimer::singleShot(timeout, &extQThread1, &ExtentQThread::onExtentQThreadFirstSlot);

    // 1.2 to call extQThread1::quit
    timeout = 3000;
    QTimer::singleShot(timeout, [&extQThread1, &timeout]() {
        qDebug() << "\n==" << QDateTime::currentMSecsSinceEpoch() - baseMSecsSinceEpoch << "timeout" << timeout
                 << "\n>> to call extQThread1::quit"
                 << "\n>> extQThread1.isRunning()" << extQThread1.isRunning();
    });
    QTimer::singleShot(timeout, &extQThread1, &ExtentQThread::quit);

    // 1.3 to test signal of extQThread1 which emit signal to an ExtentQObject created from it
    // after extQThread1::quit
    timeout = 4000;
    QTimer::singleShot(timeout, [&extQThread1, &timeout]() {
        qDebug() << "\n==" << QDateTime::currentMSecsSinceEpoch() - baseMSecsSinceEpoch << "timeout" << timeout
                 << "\n>> To test signal of extQThread1 which emit signal to an ExtentQObject created from it AFTER extQThread1::quit"
                 << "\n>> extQThread1.isRunning()" << extQThread1.isRunning();
    });
    QTimer::singleShot(timeout, &extQThread1, &ExtentQThread::onExtentQThreadFirstSlot);

    // 1.0 to test signal of extQObject10 which is moved to extQThread1 after extQThread1::quit
    timeout = 5000;
    QTimer::singleShot(timeout, [&extQThread1, &timeout]() {
        qDebug() << "\n==" << QDateTime::currentMSecsSinceEpoch() - baseMSecsSinceEpoch << "timeout" << timeout
                 << "\n>> To test signal of extQObject10 which is moved to extQThread1 AFTER extQThread1::quit"
                 << "\n>> extQThread1.isRunning()" << extQThread1.isRunning();
    });
    QTimer::singleShot(timeout, &extQObject10, &ExtentQObject::onExtentQObjectFirstSlot);
#endif

    qDebug() << QDateTime::currentMSecsSinceEpoch() - baseMSecsSinceEpoch << "Main thread 2" << QThread::currentThreadId();

    return a.exec();
}
