#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "worker.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
     ui->setupUi(this);
    mosquitto_lib_init();
    mqttClient = mosquitto_new(nullptr, true, this);
    mosquitto_message_callback_set(mqttClient, MainWindow::on_message);

    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::on_connectButton_clicked);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::on_sendButton_clicked);


}

MainWindow::~MainWindow()
{
    mosquitto_disconnect(mqttClient);
    mosquitto_destroy(mqttClient);
    mosquitto_lib_cleanup();
    delete ui;
}


void MainWindow::on_message(struct mosquitto *, void *obj, const mosquitto_message *msg) {
    MainWindow *self = static_cast<MainWindow *>(obj);
    QString payload = QString::fromUtf8(static_cast<char *>(msg->payload), msg->payloadlen);
    self->ui->receivedLabel->setText("Received: " + payload);
}
void MainWindow::on_connectButton_clicked()
{
    int rc = mosquitto_connect(mqttClient, "test.mosquitto.org", 1883, 60);
    if (rc == MOSQ_ERR_SUCCESS) {
        mosquitto_subscribe(mqttClient, nullptr, "cip", 0);
        mosquitto_loop_start(mqttClient);
        ui->statusLabel->setText("Connected and subscribed to 'cip'");
    } else {
        ui->statusLabel->setText("Connection failed");
        qDebug() << "Connection failed:" << mosquitto_strerror(rc);
    }
}
void MainWindow::startWorkerThread() {
    QThread* thread = new QThread;
    Worker* worker = new Worker;

    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &Worker::doWork);
    connect(worker, &Worker::finished, thread, &QThread::quit);  // Optional: if you emit finished
    connect(worker, &Worker::finished, worker, &Worker::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}

void MainWindow::on_sendButton_clicked()
{
    QString message = ui->messageEdit->text();
    QByteArray payload = message.toUtf8();
    mosquitto_publish(mqttClient, nullptr, "cip", payload.size(), payload.data(), 0, false);
    ui->statusLabel->setText("Published: " + message);
}

