#ifndef COMPORTDIALOG_H
#define COMPORTDIALOG_H

#include <QDialog>
#include <QListWidget>

namespace Ui {
class COMPortDialog;
}

class COMPortDialog : public QDialog
{
    Q_OBJECT

public:
    COMPortDialog(QWidget *parent = nullptr);

    QString getSelectedPort() const;

public:
    void populateCOMPorts(const QStringList& comPorts);

private slots:
    void selectPort();

private:
    QListWidget* listWidget;
};

#endif // COMPORTDIALOG_H
