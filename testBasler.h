#ifndef CAM_TESTBALSER_H
#define CAM_TESTBALSER_H

#include <QThread>
#include <QImage>
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
#include "params.h"

using namespace std;
using namespace Pylon;
using namespace Basler_GigECameraParams;
using namespace cv;
typedef Pylon::CBaslerGigEInstantCamera Camera_t;
typedef cv::Mat myMat;

//12-12-12
class testBasler: public QObject
{
	Q_OBJECT
public:
	testBasler();

	// bool to break the event loop
    bool m_abort;

    bool m_start;

    bool m_pause;
    // Initialize the private members after set button press
    // Return false if it fails
    bool initialize(params &param, string &errmsg);

    // dtor
    ~testBasler();

signals:
    void sendtoUI(const myMat &);
    void finished();

public slots:
     // Event loop function
     void process();

private:
    CDeviceInfo info;               // Device info to create camera
    CGrabResultPtr ptrGrabResult;   // Grabber pointer from camera
    Camera_t camera;                // camera object
    uint c_countOfImagesToGrab;     // maximum number of frames to capture
    uint divider;
    uint rows;                      // No of rows
    uint cols;                      // No of cols
    uint frame_rate;                // fps
    uint size_1_rgb;                // size of rgb frame (rows*cols*3)
    uint size_1_yuv;                // size of yuv frame (rows*cols*2)
    uint n_channels;                // 3

};
#endif
