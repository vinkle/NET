#include "testUSB.h"
#include "params.h"
//12-12-12
testUSB::testUSB()
{
    m_abort = false;
    m_start = false;
}

int testUSB::initialize(params &param, vector<string> &devs)
{
    no_of_cameras = 0;
//    foreach (const QCameraInfo &cameraInfo, QCameraInfo::availableCameras())
//    {
//        devs.push_back(cameraInfo.description().toUtf8().constData());
//        no_of_cameras++;
//    }
//    if(no_of_cameras > 0)
//    {
//        // choose the default USB camera;
//        capture_usb.open(0);
//        // get test image to set the parameters
//        Mat test;
//        capture_usb >> test;
//        param.cap_rowsEndo = test.rows;
//        param.cap_colsEndo = test.cols;
//    }
    capture_usb.open(0);
    if (capture_usb.isOpened())
    {
        Mat test;
        capture_usb >> test;
        param.cap_rowsEndo = test.rows;
        param.cap_colsEndo = test.cols;
        no_of_cameras = 1;
        devs.push_back("Endscopic Camera on USB");
    }
    return no_of_cameras;
}

void testUSB::process()
{
    //std::vector<unsigned char> temp_rgb(size_1_rgb);
    Mat frame;
    //Mat dest;
    //Mat img3u_disp = Mat::zeros(280, 350, CV_8UC3);
    while(!m_abort)
    {
        if(m_start)
        {
            capture_usb >> frame;
            //cvtColor(frame, dest, CV_BGR2RGB);
            //resize(dest, img3u_disp, img3u_disp.size());
            //QImage qimg((uchar*)img3u_disp.data, 350, 280, img3u_disp.step, QImage::Format_RGB888);
            emit sendtoUI(frame);
            usleep(1000);
        }
    }
    capture_usb.release();
    emit finished();
}
testUSB::~testUSB()
{
    if(capture_usb.isOpened())  // check if we succeeded
    {
        cout << "Endoscopy camera got released\n";
        capture_usb.release();
    }
}
