#include "mainwindow.h"
#include "serial_port_manager.h"
#include "second_dialog.h"
#include <QApplication>

int receivedDataArray[4] = {0};

void onDataReceived(int values[4]){
    // Update the receivedDataArray with the received values
    for (int i = 0; i < 4; i++) {
        receivedDataArray[i] = values[i];
    }

    // Display the received data
    qDebug() << "Data in main:" << receivedDataArray[0] << receivedDataArray[1] << receivedDataArray[2] << receivedDataArray[3];
    qDebug() << "dataArray[0] in main:" << receivedDataArray[1];
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w(receivedDataArray);
    w.show();

    SerialPortReader reader;
    //QObject::connect(&reader, &SerialPortReader::dataReceived, onDataReceived);

    QObject::connect(&reader, &SerialPortReader::dataReceived, [&](int values[4]) {
        // Update the receivedDataArray with the received values
        for (int i = 0; i < 4; i++) {
            receivedDataArray[i] = values[i];
        }

        // Display the received data
        qDebug() << "Data in main:" << receivedDataArray[0] << receivedDataArray[1] << receivedDataArray[2] << receivedDataArray[3];

        // Set the received data array in the MainWindow instance
        w.setReceivedDataArray(receivedDataArray);
    });

    return app.exec();
}
