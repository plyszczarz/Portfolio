#ifndef SECOND_DIALOG_H
#define SECOND_DIALOG_H

#include <QDialog>
//#include "mainwindow.h"
#include "qcustomplot.h"
#include "ui_second_dialog.h"

class MainWindow;

namespace Ui {
class Second_Dialog;
}

class Second_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Second_Dialog(MainWindow *main_window, QWidget *parent = nullptr);
    ~Second_Dialog();

private slots:
    void on_pushButton_clicked();
    void on_backButton_clicked();

public slots:
    void updateGraph();

protected:
    void showEvent(QShowEvent* event) override;

private:
    Ui::Second_Dialog *ui;
    MainWindow *main_window;
    QCustomPlot* wodaCustomPlot;
    QCustomPlot* przeplywCustomPlot;
    QCustomPlot* wilgoscCustomPlot;
    QCustomPlot* temperaturaCustomPlot;
    void changeEvent(QEvent *event) override;
    QTimer* timer;
    int time;
};

#endif // SECOND_DIALOG_H
