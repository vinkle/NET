#ifndef TEST_IDS_H
#define TEST_IDS_H

#include <QThread>
#include <QImage>
#include <QTime>
#include <stdio.h>
#include <QtCore>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <string>
#include <time.h>
#include <unistd.h>
#include <vector>
#include <stdexcept>
#include <sys/time.h>
#include <sstream>
#include "/usr/include/ueye.h"
#include "params.h"
using namespace std;
using namespace cv;
typedef cv::Mat myMat;
//12-12-12
class testIDS: public QObject
{
	Q_OBJECT
public:
    testIDS();


    // bool to break the event loop
    bool m_abort;

    bool m_start;
    // Initialize the private members after set button press
    bool initialize(params &param, string &errmsg);

    // dtor
    ~testIDS();
signals:
    void sendtoUI(const myMat &);
    void finished();

public slots:
     // Event loop function
    void process();

private:
     char *m_pMemBuffer;
     int   m_nMemID;
     HIDS  m_hCam;
     SENSORINFO m_SensorInfo;
     int camid;

     // member vars for capturing
     uint rows;                      // No of rows
     uint cols;                      // No of cols
     uint size_1_rgb;                // size of rgb frame (rows*cols*3)
     uint size_1_yuv;                // size of yuv frame (rows*cols*2)
     uint n_channels;                // 3
     string settingFile_yml;         // settings file to set the parameters

};

#endif
