#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "second_dialog.h"
#include <QPixmap>
#include <QDir>
#include <Qt>
#include <QPainter>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

int picuters_names[25] = {0,5,10,20,20,25,30,35,35,40,45,50,50,55,60,65,65,70,75,80,85,85,90,95,100};
//int picuters_names[7] = {0,20,35,50,65,80,100};
bool polacz_clicked = false;
int language = 0;

MainWindow::MainWindow(int* dataArray, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    receivedDataArray = dataArray;

    qDebug() << "Data in MainWindow:" << receivedDataArray[0] << receivedDataArray[1] << receivedDataArray[2] << receivedDataArray[3];

    ui->Zbiornik_woda->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->Krople_wody->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->Termometr->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(ui->comboBox_jezyk, SIGNAL(currentIndexChanged(int)), this, SLOT(languageSelection(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
        return;
    }
    QMainWindow::changeEvent(event);
}

void MainWindow::on_przycisk_wykresy_clicked()
{
    sec_dial = new Second_Dialog(this);
    sec_dial->show();
}

void MainWindow::languageSelection(int id) {

    static QTranslator *translator = new QTranslator();

    if (id == 0) {
        qApp->removeTranslator(translator);
        if (translator->load("polish", "X:/QT/projekty/Stacja_miernicza")) {
            qApp->installTranslator(translator);
            language = 0;
        }
    } else if (id == 1) {
        qApp->removeTranslator(translator);
        if (translator->load("english", "X:/QT/projekty/Stacja_miernicza")) {
            qApp->installTranslator(translator);
            language = 1;
        }
    }
}

void MainWindow::setReceivedDataArray(int* dataArray)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database");

    if (!db.open()) {
        qDebug() << "Failed to connect to the database:" << db.lastError().text();
        // Handle the error
    } else {
        qDebug() << "Connected to the database!";
    }

    QString imagePath;
    QString imagePath2;
    QString imagePath3;
    QString alert1_imagePath;
    QString alert2_imagePath;
    QString alert3_imagePath;
    QString alert4_imagePath;
    QString przeplyw_imagePath;
    QString chmurka_imagePath;
    QString temperatura_imagePath;
    QString currentDir = QDir::currentPath();
    QString dioda_imagePath = currentDir + "/obrazki/niepolaczone.png";

    if(polacz_clicked){
        if (receivedDataArray[2] < 25)
            //imagePath = currentDir + "/obrazki/woda/woda" + QString::number(picuters_names[7-receivedDataArray[2]]) + ".png";
            imagePath = currentDir + "/obrazki/woda/woda" + QString::number(picuters_names[25-receivedDataArray[2]]) + ".png";
        else
            imagePath = currentDir + "/obrazki/woda/woda0.png";

        imagePath2 = currentDir + "/obrazki/napis1.png";
        imagePath3 = currentDir + "/obrazki/napis1.png";
        if(receivedDataArray[2] < 7)
            alert1_imagePath = currentDir + "/obrazki/alert.png";
        if(receivedDataArray[3] > 1000)
            alert2_imagePath = currentDir + "/obrazki/alert.png";
        if (receivedDataArray[1] > 70)
            alert3_imagePath = currentDir + "/obrazki/alert.png";
        if(receivedDataArray[0] > 30)
            alert4_imagePath = currentDir + "/obrazki/alert.png";
        przeplyw_imagePath = currentDir + "/obrazki/przeplyw.png";
        chmurka_imagePath = currentDir + "/obrazki/chmurka.png";
        dioda_imagePath = currentDir + "/obrazki/polaczone.png";

        if (receivedDataArray[0] < 45 && receivedDataArray[0] > 5)
            temperatura_imagePath = currentDir + "/obrazki/temperatura/temperatura" + QString::number(receivedDataArray[0]) + ".png";
        else if (receivedDataArray[0] > 45)
            temperatura_imagePath = currentDir + "/obrazki/temperatura/temperatura45.png";
        else
            temperatura_imagePath = currentDir + "/obrazki/temperatura/temperatura5.png";
    }
    else{
        imagePath = "";
        imagePath2 = "";
        imagePath3 = "";
        alert1_imagePath = "";
        alert2_imagePath = "";
        alert3_imagePath = "";
        alert4_imagePath = "";
        przeplyw_imagePath = "";
        chmurka_imagePath = "";
        temperatura_imagePath = "";
        dioda_imagePath = currentDir + "/obrazki/niepolaczone.png";
    }

    for (int i = 0; i < 4; i++) {
        receivedDataArray[i] = dataArray[i];
    }

    qDebug() << "Data in MainWindow:" << receivedDataArray[0] << receivedDataArray[1] << receivedDataArray[2] << receivedDataArray[3];

    //QString currentDir = QDir::currentPath();
//    QString imagePath;

//    if (receivedDataArray[2] < 25)
//        imagePath = currentDir + "/obrazki/woda/woda" + QString::number(picuters_names[25-receivedDataArray[2]]) + ".png";
//    else
//        imagePath = currentDir + "/obrazki/woda/woda0.png";

    // Load the image
    QPixmap image(imagePath);

    // Get the size of the QLabel "Zbiornik_woda"
    QSize labelSize = ui->Zbiornik_woda->size();

    // Scale the image to fit the size of the QLabel
    QPixmap scaledImage = image.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->Zbiornik_woda->setPixmap(scaledImage);

    // Center align the pixmap within the QLabel
    ui->Zbiornik_woda->setAlignment(Qt::AlignCenter);


    // Load the image
    QPixmap dioda(dioda_imagePath);

    // Get the width of the QLabel "woda_ml"
    int dioda_newWidth = ui->dioda->width();

    // Scale the image while preserving the aspect ratio
    QPixmap dioda_adjustedImage = dioda.scaledToWidth(dioda_newWidth, Qt::SmoothTransformation);

    // Create a QPainter to draw on the adjusted pixmap
    QPainter dioda_painter(&dioda_adjustedImage);

    // Set the adjusted pixmap as the QLabel's pixmap
    ui->dioda->setPixmap(dioda_adjustedImage);

    // Center align the pixmap within the QLabel
    ui->dioda->setAlignment(Qt::AlignCenter);


    // Load the image
    QPixmap image2(imagePath2);

    // Get the width of the QLabel "woda_ml"
    int woda_ml_newWidth = ui->woda_ml->width();

    // Scale the image while preserving the aspect ratio
    QPixmap woda_ml_adjustedImage = image2.scaledToWidth(woda_ml_newWidth, Qt::SmoothTransformation);

    // Create a QPainter to draw on the adjusted pixmap
    QPainter woda_ml_painter(&woda_ml_adjustedImage);

    // Draw the data value on top of the image
    QString woda_ml_dataValue;
    if(receivedDataArray[2] < 25)
        //woda_ml_dataValue = QString::number(1000-receivedDataArray[2]*143) + " ml";
        woda_ml_dataValue = QString::number(500-receivedDataArray[2]*20) + " ml";
    else
        woda_ml_dataValue = "0 ml";

    woda_ml_painter.drawText(QRect(0, 0, woda_ml_adjustedImage.width(), woda_ml_adjustedImage.height()), Qt::AlignCenter, woda_ml_dataValue);

    // Set the adjusted pixmap as the QLabel's pixmap
    ui->woda_ml->setPixmap(woda_ml_adjustedImage);

    // Center align the pixmap within the QLabel
    ui->woda_ml->setAlignment(Qt::AlignCenter);



    // Load the image
    QPixmap image3(imagePath3);

    // Get the width of the QLabel "woda_ml"
    int woda_proc_Width = ui->woda_proc->width();

    // Scale the image while preserving the aspect ratio
    QPixmap woda_proc_adjustedImage = image3.scaledToWidth(woda_proc_Width, Qt::SmoothTransformation);

    // Create a QPainter to draw on the adjusted pixmap
    QPainter woda_proc_painter(&woda_proc_adjustedImage);

    // Draw the data value on top of the image
    QString dataValue;
    if(receivedDataArray[2] < 25)
        dataValue = QString::number(100-receivedDataArray[2]*4) + "%";
    else
        dataValue = "0 %";
    woda_proc_painter.drawText(QRect(0, 0, woda_proc_adjustedImage.width(), woda_proc_adjustedImage.height()), Qt::AlignCenter, dataValue);

    // Set the adjusted pixmap as the QLabel's pixmap
    ui->woda_proc->setPixmap(woda_proc_adjustedImage);

    // Center align the pixmap within the QLabel
    ui->woda_proc->setAlignment(Qt::AlignCenter);




    // Load the image
    QPixmap alert1_image(alert1_imagePath);

    // Get the width of the QLabel "woda_ml"
    int alert1_Width = ui->Alert1->width();

    // Scale the image while preserving the aspect ratio
    QPixmap alert1_adjustedImage = alert1_image.scaledToWidth(alert1_Width, Qt::FastTransformation);

    // Set the adjusted pixmap as the QLabel's pixmap
    ui->Alert1->setPixmap(alert1_adjustedImage);

    // Center align the pixmap within the QLabel
    ui->Alert1->setAlignment(Qt::AlignCenter);

    // Load the image
    QPixmap alert2_image(alert2_imagePath);

    // Get the width of the QLabel "woda_ml"
    int alert2_Width = ui->Alert2->width();

    // Scale the image while preserving the aspect ratio
    QPixmap alert2_adjustedImage = alert2_image.scaledToWidth(alert2_Width, Qt::FastTransformation);

    // Set the adjusted pixmap as the QLabel's pixmap
    ui->Alert2->setPixmap(alert2_adjustedImage);

    // Center align the pixmap within the QLabel
    ui->Alert2->setAlignment(Qt::AlignCenter);

    QPixmap alert3_image(alert3_imagePath);

    // Get the size of the QLabel "Alert3"
    QSize alert3_labelSize = ui->Alert3->size();

    // Scale the image to fit the size of the QLabel
    QPixmap alert3_scaledImage = alert3_image.scaled(alert3_labelSize * 1.1, Qt::KeepAspectRatio, Qt::FastTransformation);

    // Set the adjusted pixmap as the QLabel's pixmap
    ui->Alert3->setPixmap(alert3_scaledImage);

    // Center align the pixmap within the QLabel
    ui->Alert3->setAlignment(Qt::AlignCenter);


    // Load the image
    QPixmap alert4_image(alert4_imagePath);

    // Get the width of the QLabel "woda_ml"
    int alert4_Width = ui->Alert4->width();

    // Scale the image while preserving the aspect ratio
    QPixmap alert4_adjustedImage = alert4_image.scaledToWidth(alert4_Width, Qt::FastTransformation);

    // Set the adjusted pixmap as the QLabel's pixmap
    ui->Alert4->setPixmap(alert4_adjustedImage);

    // Center align the pixmap within the QLabel
    ui->Alert4->setAlignment(Qt::AlignCenter);



    /* PRZEPLYW */

    // Load the image
    QPixmap przeplyw_image(przeplyw_imagePath);

    // Get the size of the QLabel "Zbiornik_woda"
    QSize przeplyw_labelSize = ui->Przeplyw_tuba->size();

    // Scale the image to fit the size of the QLabel
    QPixmap przeplyw_scaledImage = przeplyw_image.scaled(przeplyw_labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Create a QPainter to draw on the adjusted pixmap
    QPainter przeplyw_painter(&przeplyw_scaledImage);

    // Draw the data value on top of the image
    QString przeplyw_dataValue = QString::number(receivedDataArray[3])+ "ml/min";
    QFont font_przeplyw;
    font_przeplyw.setPointSizeF(0.05 * przeplyw_labelSize.height()); // Set the font size as a fraction of the label's height
    przeplyw_painter.setFont(font_przeplyw);
    przeplyw_painter.setPen(Qt::black); // Set the desired text color

    // Calculate the position to adjust the text vertically
    int textHeight_przeplyw = QFontMetricsF(font_przeplyw).height();
    int verticalOffset = przeplyw_scaledImage.height() / 2.2; // Adjust the vertical offset as desired

    // Calculate the y position by subtracting the vertical offset from the text height
    int y_przeplyw = textHeight_przeplyw - verticalOffset;

    // Calculate the x position to shift the text to the left
    int x_przeplyw = -(przeplyw_scaledImage.width() / 30); // Adjust the horizontal shift as desired

    // Draw the text on the adjusted pixmap
    przeplyw_painter.drawText(przeplyw_scaledImage.rect().translated(x_przeplyw, y_przeplyw), Qt::AlignCenter, przeplyw_dataValue);

    ui->Przeplyw_tuba->setPixmap(przeplyw_scaledImage);

    // Center align the pixmap within the QLabel
    ui->Przeplyw_tuba->setAlignment(Qt::AlignCenter);




    /* CHMURKA */

    // Load the image
    QPixmap chmurka_image(chmurka_imagePath);

    // Get the size of the QLabel "Zbiornik_woda"
    QSize chmurka_labelSize = ui->Krople_wody->size();

    // Scale the image to fit the size of the QLabel
    QPixmap chmurka_scaledImage = chmurka_image.scaled(chmurka_labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Create a QPainter to draw on the adjusted pixmap
    QPainter chmurka_painter(&chmurka_scaledImage);

    // Draw the data value on top of the image
    QString chmurka_dataValue = QString::number(receivedDataArray[1])+ "% RH";
    QFont font;
    font.setPointSizeF(0.05 * chmurka_labelSize.height()); // Set the font size as a fraction of the label's height
    chmurka_painter.setFont(font);
    chmurka_painter.setPen(Qt::blue); // Set the desired text color

    // Calculate the position to center the text vertically
    int textHeight = QFontMetricsF(font).height();
    int y = (chmurka_scaledImage.height() - textHeight) / 3.25; // Adjust the vertical position as desired

    // Draw the text on the adjusted pixmap
    chmurka_painter.drawText(chmurka_scaledImage.rect().translated(0, y), Qt::AlignCenter, chmurka_dataValue);

    ui->Krople_wody->setPixmap(chmurka_scaledImage);

    // Center align the pixmap within the QLabel
    ui->Krople_wody->setAlignment(Qt::AlignCenter);



    /* TEMPERATURA */

    // Load the image

    QPixmap temperatura_image(temperatura_imagePath);

    // Get the size of the QLabel "Zbiornik_woda"
    QSize temperatura_labelSize = ui->Termometr->size();

    // Scale the image to fit the size of the QLabel
    QPixmap temperatura_scaledImage = temperatura_image.scaled(temperatura_labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Create a QPainter to draw on the adjusted pixmap
    QPainter temperatura_painter(&temperatura_scaledImage);

    // Draw the data value on top of the image
    QString temperatura_dataValue = QString::number(receivedDataArray[0])+ " °C";
    QFont font_temperatura;
    font_temperatura.setPointSizeF(0.05 * temperatura_labelSize.height()); // Set the font size as a fraction of the label's height
    temperatura_painter.setFont(font_temperatura);
    temperatura_painter.setPen(Qt::green); // Set the desired text color

    // Calculate the position to center the text vertically
    int textHeight_temperatura = QFontMetricsF(font_temperatura).height();
    int y_temperatura = (temperatura_scaledImage.height() - textHeight_temperatura) / 2.5; // Adjust the vertical position as desired
    int x_temperatura = -temperatura_scaledImage.width() / 2.7; // Adjust the horizontal position as desired

    // Draw the text on the adjusted pixmap
    temperatura_painter.drawText(temperatura_scaledImage.rect().translated(x_temperatura, y_temperatura), Qt::AlignCenter, temperatura_dataValue);


    ui->Termometr->setPixmap(temperatura_scaledImage);

    // Center align the pixmap within the QLabel
    ui->Termometr->setAlignment(Qt::AlignCenter);

    db.close();
}

void MainWindow::on_przycisk_polacz_clicked()
{
    polacz_clicked = true;
}

