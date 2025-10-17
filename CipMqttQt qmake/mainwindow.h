#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mosquitto.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectButton_clicked();
    void startWorkerThread();
    void on_sendButton_clicked();

private:
    struct mosquitto *mqttClient;
    static void on_message(struct mosquitto *, void *, const mosquitto_message *);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
