#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include "second_dialog.h"
#include <QLabel>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(int* dataArray, QWidget *parent = nullptr);
    ~MainWindow();
    void setReceivedDataArray(int* dataArray);

private slots:
    void on_przycisk_wykresy_clicked();
    void on_przycisk_polacz_clicked();
    void languageSelection(int id);

private:
    Ui::MainWindow *ui;
    Second_Dialog *sec_dial;
    int* receivedDataArray;
    QPixmap scaledImage;
    void changeEvent(QEvent *event) override;
};

#endif // MAINWINDOW_H
