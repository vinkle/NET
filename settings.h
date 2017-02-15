#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <time.h>
#include <sys/time.h>
#include <vector>
#include <utility>
#include <QDebug>
#include <unistd.h>
#include "params.h"
#include <QtSerialPort/QSerialPort>
#include <QMessageBox>
#include <QStringRef>
#include <vector>
#include <QtSql>
#include <QDate>
#include <QTime>
#include <QSqlQuery>
#include <QFileDialog>
//12-12-12
#define CALIB_BUF_SIZE_NoRing 12
#define CALIB_BUF_SIZE 12

using namespace std;

namespace Ui {
class settings;
}

class settings : public QDialog
{
    Q_OBJECT

public:
    struct Serial_settings
    {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
    };
    explicit settings(QWidget *parent = 0);
    ~settings();

    void setDB(const QSqlDatabase &endoDB);


signals:
    void makeUpdateParams(const params &);
    void enablePushButtonSig(bool val);


private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_btnCalib_clicked();
    void openSerialPort();
    void closeSerialPort();
    void readData();
    void writeData(const QByteArray &data);
    void handleError(QSerialPort::SerialPortError error);
    void enablePushButtonSlot(bool val);
    double average(const vector<double>  &v);

    void on_btnAddtoDatabase_clicked();

    void on_pushButton_clicked();

private:
    void updateSettings();
    void sendSerialCommand(const QString &);
    QString calculateCalibrationValues(bool);
    void parseStringtoNumbers(const QString &, vector<int> &numbers, int numOfValues = 1);

private:
    Ui::settings *ui;
    Serial_settings serial_settings;
    QSerialPort *serial;
    QByteArray serial_data;
    vector<QString> CNO;
    vector<QString> C01;
    vector<QString> C02;
    vector<QString> C03;
    vector<QString> C04;
    vector<QString> C05;
    vector<QString> C06;
    vector<QString> C07;
    vector<QString> C08;
    vector<QString> C09;
    vector<QString> C10;
    vector<QString> C11;
    vector<QString> C12;
    vector<int> Ring_false;
    vector<int> Ring_true;

    bool dataStopped;
    int calibCounter;

    // db
    QSqlDatabase endoDB;
    bool resultQry;
};

#endif // SETTINGS_H
