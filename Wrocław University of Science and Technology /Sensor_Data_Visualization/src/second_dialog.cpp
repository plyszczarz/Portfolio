#include "second_dialog.h"
#include "serial_port_manager.h"
#include "ui_second_dialog.h"
#include "mainwindow.h"
#include <QTimer>

extern bool polacz_clicked;
extern int language;

QVector<QPointF> poziom_wody_dataPoints;
QVector<QPointF> przeplyw_dataPoints;
QVector<QPointF> wilgoc_dataPoints;
QVector<QPointF> temperatura_dataPoints;

Second_Dialog::Second_Dialog(MainWindow *main_window, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Second_Dialog),
    main_window(main_window)
{
    ui->setupUi(this);

    // Assign the QCustomPlot widget to the member variable
    wodaCustomPlot = ui->woda_wykres;
    przeplywCustomPlot = ui->przeplyw_wykres;
    wilgoscCustomPlot = ui->wilgoc_wykres;
    temperaturaCustomPlot = ui->temperatura_wykres;

    // Set up the axes
    if(!language){
        wodaCustomPlot->xAxis->setLabel("Czas [s]");
        wodaCustomPlot->yAxis->setLabel("wysokość wody [ml]");

        przeplywCustomPlot->xAxis->setLabel("Czas [s]");
        przeplywCustomPlot->yAxis->setLabel("przepływ [ml/s]");

        wilgoscCustomPlot->xAxis->setLabel("Czas [s]");
        wilgoscCustomPlot->yAxis->setLabel("wilgoć [% RH]");

        temperaturaCustomPlot->xAxis->setLabel("Czas [s]");
        temperaturaCustomPlot->yAxis->setLabel("temperatura [℃]");
    }
    else{
        wodaCustomPlot->xAxis->setLabel("Time [s]");
        wodaCustomPlot->yAxis->setLabel("Water level [ml]");

        przeplywCustomPlot->xAxis->setLabel("Time [s]");
        przeplywCustomPlot->yAxis->setLabel("Flow [ml/s]");

        wilgoscCustomPlot->xAxis->setLabel("Time [s]");
        wilgoscCustomPlot->yAxis->setLabel("Humidity [% RH]");

        temperaturaCustomPlot->xAxis->setLabel("Time [s]");
        temperaturaCustomPlot->yAxis->setLabel("Temperature [℃]");
    }


    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Second_Dialog::updateGraph);

    // Set the timer interval (e.g., update every 1 second)
    int intervalMs = 1000;
    timer->setInterval(intervalMs);

    // Start the timer
    timer->start();

    connect(ui->pushButton_powrot, &QPushButton::clicked, this, &Second_Dialog::on_pushButton_clicked);
}

Second_Dialog::~Second_Dialog()
{
    delete ui;

    // Stop the timer
    timer->stop();

    // Release resources
    delete timer;
}

void Second_Dialog::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
        return;
    }
    QDialog::changeEvent(event);
}

void Second_Dialog::updateGraph()
{
    static int time = 0;

    double wodaData = receivedDataArray[2]* 20;
    double przeplywData = receivedDataArray[3];
    double wilgocData = receivedDataArray[1];
    double temperaturaData = receivedDataArray[0];

    // Set up the axes
    if(!language){
        wodaCustomPlot->xAxis->setLabel("Czas [s]");
        wodaCustomPlot->yAxis->setLabel("wysokość wody [ml]");

        przeplywCustomPlot->xAxis->setLabel("Czas [s]");
        przeplywCustomPlot->yAxis->setLabel("przepływ [ml/s]");

        wilgoscCustomPlot->xAxis->setLabel("Czas [s]");
        wilgoscCustomPlot->yAxis->setLabel("wilgoć [% RH]");

        temperaturaCustomPlot->xAxis->setLabel("Czas [s]");
        temperaturaCustomPlot->yAxis->setLabel("temperatura [℃]");
    }
    else{
        wodaCustomPlot->xAxis->setLabel("Time [s]");
        wodaCustomPlot->yAxis->setLabel("Water level [ml]");

        przeplywCustomPlot->xAxis->setLabel("Time [s]");
        przeplywCustomPlot->yAxis->setLabel("Flow [ml/s]");

        wilgoscCustomPlot->xAxis->setLabel("Time [s]");
        wilgoscCustomPlot->yAxis->setLabel("Humidity [% RH]");

        temperaturaCustomPlot->xAxis->setLabel("Time [s]");
        temperaturaCustomPlot->yAxis->setLabel("Temperature [℃]");
    }

    // Store the data point in the QVector
    if(polacz_clicked){
        if(wodaData < 500 && wodaData > 0)
            poziom_wody_dataPoints.append(QPointF(static_cast<double>(time), wodaData));
        else
            poziom_wody_dataPoints.append(QPointF(static_cast<double>(time), 500));

        przeplyw_dataPoints.append(QPointF(static_cast<double>(time), przeplywData));
        wilgoc_dataPoints.append(QPointF(static_cast<double>(time), wilgocData));
        temperatura_dataPoints.append(QPointF(static_cast<double>(time), temperaturaData));
    }

    // Clear the previous graph
    wodaCustomPlot->clearGraphs();
    przeplywCustomPlot->clearGraphs();
    wilgoscCustomPlot->clearGraphs();
    temperaturaCustomPlot->clearGraphs();

    // Create a new graph
    QCPGraph* woda_graph = wodaCustomPlot->addGraph();
    QCPGraph* przeplyw_graph = przeplywCustomPlot->addGraph();
    QCPGraph* wilgoc_graph = wilgoscCustomPlot->addGraph();
    QCPGraph* temperatura_graph = temperaturaCustomPlot->addGraph();

    // Set the data from the QVector to the graph
    for (const QPointF& point : poziom_wody_dataPoints) {
        woda_graph->addData(point.x(), point.y());
    }

    for (const QPointF& point : przeplyw_dataPoints) {
        przeplyw_graph->addData(point.x(), point.y());
    }

    for (const QPointF& point : wilgoc_dataPoints) {
        wilgoc_graph->addData(point.x(), point.y());
    }

    for (const QPointF& point : temperatura_dataPoints) {
        temperatura_graph->addData(point.x(), point.y());
    }

    // Increment the time
    ++time;

    // Get the current x-axis range
    QCPRange woda_xRange = wodaCustomPlot->xAxis->range();
    QCPRange przeplyw_xRange = wodaCustomPlot->xAxis->range();
    QCPRange wilgoc_xRange = wodaCustomPlot->xAxis->range();
    QCPRange temepratura_xRange = temperaturaCustomPlot->xAxis->range();
    woda_graph->setLineStyle(QCPGraph::lsLine);
    woda_graph->setPen(QPen(Qt::blue));

    przeplyw_graph->setLineStyle(QCPGraph::lsNone);
    przeplyw_graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::red), QBrush(Qt::red), 8));

    wilgoc_graph->setLineStyle(QCPGraph::lsLine);
    wilgoc_graph->setPen(QPen(QColor("#A52A2A")));

    // Clear the previous graph
    temperaturaCustomPlot->clearPlottables();

    // Create a new graph
    QCPBars* temperatura_bars = new QCPBars(temperaturaCustomPlot->xAxis, temperaturaCustomPlot->yAxis);

    // Set the data from the QVector to the graph
    QVector<double> temperaturaKeys;
    QVector<double> temperaturaValues;
    for (const QPointF& point : temperatura_dataPoints) {
        temperaturaKeys.append(point.x());
        temperaturaValues.append(point.y());
    }
    temperatura_bars->setData(temperaturaKeys, temperaturaValues);

    // Set the bar color and width
    temperatura_bars->setPen(Qt::NoPen);
    temperatura_bars->setBrush(QColor("#FFA500"));
    temperatura_bars->setWidth(0.8);


    // Check if the current time is greater than the x-axis range
    if (static_cast<double>(time) > woda_xRange.upper)
    {
        // Expand the x-axis range by adding a fixed increment
        double increment = 10.0; // Adjust the increment as needed
        wodaCustomPlot->xAxis->setRange(woda_xRange.lower, woda_xRange.upper + increment);
        przeplywCustomPlot->xAxis->setRange(przeplyw_xRange.lower, przeplyw_xRange.upper + increment);
        wilgoscCustomPlot->xAxis->setRange(wilgoc_xRange.lower, wilgoc_xRange.upper + increment);
        temperaturaCustomPlot->xAxis->setRange(temepratura_xRange.lower, temepratura_xRange.upper + increment);
    }
    // Rescale the y-axis to fit the data
    //wodaCustomPlot->rescaleAxes(true);

    wodaCustomPlot->yAxis->setRange(0, 500);
    przeplywCustomPlot->yAxis->setRange(0, 1500);
    wilgoscCustomPlot->yAxis->setRange(0, 90);
    temperaturaCustomPlot->yAxis->setRange(0, 50);

    wodaCustomPlot->setBackground(QBrush(QColor(170, 170, 255)));
    przeplywCustomPlot->setBackground(QBrush(QColor(170, 170, 255)));
    wilgoscCustomPlot->setBackground(QBrush(QColor(170, 170, 255)));
    temperaturaCustomPlot->setBackground(QBrush(QColor(170, 170, 255)));

    // Replot the graph
    wodaCustomPlot->replot();
    przeplywCustomPlot->replot();
    wilgoscCustomPlot->replot();
    temperaturaCustomPlot->replot();
}


void Second_Dialog::showEvent(QShowEvent* event)
{
    QDialog::showEvent(event);
    timer->start(1000); // Start the timer
}

void Second_Dialog::on_pushButton_clicked()
{
    // Show the main window and close the second dialog
    main_window->show();
    close();
}

void Second_Dialog::on_backButton_clicked()
{

}
