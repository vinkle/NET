#ifndef USBCAMRECORDDISP_H
#define USBCAMRECORDDISP_H


#include <QThread>
#include <QImage>
#include "buf_endo.h"
#include <QTime>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <QtCore>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <termios.h>
#include <time.h>
#include "params.h"
#include <QRegExp>
#include <QDir>
//12-12-12
using namespace std;
using namespace cv;
typedef cv::Mat myMat;
typedef params params;
class usbCamRecordDisp_producer : public QObject
{
    Q_OBJECT
public:
    usbCamRecordDisp_producer();
    ~usbCamRecordDisp_producer();

    // Initialize the private members after set button press
    bool initialize(const params &par);
    void evaluate();
    void abort();
    void processFrame(const myMat &current_frame);
    void grab();
    bool sendFrame;


signals:
    void finished();
    void sendtoUI(const myMat &);

public slots:
     // Event loop function
     void process();


private:
    bool m_eval;
    bool m_abort;
    bool m_grab;
    VideoCapture capture_usb;
    int size_bin_endo;
    params parameters;

};

class usbCamRecordDisp_consumer : public QObject
{
    Q_OBJECT
public:
    usbCamRecordDisp_consumer();
    ~usbCamRecordDisp_consumer();

     void abort();
     void startGrabbing();

     void initialize(const params &par, const string &filename);
     vector<string> timestamp_endo;

signals:
    void finished();

public slots:
     // Event loop function
     void process();

private:
    const string currentDateTime();
    const string num2str(int num);
    params parameters;

    bool m_abort;
    bool m_grab;

    int no_of_frames;      // count no of frames captured.
    uint size_bin_endo;       // size of the bin
    cv::VideoWriter video;  // opencv videowriter object
    string videoPathName;   // capture scratch path
    string videoFilename;    // video file name
    string videoFullpath;
    bool startdumping;


};




#endif
