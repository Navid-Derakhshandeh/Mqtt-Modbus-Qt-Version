#include <QObject>

class Worker : public QObject {
    Q_OBJECT
public slots:
    void doWork();  // Your background task
signals:
    void finished();
};
