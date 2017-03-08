#ifndef QMAINWINDOW_H
#define QMAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QThread>
#include <string>
#include <QRect>
#include <QVector>
#include <opencv2/highgui/highgui.hpp>
#include "usbcamrecorddisp.h"
#include "auxCamRecord.h"
#include <string>
#include <QImage>
#include <QFileInfo>
#include <fstream>
#include <iterator>
#include <vector>
#include "params.h"
#include "settings_main.h"
#include <QtSerialPort/QSerialPort>
#include <QMessageBox>
#include "Scorer.h"
#include "timeClass.h"
#include "util.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTreeView>
#include <QTime>
#include "showresult.h"
#include <QStandardItemModel>

using namespace std;


namespace Ui {
class qMainWindow;
}

typedef cv::Mat myMat;

class qMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit qMainWindow(/*settings_main &p, */const params &par, string type, int level, string drName, string camAux,
                         QRect boundingRectangle,
                         QVector<QRect> pegRectBoxSmall, QVector<QRect> pegRectBoxBig,
                         const QSqlDatabase &db,
                         double withoutRing_smallRectThresh = 0, double withoutRing_bigRectThresh = 0,
                         double withRing_smallRectThresh = 0, double withRing_bigRectThresh = 0,
                         string experimentType = "Regular",
                         string details = QDate::currentDate().toString().toStdString(),
                         bool RecordOnlineEndo = false, bool RecordOnlineAux = false,
                         bool FlipVert = false, bool FlipHorz = false,
                         int thresh_ring = 0, int thresh_tool = 0,
                         QWidget *parent = 0);
    ~qMainWindow();

private slots:
    void on_actionStart_Activity_triggered();

    void on_action_Vertical_Flip_toggled(bool arg1);

    void on_action_Horizontal_Flip_triggered(bool checked);

    void updateScreen(const myMat &);

    void updateStatus(const QString & trackingMsg);

    void on_actionQuit_triggered();

    void on_actionStop_2_triggered();

    void readData();

    void handleError(QSerialPort::SerialPortError error);

    //void processEvaluationData(const vector<pair<string, pair<double, double> > > &);

    void on_actionTemp_triggered();

    void on_actionTemp2_triggered();

    void on_actionSwitch_Camera_triggered();

public slots:
    void LEDindexChange(int id);

signals:
//    void ReinitializeSettings_Main();

private:

    void cleanup();
    void openSerialPort();
    void closeSerialPort();
    void writeData(const QString str);
    const string currentDateTime();
    void stringToValues(const string &str, pair<int, int> &values, char separator);
    void processData();
    void showData();
    void saveData();

private:
    Ui::qMainWindow *ui;
    bool mFlipVert;
    bool mFlipHoriz;
    params param;
    showResult *m_showResult;
    QStandardItemModel *modelResult;
    /*settings_main *mSettingMain;*/

    QThread* mThread_endo_producer;
    QThread* mThread_endo_consumer;

    QThread* mThread_aux_producer;
    QThread* mThread_aux_consumer;

    QThread* mThread_serialComm;

    usbCamRecordDisp_producer* mProducer_endo;
    usbCamRecordDisp_consumer* mConsumer_endo;

    auxCamRecord_producer* mProducer_aux;
    auxCamRecord_consumer* mConsumer_aux;
    string type;
    int level;
    string drName;
    string camAux;
    bool RecordOnlineEndo;
    bool RecordOnlineAux;
    bool switchCam;
    bool start_serial_logging;
    string experimentType, details;
    QSerialPort *serial;

    vector<pair<string, string> > hittingInfo;
    vector<Activity> activities;
    Result result;

    QRect boundingRectangle;
    QVector<QRect> pegRectBoxSmall;
    QVector<QRect> pegRectBoxBig;
    double withoutRing_smallRectThresh, withoutRing_bigRectThresh;
    double withRing_smallRectThresh, withRing_bigRectThresh;

    int thresh_ring;
    int thresh_tool;
    std::ofstream Activity_Data;
    bool camState;
    string endoFilename;
    string auxFilename;
    string saveDirectory;
    string timestamp;
    QSqlDatabase endoDB;
    QString emailID;
    bool resultQry;
    string ResultString;
    QTime startTime;
    int TotalTimeinMs;
    bool sendtoDB;
    bool stopProcessing;
protected:
    //void timerEvent(QTimerEvent *event);
};

#endif // QMAINWINDOW_H
