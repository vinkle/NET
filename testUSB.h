#ifndef TEST_USB_H
#define TEST_USB_H

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
//#include <QCameraInfo>
#include <QActionGroup>
#include "params.h"
//12-12-12
using namespace std;
using namespace cv;
typedef cv::Mat myMat;

class testUSB: public QObject
{
    Q_OBJECT
public:
    testUSB();

    // bool to break the event loop
    bool m_abort;

    bool m_start;

    bool m_pause;
    
    int initialize(params &param, vector<string> &devs_endo);

    // dtor
    ~testUSB();
signals:
    void sendtoUI(const myMat &);
    void finished();

public slots:
    // Event loop function
    void process();

private:

    VideoCapture capture_usb;
    int no_of_cameras;
};


#endif
