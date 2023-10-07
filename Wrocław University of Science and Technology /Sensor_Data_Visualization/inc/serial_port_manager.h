#ifndef SERIAL_PORT_MANAGER_H
#define SERIAL_PORT_MANAGER_H

#pragma once

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QThread>
#include <QTimer>

extern int receivedDataArray[4];
extern bool polacz_clicked;

class SerialPortManager
{
public:
    SerialPortManager()
    {
        m_serialPort = new QSerialPort();
    }

    void setBaudRate(qint32 baudRate)
    {
        m_serialPort->setBaudRate(baudRate);
    }

    void setReadBufferSize(int size)
    {
        m_serialPort->setReadBufferSize(size);
    }

    bool openPort()
    {
        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            m_serialPort->setPort(info);

            if (m_serialPort->open(QIODevice::ReadOnly))
            {
                qDebug() << "Opened serial port:" << info.portName();
                return true;
            }
        }

        qDebug() << "Failed to open any serial port.";
        return false;
    }

    void closePort()
    {
        if (m_serialPort->isOpen())
        {
            m_serialPort->close();
        }
    }

    QSerialPort* getSerialPort() const
    {
        return m_serialPort;
    }

private:
    QSerialPort* m_serialPort;
};

class SerialPortReader : public QObject
{
    Q_OBJECT
public:

    SerialPortReader(QObject *parent = nullptr) : QObject(parent)
    {
        SerialPortManager portManager;
        portManager.setBaudRate(9600);
        portManager.setReadBufferSize(17);

        if (portManager.openPort())
        {
            m_serialPort = portManager.getSerialPort();

            // Find available serial ports
            foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
                qDebug() << "Found serial port:" << info.portName();
            }

            QTimer *timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(readData()));
            timer->start(100);

            // Connect the readyRead signal to the readData slot
            connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortReader::readData);
        }
        else
        {
            qDebug() << "No available serial ports found.";
        }
    }

signals:
    void dataReceived(int values[4]);

private slots:

    void readData()
    {
        int values[4];
        if(polacz_clicked){

        QString stringData;
        static QByteArray receivedData; // static variable to store previously received data

        //QThread::msleep(100);

        receivedData += m_serialPort->readAll(); // append newly received data

        // Check if any error occurred while reading data
        if (m_serialPort->error() != QSerialPort::NoError) {
            qDebug() << "Error while reading data:" << m_serialPort->errorString();
            return;
        }

        // Process the received data
        int index;
        while ((index = receivedData.indexOf('*')) >= 0) {
            QByteArray data = receivedData.left(index + 3); // extract data including checksum
            receivedData = receivedData.mid(index + 3); // remove processed data from receivedData

            // Parse the data and extract the four integers and checksum
            QList<QByteArray> parts = data.split(',');
            if (parts.size() != 5 || !parts.last().startsWith('*')) {
                qDebug() << "Invalid data format received";
                continue;
            }

            bool ok;
            //int values[4];
            values[0] = parts[0].toInt(&ok);
            if (!ok || values[0] > 100) {
                //qDebug() << "Invalid integer format or value in received dataaaa";
                continue;
            }
            for (int i = 1; i < 3; i++) {
                values[i] = parts[i].toInt(&ok);
                stringData = QString::fromUtf8(parts[3]);
                values[3] = stringData.toDouble(&ok)*1000;
                if (!ok) {
                    qDebug() << "Invalid integer format in received data";
                    continue;
                }
            }

            QString checksum = parts.last().mid(1); // extract checksum without "*"
            //qDebug() << "Received data:" << values[0] << values[1] << values[2] << values[3] << checksum;

            // Emit the dataReceived signal with the received values
            emit dataReceived(values);
        }
        }
    }

private:
    QSerialPort* m_serialPort;
};

#endif // SERIAL_PORT_MANAGER_H


