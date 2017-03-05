#ifndef AUXCAMRECORD_H
#define AUXCAMRECORD_H

#include <QThread>
#include <QImage>
#include "buf_aux.h"
#include <QTime>
#include <stdio.h>
#include <QtCore>
#include <pylon/PylonIncludes.h>
#include <pylon/gige/BaslerGigEInstantCamera.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <string>
#include <time.h>
#include <unistd.h>
#include <vector>
#include <sys/time.h>
#include <stdexcept>
#include <time.h>
#include "/usr/include/ueye.h"
#include <QDebug>
#include "params.h"
#include <QDir>
#include <QTime>
#include "tracker/MedianFlowTracker.h"

using namespace std;
using namespace Pylon;
using namespace Basler_GigECameraParams;
using namespace cv;
typedef cv::Mat myMat;
typedef Pylon::CBaslerGigEInstantCamera Camera_t;
#define TRACKING_BLOB_THRESH 10
#define THRESH_RING_SEGMENT_ON 50000
#define THRESH_RING_SEGMENT_OFF 1000
#define THRESH_PICKING_TO_PICKING 200000
#define THRESH_PICKING_TO_MOVING 5000
#define STABLE_COUNT 50
#define No_pegs 12
#define HITTING_THRESHOLD 5
class auxCamRecord_producer:public QObject
{
    Q_OBJECT
public:
    auxCamRecord_producer();
    // Initialize the private members after set button press
    bool initialize(const params &par, string &errmsg,
                    const QRect &boundingRectangle,
                    const QVector<QRect> &pegRectBoxSmall,
                    const QVector<QRect> &pegRectBoxBig,
                    double withoutRing_smallRectThresh, double withoutRing_bigRectThresh,
                    double withRing_smallRectThresh, double withRing_bigRectThresh,
                    int thresh_ring, int thresh_tool);
    void evaluate();
    void abort();
    void grab();
    void processFrame(const cv::Mat &prv_frame, const cv::Mat &current_frame);
    int hittingDetection(const cv::Mat &prv_frame, const cv::Mat &current_frame);
    void tuggingDetection(const cv::Mat &current_frame);
    const string currentDateTime();
    Rect blobTrack(const cv::Mat &current_frame);
    void medianFlowTrack(const cv::Mat &);
    void medianFlowInit(const cv::Mat &img, Rect *bb);
    void track(const cv::Mat &current_frame);
    bool sendFrame;
    vector<pair<string, pair<double, double> > > trackingData;
    vector<pair<string, int > > hittingData_fdiff;
    vector<vector<vector<Point> > > tuggingData;
    vector<pair<pair<string, int>, string> >  stateInfo; //timestamp, count, state
    // dtor
    ~auxCamRecord_producer();

signals:
     void finished();
     void sendtoUI(const myMat &);
     //void sendEvalData(const vector<pair<string, pair<double, double> > > &);
     void changeLEDIndex(int id);
     void sendTrackingStatus(const QString &);

public slots:
     // Event loop function
     void process();

private:
    cv::Rect rect(const QRect &);
    string getState(const cv::Mat &current_frame);
    Rect * copyRect(Rect *r);
    bool indexSet;
    string status;

private:
    //pylon specific
    CDeviceInfo info;               // Device info to create camera
    CGrabResultPtr ptrGrabResult;   // Grabber pointer from camera
    Camera_t camera;                // camera object
    uint c_countOfImagesToGrab;     // maximum number of frames to capture

    // ids specific
    char *m_pMemBuffer;
    int   m_nMemID;
    HIDS  m_hCam;
    SENSORINFO m_SensorInfo;
    int camid;
    params parameters;

    // tracker parameters
    MedianFlowTracker *medianFlowTracker;
    cv::Rect *prevBB;
    cv::Rect *currBB;
    cv::Mat prevImg;
    cv::Mat currImg;
    bool startMedFlowTracker;

    // bools to control flow
    bool m_abort;
    bool m_eval;

    string deviceName;
    uint divider;
    uint rows;                      // No of rows
    uint cols;                      // No of cols
    uint size_bin_aux;              // bin size
    uint frame_rate;                // fps
    uint size_1_rgb;                // size of rgb frame (rows*cols*3)
    uint size_1_yuv;                // size of yuv frame (rows*cols*2)
    uint n_channels;                // 3


    cv::Mat element[4];
    QRect boundingRectangle;
    QVector<QRect> pegRectBoxSmall;
    QVector<QRect> pegRectBoxBig;
    double withoutRing_smallRectThresh, withoutRing_bigRectThresh;
    double withRing_smallRectThresh, withRing_bigRectThresh;

    int thresh_ring;
    int thresh_tool;
    int stable_count;
    int current_index, old_index;
    int countFrame;
    bool m_grab;

    QTime trackingTimer;
    Mat img3u, img3u_prv;
    Mat diff, canny_output, dst;
    int thresh;
    Mat kernel;
    vector<vector<Point> > contours;
    vector<vector<Point> > contours_tug;
    vector<Vec4i> hierarchy;
    vector<Vec4i> hierarchy_tug;
    int smallImage_width, smallImage_height;
    cv::Size smallSize;
    QString stat;

};


class auxCamRecord_consumer:public QObject
{
    Q_OBJECT
public:
    auxCamRecord_consumer();

    // Initialize the private members after set button press
    void initialize(const params &par, const string &drName);
    void abort();
    void startGrabbing();
    // dtor
    ~auxCamRecord_consumer();


    //timestamp
    vector<string> timestamp_aux;

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
     //bool to start the duming the frame
     bool m_grab;


     uint divider;
     uint rows;                 // No of rows
     uint cols;                 // No of cols
     uint n_channels;           // 3
     uint size_1_rgb;           // size of rgb frame (rows*cols*3)
     uint size_bin_aux;         // Bin Size
     int no_of_frames;          // count no of frames captured.
     cv::VideoWriter videoWriter;     // opencv videowriter object
     string capturePath;
     string videoFullpath;      // capture scratch path
     bool startdumping;
};

#endif // AUXCAMRECORD_H
