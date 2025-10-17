// worker.cpp
#include "worker.h"
#include <QDebug>
#include <QThread>

void Worker::doWork() {
    qDebug() << "Worker is running in thread:" << QThread::currentThread();
    emit finished();
    // Your long-running or socket-related code here
}
