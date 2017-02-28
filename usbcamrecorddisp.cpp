#include "usbcamrecorddisp.h"
//12-12-12
// producer functions
usbCamRecordDisp_producer::usbCamRecordDisp_producer()
{
    sendFrame = true;
    m_grab = false;
}

bool usbCamRecordDisp_producer::initialize(const params &par)
{
    parameters = par;
    m_eval = false;
    size_bin_endo = par.cap_binSize;
    m_abort = false;
    buf_endo::instance(parameters);
    capture_usb.open(0);
    if(!capture_usb.isOpened())  // check if we succeeded
        return false;

    return true;
}

void usbCamRecordDisp_producer::evaluate()
{
    m_eval = true;
}
void usbCamRecordDisp_producer::grab()
{
    m_grab = true;
}

void usbCamRecordDisp_producer::abort()
{
    m_abort = true;
}

usbCamRecordDisp_producer::~usbCamRecordDisp_producer()
{
    if(capture_usb.isOpened())  // check if we succeeded
        capture_usb.release();
}

void usbCamRecordDisp_producer::process()
{
    std::vector<Mat> vec_frame_endo(size_bin_endo);
    while(!m_abort)
    {
        // Get the 20 frames
        for (uint i = 0 ; i < size_bin_endo; ++i)
        {
            capture_usb >> vec_frame_endo[i];
            usleep(100);
            if(sendFrame)
                emit sendtoUI(vec_frame_endo[i]);
            usleep(10);
        }
        // Lock the Buffer, and produce an item
        if(m_grab)
        {
            buf_endo::instance(parameters)->mutex.lock();
            while(buf_endo::instance(parameters)->getFull())
            {
                //cout<<"Endoscopy->Producer Full \n";
                buf_endo::instance(parameters)->notFull.wait(&buf_endo::instance(parameters)->mutex);
            }
            //printf("Endo->P%d\n", buf_endo::instance()->getTail());
            buf_endo::instance(parameters)->setBuffer(vec_frame_endo);
            buf_endo::instance(parameters)->mutex.unlock();
            buf_endo::instance(parameters)->notEmpty.wakeOne();
            //cout << "In cam_endo_producer\n";
            usleep(10);
        }
    }

    // off the stream and close the camera
    cout << "Out Endoscopy Producer \n";
    capture_usb.release();
    emit finished();
}

void usbCamRecordDisp_producer::processFrame(const myMat &current_frame)
{
    // process the current frame; Entry point for the online evaluation for the endoscopy camera.


}

// consumer functions
usbCamRecordDisp_consumer::usbCamRecordDisp_consumer()
{
    videoPathName = "";
}
usbCamRecordDisp_consumer::~usbCamRecordDisp_consumer()
{
    m_grab = false;
}

void usbCamRecordDisp_consumer::abort()
{
    m_abort = true;
}

void usbCamRecordDisp_consumer::startGrabbing()
{
    m_grab = true;
}

void usbCamRecordDisp_consumer::initialize(const params &par, const string &filename)
{
    parameters = par;
    // getting the first path
    videoPathName = filename;
    videoFilename = filename;
    videoFullpath = filename;
    m_grab = false;
    m_abort = false;
    size_bin_endo = 20;
    no_of_frames = 0;
    timestamp_endo.clear();
    startdumping = false;
}

const string usbCamRecordDisp_consumer::currentDateTime()
{
    timeval curTime;
    gettimeofday(&curTime, NULL);
    int milli = curTime.tv_usec / 1000;

    char buffer [80];
    strftime(buffer, 80, "%H:%M:%S", localtime(&curTime.tv_sec));

    char currentTime[84] = "";
    sprintf(currentTime, "%s:%d", buffer, milli);
    return currentTime;
}

const string usbCamRecordDisp_consumer::num2str(int num)
{
    string str;
    str = dynamic_cast< std::ostringstream & >(( std::ostringstream() << std::dec << num ) ).str();
    return str;
}

void usbCamRecordDisp_consumer::process()
{
    while(!m_abort)
    {
        std::vector<cv::Mat> vec_frame_consume;
        if(m_grab)
        {
            buf_endo::instance(parameters)->mutex.lock();
            while (buf_endo::instance(parameters)->getEmpty())
            {
                //cout << "Endoscopy-> Consumer: queue EMPTY.\n";
                buf_endo::instance(parameters)->notEmpty.wait(&buf_endo::instance(parameters)->mutex);
            }
            //printf("Endo->C%d\n", buf_endo::instance()->getHead());
            buf_endo::instance(parameters)->getBuffer(vec_frame_consume);
            buf_endo::instance(parameters)->mutex.unlock();
            buf_endo::instance(parameters)->notFull.wakeOne();
            if(!vec_frame_consume.empty())
            {
                for(int i = 0; i < size_bin_endo; i++)
                {
                    if(!startdumping)
                    {
                        cout << "started dumping endo\n";
                        cout << "capture path endo ->" << videoFullpath << endl;
                        video.open(videoFullpath.c_str(), CV_FOURCC('F','M','P','4'), 25, Size(vec_frame_consume[0].cols, vec_frame_consume[0].rows), true);
                        startdumping = true;
                    }
                    video.write(vec_frame_consume[i]);
                    timestamp_endo.push_back("Endo " + num2str(++no_of_frames) + " " + currentDateTime());
                    usleep(10);
                }
            }
            else
            {
                cout << "vector is empty \n";
            }
        }
        usleep(10);
    }
    cout << "No of frames produced (Endoscopy)-> " << no_of_frames<< endl;
    no_of_frames = 0;
    video.release();
    cout << "video capture released \n";
    emit finished();
}
