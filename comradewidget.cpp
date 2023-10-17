#include "comradewidget.h"
#include "./ui_comradewidget.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>

QSerialPort *port1 = new QSerialPort;
QSerialPort *port2 = new QSerialPort;

comradeWidget::comradeWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::comradeWidget)
{
    ui->setupUi(this);
    QList<QSerialPortInfo> serialPortsInfo = QSerialPortInfo::availablePorts();
    if(serialPortsInfo.size() < 2)
    {
        QMessageBox::critical(this,"Serial insuficiente","é necessário duas ou mais portas");
        exit(1);
    }
    for (qsizetype i = 0; i < serialPortsInfo.size(); ++i)
    {
        this->ui->com1box->addItem(serialPortsInfo.at(i).portName());
        this->ui->com2box->addItem(serialPortsInfo.at(i).portName());
    }
    this->ui->baudBox->addItem("1200");
    this->ui->baudBox->addItem("2400");
    this->ui->baudBox->addItem("4800");
    this->ui->baudBox->addItem("9600");
    this->ui->baudBox->addItem("19200");
    this->ui->baudBox->addItem("38400");
    this->ui->baudBox->addItem("57600");
    this->ui->baudBox->addItem("115200");

}

/*
QSerialPort::Baud1200
QSerialPort::Baud2400
QSerialPort::Baud4800
QSerialPort::Baud9600
QSerialPort::Baud19200
QSerialPort::Baud38400
QSerialPort::Baud57600
QSerialPort::Baud115200
*/

void comradeWidget::readData1()
{
    const QByteArray data = port1->readAll();
    writeData2(data);
}

void comradeWidget::writeData1(const QByteArray &data)
{
    port1->write(data);
}


void comradeWidget::readData2()
{
    const QByteArray data = port2->readAll();
    writeData1(data);
}

void comradeWidget::writeData2(const QByteArray &data)
{
    port2->write(data);
}


comradeWidget::~comradeWidget()
{
    delete ui;
}


void comradeWidget::on_startButton_clicked()
{
    port1->setPortName(this->ui->com1box->currentText());
    port2->setPortName(this->ui->com2box->currentText());
    port1->setStopBits(QSerialPort::OneStop);
    port2->setStopBits(QSerialPort::OneStop);
    port1->setParity(QSerialPort::NoParity);
    port2->setParity(QSerialPort::NoParity);

    port1->setBaudRate(this->ui->baudBox->currentText().toInt());
    port2->setBaudRate(this->ui->baudBox->currentText().toInt());

    port1->open(QSerialPort::ReadWrite);
    port2->open(QSerialPort::ReadWrite);
    connect(port1, &QSerialPort::readyRead, this, &comradeWidget::readData1);
    connect(port2, &QSerialPort::readyRead, this, &comradeWidget::readData2);

}

