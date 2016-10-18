#ifndef SETTINGS_MAIN_H
#define SETTINGS_MAIN_H

#include <QDialog>
#include <QDebug>
#include <string>
#include <QImage>
#include <QFileInfo>
#include <fstream>
#include <iterator>
#include <vector>
#include <QtCore>
#include <QFile>
#include <QTextStream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QTimer>
#include <QCameraInfo>
#include <QGraphicsScene>
#include <sys/time.h>
#include <QDebug>
#include <QMessageBox>
#include <QThread>
#include <QCloseEvent>
#include <QVector>
#include "testBasler.h"
#include "testIDS.h"
#include "testUSB.h"
#include "qmainwindow.h"
#include "settings.h"
#include "params.h";
#include <QMessageBox>
#include <QtSql>
#include <QSqlQuery>
#include <QDir>
//12-12-12
using namespace std;
using namespace cv;
typedef cv::Mat myMat;

#define SmallRect_Width 320
#define SmallRect_Height 256
#define RatioRect 4

namespace Ui {
class settings_main;
}

class settings_main : public QDialog
{
    Q_OBJECT

public:
    explicit settings_main(QWidget *parent = 0);
    ~settings_main();

    void clearUI();
    //virtual void closeEvent(QCloseEvent *event);

private slots:
    void on_tabWidget_tabBarClicked(int index);
    void on_pbPractice_clicked();
    void on_pbOnline_clicked();
    void on_pbOffline_clicked();
    void on_listWidgetEndoOnline_clicked(const QModelIndex &index);
    void on_listWidgetAuxOnline_clicked(const QModelIndex &index);
    void updatelblAux(const myMat &);
    void updatelblEndo(const myMat &);
    void on_pbQuit_clicked();
    void on_listWidgetAuxOffline_clicked(const QModelIndex &index);
    void on_listWidgetEndoOffline_clicked(const QModelIndex &index);
    void on_listWidgetPractice_clicked(const QModelIndex &index);
    void on_pbRefresh_clicked();
    void openSettingsDialog();
    void updateParameters(const params &params);
    bool initialSetup();


    void on_checkCalib_clicked(bool checked);


    void on_checkBox_3_clicked(bool checked);

    void on_radioPegSegment_clicked(bool checked);

    void on_radioRingSegment_clicked(bool checked);

    void on_radioToolTipSegment_clicked(bool checked);


    void mouseClickOnAuxCam(string &clk, vector<int> &data);
    void mouseMoveOnAuxCam(vector<int> &data);
    void mouseReleaseOnAuxCam(vector<int> &data);

    //void on_sliderPegSegment_valueChanged(int value);

    void on_btnBoundingBox_clicked();

    void on_btnPegSegment_clicked();

    void on_sliderRingSegment_valueChanged(int value);

    void on_btnRingSegment_clicked();

    void on_sliderToolSegment_valueChanged(int value);

    void on_btnToolSegment_clicked();

    void on_boxType_currentIndexChanged(const QString &arg1);

    void handleError(QSerialPort::SerialPortError error);

protected:
    virtual void  keyPressEvent(QKeyEvent *event);


private:
    void cleanup();
    void parse_AuxCamCalib();
    bool checkSettings();
    void openSerialPort();
    void closeSerialPort();
    void writeData(const QString str);
    void ringSegment(const cv::Mat &img, int value);
    cv::Rect rect(const QRect &r);
    double sumAfterRingSegment(const cv::Mat &img, int value, const QRect &r);
    void updateNames();
private:
    Ui::settings_main *ui;
    //QMap<QString, QAction *> cameraStr;
    QMainWindow *mainWindow;
    settings  *mSettings;

    testBasler *mTest_Basler;
    testIDS    *mTest_IDS;
    testUSB    *mTest_USB;
    QThread* thread_endo;
    QThread* thread_aux;

    QImage AuxImg;
    cv::Mat EndoImg, AuxImg_full;

    params parameters;
    QVector<QRect> pegs_small;
    QVector<QRect> pegs_big;
    QVector<pair<double, double> > withRingThresh;
    QVector<pair<double, double> > withoutRingThresh;
    double withoutRing_smallRectThresh, withoutRing_bigRectThresh;
    double withRing_smallRectThresh, withRing_bigRectThresh;

    QSerialPort *serial;


    // Database details
    QSqlDatabase endoDB;
    QString path_to_db;
    //QSqlQuery query;
    bool resultQry;

    int cameraCountEndo;
    int cameraCountAux;
    bool camBaslerFound, camIDSFound, camEndoFound, camAuxFound, endoInitialized, auxInitialized;
    string devAux;
    string errmsg;
    vector<string> devs_endo;
    Mat img3u_disp;
    Mat img3u_disp1;
    Rect pegGroupROI;


    QGraphicsScene *scene_aux;
    QGraphicsScene *scene_endo;
    QRect boundingRectangle;
    int ring_segment;
    int tool_segment;
    bool mouseDrag;
    int x_left_start, y_left_start;
    bool  segment_peg, segment_tool;
    bool segment_ring;
    QRect temp_rect, temp_rectBig;
    QString filename_auxCamCalib;
    cv::Mat element[4];

};
#endif
