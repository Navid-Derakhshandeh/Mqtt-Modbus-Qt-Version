#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QModbusDataUnit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,modbusDevice(new QModbusTcpClient(this))
{
    ui->setupUi(this);
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::connectToServer);
    connect(ui->dial, &QDial::valueChanged, this, &MainWindow::updateDialValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::connectToServer() {
    modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, "localhost");
    modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, 1502);
    modbusDevice->setTimeout(1000);
    modbusDevice->setNumberOfRetries(3);

    if (!modbusDevice->connectDevice()) {
        qDebug() << "Failed to connect to Modbus server";
    } else {
        qDebug() << "Connected to Modbus server";
    }
}

void MainWindow::updateDialValue(int value) {
    ui->lineEdit->setText(QString::number(value));

    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, 8, 1);
    writeUnit.setValue(0, value);

    modbusDevice->sendWriteRequest(writeUnit, 1); // Slave ID = 1
}
