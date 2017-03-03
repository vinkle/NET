#include "auxCamRecord.h"

auxCamRecord_producer::auxCamRecord_producer()
{
    sendFrame = false;
    old_index = -1;
    current_index =  (rand() % (int)(No_pegs)) + 1;
    //current_index = 7;
    element[0] = getStructuringElement(MORPH_ELLIPSE, Size(3, 3), Point(0, 0));
    element[1] = getStructuringElement(MORPH_ELLIPSE, Size(8, 8), Point(0, 0));
    element[2] = getStructuringElement(MORPH_ELLIPSE, Size(3, 3), Point(0, 0));
    element[3] = getStructuringElement(MORPH_ELLIPSE, Size(3, 3), Point(0, 0));
    stable_count = 0;
    countFrame = 0;
    m_grab = false;
    startMedFlowTracker = false;
    indexSet = true;
    //changeLEDIndex(current_index);

    currBB = NULL;
    prevBB = new Rect(0,0,0,0);
    medianFlowTracker = new MedianFlowTracker();
}
auxCamRecord_producer::~auxCamRecord_producer()
{
    if(deviceName == "basler")
    {
        if(camera.IsOpen())
            camera.Close();
    }
}

void auxCamRecord_producer::grab()
{
    m_grab = true;
}

Rect * auxCamRecord_producer::copyRect(Rect *r)
{
    Rect *r2 = new Rect();
    r2->x = r->x;
    r2->y = r->y;
    r2->width = r->width;
    r2->height = r->height;
    return r2;
}

void auxCamRecord_producer::medianFlowInit(const cv::Mat &img, Rect *bb)
{
    Mat gray;
    if(img.channels() == 3)
    {
        cv::cvtColor(img, gray, CV_BGR2GRAY);
        currImg = gray.clone();
    }
    else
    {
        currImg = img.clone();
    }
    if(currBB)
    {
        delete currBB;
        currBB = NULL;
    }
    currBB = copyRect(bb);
}

void auxCamRecord_producer::medianFlowTrack(const cv::Mat &img)
{
    prevImg.release();
    prevImg = currImg.clone();
    if(currBB)//Store old bounding box (if any)
    {
        prevBB->x = currBB->x;
        prevBB->y = currBB->y;
        prevBB->width = currBB->width;
        prevBB->height = currBB->height;
    }
    else
    {
        prevBB->x = 0;
        prevBB->y = 0;
        prevBB->width = 0;
        prevBB->height = 0;
    }
    medianFlowTracker->cleanPreviousData();

    Mat grey_frame;
    if(img.channels() == 3)
    {
        cvtColor(img, grey_frame, CV_BGR2GRAY);
        currImg = grey_frame.clone();
    }
    else
    {
        currImg = img.clone();
    }
    medianFlowTracker->track(prevImg, currImg, prevBB);
    if (currBB)
    {
        delete currBB;
        currBB = NULL;
    }
    Rect *trackerBB = medianFlowTracker->trackerBB;
    if (trackerBB != NULL)
    {
        currBB = copyRect(trackerBB);
    }
    else
    {
        startMedFlowTracker = false;
        if (currBB)
        {
            delete currBB;
            currBB = NULL;
        }
    }
}

Rect auxCamRecord_producer::blobTrack(const cv::Mat &current_frame)
{
    // process the current frame; Entry point for the online evaluation for the auxiliary camera.
    Rect rectA = Rect(-1,-1,-1,-1);
    Mat hsv, tooltip;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    cvtColor(current_frame, hsv, CV_BGR2HSV);
    inRange(hsv, cv::Scalar(50, 130, 100), cv::Scalar(thresh_tool, 255, 255), tooltip);
    erode(tooltip, tooltip, Mat(), Point(-1, -1), 2, 1, 1);
    dilate(tooltip, tooltip, Mat(), Point(-1, -1), 2, 1, 1);
    dilate(tooltip, tooltip, Mat(), Point(-1, -1), 2, 1, 1);
    erode(tooltip, tooltip, Mat(), Point(-1, -1), 2, 1, 1);

    findContours(tooltip, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    if(contours.size() > 0)
    {
        int Maxsize = contours[0].size();
        int index = 0;
        for (int i = 1; i < contours.size(); ++i)
        {
            int size = contours[i].size();
            if (Maxsize < size)
            {
                Maxsize = size;
                index = i;
            }
        }
        if(contours[index].size() > TRACKING_BLOB_THRESH)
        {
            vector<Point> poly;
            approxPolyDP( Mat(contours[index]), poly, 3, true );
            rectA = boundingRect(Mat(poly));
            sendTrackingStatus("Tracking Active:(" + QString::number(rectA.x) + ","+
                                                     QString::number(rectA.y) + ","+
                                                     QString::number(rectA.width) + ","+
                                                     QString::number(rectA.height) + ")");
        }
    }
    return rectA;
}

void auxCamRecord_producer::track(const cv::Mat &current_frame)
{
    if(!startMedFlowTracker)
    {
        //qDebug() << "blob tracker active\n";
        Rect p = blobTrack(current_frame);
        if(p.width != -1)
        {
            startMedFlowTracker = true;
            medianFlowInit(current_frame, &p);
        }
    }
    else
    {
        //qDebug() << "Lucas kanade active\n";
        medianFlowTrack(current_frame);
    }

}

const string auxCamRecord_producer::currentDateTime()
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


bool auxCamRecord_producer::initialize(const params &par, string &errmsg,
                                       const QRect &boundingRectangle,
                                       const QVector<QRect> &pegRectBoxSmall,
                                       const QVector<QRect> &pegRectBoxBig,
                                       double withoutRing_smallRectThresh, double withoutRing_bigRectThresh,
                                       double withRing_smallRectThresh, double withRing_bigRectThresh,
                                       int thresh_ring, int thresh_tool)
{
    // instantiate the buffer class;
    // and private variables 12-12-12
    this->boundingRectangle = boundingRectangle;
    this->pegRectBoxSmall = pegRectBoxSmall;
    this->pegRectBoxBig = pegRectBoxBig,
    this->withoutRing_smallRectThresh = withoutRing_smallRectThresh;
    this->withoutRing_bigRectThresh = withoutRing_bigRectThresh;
    this->withRing_smallRectThresh = withRing_smallRectThresh;
    this->withRing_bigRectThresh = withRing_bigRectThresh;
    this->thresh_ring = thresh_ring;
    this->thresh_tool = thresh_tool;
    qDebug() << "boundingRectangle " << boundingRectangle;
    qDebug() << "pegRectBoxSmall " << pegRectBoxSmall;
    qDebug() << "pegRectBoxBig " << pegRectBoxBig;
    qDebug() << "withoutRing_smallRectThresh " << withoutRing_smallRectThresh;
    qDebug() << "withoutRing_bigRectThresh " << withoutRing_bigRectThresh;
    qDebug() << "withRing_smallRectThresh " << withRing_smallRectThresh;
    qDebug() << "withRing_bigRectThresh " << withRing_bigRectThresh;
    qDebug() << "thresh_ring " << thresh_ring;
    qDebug() << "thresh_tool " << thresh_tool;

    parameters = par;
    buf_aux::instance(par);
    rows = par.cap_rowsAux;
    cols = par.cap_colsAux;
    frame_rate = par.cap_fpsAux;
    size_bin_aux = par.cap_binSize;
    camid =par.cap_camID_IDS;
    deviceName = par.cap_auxCam;
    n_channels = 3;
    size_1_rgb = rows * cols * n_channels;
    size_1_yuv = rows * cols * 2;
    m_abort = false;
    c_countOfImagesToGrab = 1800000;
    if(deviceName == "basler")
    {
        try
        {
            if(!camera.IsOpen())
            {
                info.SetDeviceClass(Camera_t::DeviceClass());
                camera.Attach(CTlFactory::GetInstance().CreateFirstDevice(info));
                camera.Open();
                camera.PixelFormat.SetValue(PixelFormat_YUV422Packed);
                camera.Width.SetValue(cols);
                camera.Height.SetValue(rows);
                //cout << "Using device " << camera.GetDeviceInfo().GetModelName() << endl;
                camera.MaxNumBuffer = 25;//(int) fs["max_num_buffer_basler"]; //25;
                camera.GainAuto.SetValue(GainAuto_Continuous);
                camera.GainSelector.SetValue(GainSelector_AnalogAll);
                camera.GainRaw.SetValue(0);
                camera.Gamma.SetValue(1);
                camera.DigitalShift.SetValue(0);
                camera.ColorTransformationSelector.SetValue(ColorTransformationSelector_RGBtoRGB);
                camera.LightSourceSelector.SetValue(LightSourceSelector_Daylight6500K);
                camera.BalanceRatioSelector.SetValue(BalanceRatioSelector_Blue);
                camera.BalanceRatioAbs.SetValue(1.375);
                camera.BalanceRatioRaw.SetValue(88);
                camera.ColorTransformationMatrixFactor.SetValue(1);
                camera.ColorTransformationMatrixFactorRaw.SetValue(65536);
                camera.ExposureTimeAbs.SetValue(1500);
                camera.ExposureTimeRaw.SetValue(1500);
                camera.AcquisitionFrameRateAbs.SetValue(50);
                camera.StartGrabbing(c_countOfImagesToGrab);
            }
            errmsg = "Using device " + camera.GetDeviceInfo().GetModelName();
            return true;
        }
        catch (GenICam::GenericException &e)
        {
            // Error handling.
            errmsg = e.GetDescription();
            return false;
        }
    }
    else if (deviceName == "ids")
    {
        return false;
        HIDS cam = camid;
        int nRet = is_InitCamera(&cam, 0);
        if (nRet == IS_SUCCESS)
        {
            m_hCam = cam;
            nRet = is_GetSensorInfo(m_hCam, &m_SensorInfo);

            cout<< "using device IDS UI-5240CP-C-HQ" << endl;
            errmsg = "using device IDS UI-5240CP-C-HQ";

            // Allocate the memory to buffer;
            // first free the previous allocated memory
            if(m_pMemBuffer != NULL && m_nMemID != 0)
            {
                nRet = is_FreeImageMem(m_hCam, m_pMemBuffer, m_nMemID);
                m_pMemBuffer = 0;
                m_nMemID = 0;
            }
            nRet = is_AllocImageMem(m_hCam, m_SensorInfo.nMaxWidth, m_SensorInfo.nMaxHeight, 24,
                                    &m_pMemBuffer, &m_nMemID);
            nRet = is_SetImageMem(m_hCam, m_pMemBuffer, m_nMemID);

            // Set the BGR8 capturing mode
            nRet = is_SetColorMode(m_hCam, IS_CM_BGR8_PACKED);

             // to do the top-left and top-bottom mirror
            //is_SetRopEffect (m_hCam, IS_SET_ROP_MIRROR_UPDOWN, true, 0);
            //is_SetRopEffect (m_hCam, IS_SET_ROP_MIRROR_LEFTRIGHT, true, 0);

            cout<< "Memory Allocation Done \n";
            is_CaptureVideo(m_hCam, IS_DONT_WAIT);
            return true;
        }
        else if (nRet == IS_DEVICE_ALREADY_PAIRED)
        {
            return false;
            // Do nothing
            return true;
        }
        else
        {
            //cout << "Error code - " << nRet << endl;
            cout<< "Fail to open camera IDS UI-5240CP-C-HQ - Check if it is connected" << endl;
            errmsg = "Fail to open camera IDS UI-5240CP-C-HQ - Check if it is connected";
            //fs.release();
            return false;
        }
    }
    return true;
}

void auxCamRecord_producer::evaluate()
{
    m_eval = true;
}

void auxCamRecord_producer::abort()
{
    m_abort = true;
}

cv::Rect auxCamRecord_producer::rect(const QRect &r)
{
    return cv::Rect(r.x(), r.y(), r.width(), r.height());
}

string auxCamRecord_producer::getState(const cv::Mat &current_frame)
{
    Mat diff_hsv, mask_out;
    Mat channel[3];
    cv::Mat p = current_frame.clone();
    cv::medianBlur(p, p, 3);
    cvtColor(p, diff_hsv, CV_BGR2HSV);
    split(diff_hsv, channel);
    cv::threshold(channel[0], mask_out, thresh_ring, 255, THRESH_TOZERO_INV); //b1((b1 >= T))= 0;
    cv::threshold(mask_out, mask_out, 1, 255, THRESH_BINARY); //b1((b1 > 0))= 255;
    erode(mask_out, mask_out, element[2]);
    dilate(mask_out, mask_out, element[0]);
    erode(mask_out, mask_out, element[2]);
    dilate(mask_out, mask_out, element[0]);
    if(indexSet)
    {
        indexSet = false;
        for(int i = 0; i < pegRectBoxSmall.size(); i++)
        {
            cv::Mat p = mask_out(rect(pegRectBoxSmall[i]));
            //cv::Mat p1 = mask_out(rect(pegRectBoxBig[i]));
            double s = cv::sum(p)[0];
            //double s1 = cv::sum(p1)[0];
            //qDebug() << "sum at small "  << i+1 << " is " << s;
            //qDebug() << "sum at big "  << i+1 << " is " << s1;
            if(s > THRESH_RING_SEGMENT_ON) // put the threshold
            {
                old_index = i+1;
                break;
            }
        }
        if(old_index == -1)
        {
            status = "moving";
        }
        else
        {
            status = "stationary";
            if(old_index == current_index)
            {
                do
                {
                    current_index =  (rand() % (int)(No_pegs)) + 1;
                }while(old_index == current_index);
            }
        }
        changeLEDIndex(current_index);
    }
    qDebug() << "old_index " << old_index << " current_index " << current_index << " status " << QString::fromStdString(status) << endl;
    if(old_index != -1)
    {
        double sum_oldIndex_small = cv::sum(mask_out(rect(pegRectBoxSmall[old_index-1])))[0];
        double sum_oldIndex_big = cv::sum(mask_out(rect(pegRectBoxBig[old_index-1])))[0];
        double sum_currentIndex_small = cv::sum(mask_out(rect(pegRectBoxSmall[current_index -1])))[0];
        //double sum_currentIndex_big = mask_out(rect(pegRectBoxBig[current_index-1]));
        if(status == "stationary")
        {
            if(sum_oldIndex_small > THRESH_RING_SEGMENT_ON)
            {
                status = "stationary";
            }
            else if (sum_oldIndex_small < THRESH_RING_SEGMENT_OFF)
            {
                status = "picking";
            }
        }
        else if (status == "picking")
        {
            if(sum_oldIndex_big > THRESH_PICKING_TO_PICKING)
            {
                status = "picking";
            }
            else if (sum_oldIndex_big < THRESH_PICKING_TO_MOVING)
            {
                status = "moving";
            }
        }
        else if(status == "moving")
        {
            if(sum_currentIndex_small > THRESH_RING_SEGMENT_ON)
            {
                stable_count++;
            }
            if(stable_count > STABLE_COUNT)
            {
                stable_count = 0;
                status = "stationary";
                old_index = current_index;
                current_index =  (rand() % (int)(No_pegs)) + 1;
                if(old_index == current_index)
                {
                    do
                    {
                        current_index =  (rand() % (int)(No_pegs)) + 1;
                    }while(old_index == current_index);
                }
                changeLEDIndex(current_index);
            }
            else
            {
                status = "moving";
            }
        }
    }
    else
    {
        double sum_currentIndex_small = cv::sum(mask_out(rect(pegRectBoxSmall[current_index -1])))[0];
        if(sum_currentIndex_small > 10000)
        {
            stable_count++;
        }
        if(stable_count > STABLE_COUNT)
        {
            stable_count = 0;
            status = "stationary";
            old_index = current_index;
            current_index =  (rand() % (int)(No_pegs)) + 1;
            if(old_index == current_index)
            {
                do
                {
                    current_index =  (rand() % (int)(No_pegs)) + 1;
                }while(old_index == current_index);
            }
            changeLEDIndex(current_index);
        }
        else
        {
            status = "moving";
            changeLEDIndex(current_index);
        }
    }
    return status;
}

void auxCamRecord_producer::processFrame(const cv::Mat &current_frame)
{
    getState(current_frame);
    if(m_eval)
    {
        // lgogging info
        track(current_frame);


        //Rect pp = blobTrack(current_frame);
        Mat aa = current_frame.clone();
        if(currBB != NULL)
        {
            rectangle(aa, *currBB, Scalar(255,0,0), 2);
        }


        if(sendFrame)
            emit sendtoUI(aa);

        if(currBB != NULL)
        {
            trackingData.push_back(make_pair(currentDateTime(), make_pair(currBB->x + ((double)currBB->width/2.0), currBB->y + ((double)currBB->height/2.0))));
            sendTrackingStatus("Tracking active: Status -> " + QString::fromStdString(status) + " ");
        }
        else
        {
            trackingData.push_back(make_pair(currentDateTime(), make_pair(-1, -1)));
            sendTrackingStatus("Tracking LOST : Status -> " + QString::fromStdString(status) + " ");
        }


        if(status == "stationary")
        {
            stateInfo.push_back(make_pair(make_pair(currentDateTime(), ++countFrame), "St:S"));
        }
        else if(status == "picking")
        {
            QString v = "St:P," + QString::number(old_index);
            stateInfo.push_back(make_pair(make_pair(currentDateTime(), ++countFrame), v.toStdString()));
        }
        else if(status == "moving")
        {
            QString v = "St:M," + QString::number(old_index) + "," + QString::number(current_index);
            stateInfo.push_back(make_pair(make_pair(currentDateTime(), ++countFrame), v.toStdString()));
        }
        // get the hitting info
        // get the tugging info
    }
}

void auxCamRecord_producer::process()
{
    //std::vector<unsigned char> temp_rgb(size_1_rgb);
    std::vector<Mat> vec_frame_ax_rgb(size_bin_aux);
    Mat img3u = Mat::zeros(rows, cols, CV_8UC3);
    //Mat img3u_prv = Mat::zeros(rows, cols, CV_8UC3);
    unsigned char* color = img3u.ptr<unsigned char>(0);

    char *lastBuffer;
    INT nRet;
    while(!m_abort)
    {
        if(deviceName == "basler")
        {
            if(!camera.IsGrabbing()) break;
            //cout << "Grabbing Start Producer\n";
            for (uint i = 0 ; i < size_bin_aux; ++i)
            {
                //cout << "Going to trigger camera\n";
                camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);
                if(ptrGrabResult->GrabSucceeded())
                {
                    //cout << "Grab succeed\n";
                    const uchar *pImageBuffer = (uchar *)ptrGrabResult->GetBuffer();
                    // conversion from yuv to rgb;
                    for(unsigned int k = 0, p = 0; k < size_1_yuv; k = k + 4, p = p + 6)
                    {
                        int zero = 0; int max_1 = 255;
                        float Cr = static_cast<float>(static_cast<unsigned int>(pImageBuffer[k]));
                        float Y0 = static_cast<float>(static_cast<unsigned int>(pImageBuffer[k + 1]));
                        float Cb = static_cast<float>(static_cast<unsigned int>(pImageBuffer[k + 2]));
                        float Y1 = static_cast<float>(static_cast<unsigned int>(pImageBuffer[k + 3]));
                        uint8_t r1 = (uint8_t)max(zero, min(max_1, static_cast<int>((Y0)+1.403f*(Cb - 128))));
                        uint8_t g1 = (uint8_t)max(zero, min(max_1, static_cast<int>((Y0)-0.344f*(Cr - 128) - 0.714f*(Cb - 128))));
                        uint8_t b1 = (uint8_t)max(zero, min(max_1, static_cast<int>((Y0)+1.773f*(Cr - 128))));
                        uint8_t r2 = (uint8_t)max(zero, min(max_1, static_cast<int>((Y1)+1.403f*(Cb - 128))));
                        uint8_t g2 = (uint8_t)max(zero, min(max_1, static_cast<int>((Y1)-0.344f*(Cr - 128) - 0.714f*(Cb - 128))));
                        uint8_t b2 = (uint8_t)max(zero, min(max_1, static_cast<int>((Y1)+1.773f*(Cr - 128))));
                        //temp_rgb[p] = b1; temp_rgb[p + 1] = g1; temp_rgb[p + 2] = r1;
                        //temp_rgb[p + 3] = b2; temp_rgb[p + 4] = g2; temp_rgb[p + 5] = r2;
                        color[p] = b1; color[p + 1] = g1; color[p + 2] = r1;
                        color[p + 3] = b2; color[p + 4] = g2; color[p + 5] = r2;
                    }
                    //cout << "conversion complete\n";
                    //std::copy ( temp_rgb.begin(), temp_rgb.begin() + (size_1_rgb), vec_frame_ax_rgb.begin() + ((i) * (size_1_rgb)));
                    vec_frame_ax_rgb[i] = img3u;
                    usleep(10);
                    processFrame(img3u);
                    //if(sendFrame)
                    //    emit sendtoUI(img3u);
                }
                else
                {
                    cout << "Auxillary Camera->Error: " << ptrGrabResult->GetErrorCode() << " " << ptrGrabResult->GetErrorDescription() << endl;
                    exit(1);
                }
                //cout << "Putting data in temp rgb\n";
            }
        }
        else if(deviceName == "ids")
        {
            if(m_hCam == 0) break;
            for(uint i = 0; i < size_bin_aux; ++i)
            {
                nRet = is_GetActSeqBuf(m_hCam, 0, 0, &lastBuffer);
                if (nRet == IS_SUCCESS)
                {
                    //std::copy ( lastBuffer, lastBuffer + (size_1_rgb), vec_frame_ax_rgb.begin() + ((i) * (size_1_rgb)));
                }
                else
                {
                    cout << "Getting the frame error ... exiting \n";
                    exit(1);
                }
            }
        }
        // Lock the Buffer, and put frame in buffer
        //cout << "Going to lock\n";
        if(m_grab)
        {
            buf_aux::instance(parameters)->mutex.lock();
            while(buf_aux::instance(parameters)->getFull())
            {
                //cout<<"Auxilary->Producer Full \n";
                buf_aux::instance(parameters)->notFull.wait(&buf_aux::instance(parameters)->mutex);
            }
            //printf("Aux->P%d\n", buf_aux::instance()->getTail());
            buf_aux::instance(parameters)->setBuffer(vec_frame_ax_rgb);
            buf_aux::instance(parameters)->mutex.unlock();
            buf_aux::instance(parameters)->notEmpty.wakeOne();
            usleep(10);
        }
    }
    cout << "Out of Auxillary Producer\n";
    if(deviceName == "basler")
    {
        if(camera.IsOpen())
            camera.Close();
    }
    else if(deviceName == "ids")
    {
        if(m_hCam != 0)
        {
            //Disable messages
            is_EnableMessage(m_hCam, IS_FRAME, NULL);

            // stop live video
            is_StopLiveVideo(m_hCam, IS_WAIT);

            if(m_pMemBuffer != NULL)
            {
                is_FreeImageMem(m_hCam, m_pMemBuffer, m_nMemID);
            }
            m_pMemBuffer = NULL;

            //close the camera
            is_ExitCamera(m_hCam);
            //cout << "Error code of Exiting the camera Process Producer - " << pp <<endl;
            m_hCam = 0;
        }
    }
    //emit sendEvalData(trackingData);
    emit finished();
}


// consumer functuions
auxCamRecord_consumer::auxCamRecord_consumer()
{
}

auxCamRecord_consumer::~auxCamRecord_consumer()
{
}

void auxCamRecord_consumer::initialize(const params &par, const string &name)
{
    parameters = par;
    // getting the first path
    capturePath = name;
    rows = par.cap_rowsAux;
    cols = par.cap_colsAux;
    size_bin_aux = par.cap_binSize;
    n_channels = 3;
    size_1_rgb = rows * cols * n_channels;
    no_of_frames = 0;
    timestamp_aux.clear();
    startdumping = false;
    m_grab = false;
    m_abort = false;
    videoFullpath = name;
}

void auxCamRecord_consumer::abort()
{
    m_abort = true;
}

void auxCamRecord_consumer::startGrabbing()
{
    m_grab = true;
}

const string auxCamRecord_consumer::currentDateTime()
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



const string auxCamRecord_consumer::num2str(int num)
{
    string str;
    str = dynamic_cast< std::ostringstream & >(( std::ostringstream() << std::dec << num ) ).str();
    return str;
}

void auxCamRecord_consumer::process()
{
    while(!m_abort)
    {
        if (m_grab)
        {
            std::vector<Mat> vec_frame_consume;
            buf_aux::instance(parameters)->mutex.lock();
            while (buf_aux::instance(parameters)->getEmpty())
            {
                //cout << "Endoscopy-> Consumer: queue EMPTY.\n";
                buf_aux::instance(parameters)->notEmpty.wait(&buf_aux::instance(parameters)->mutex);
            }
            //printf("Endo->C%d\n", buf_endo::instance()->getHead());
            buf_aux::instance(parameters)->getBuffer(vec_frame_consume);
            buf_aux::instance(parameters)->mutex.unlock();
            buf_aux::instance(parameters)->notFull.wakeOne();
            if(!vec_frame_consume.empty())
            {
                for(int i = 0; i < size_bin_aux; i++)
                {
                    if(!startdumping)
                    {
                        cout << "started dumping aux\n";
                        cout << "capture path aux-> " << videoFullpath << endl;
                        videoWriter.open(videoFullpath.c_str(), CV_FOURCC('F','M','P','4'), 25, Size(cols, rows), true);
                        startdumping = true;
                    }
                    videoWriter.write(vec_frame_consume[i]);
                    timestamp_aux.push_back("Aux " + num2str(++no_of_frames) + " " + currentDateTime() );
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
    cout << "No of frames produced (Auxiliary)-> " << no_of_frames<< endl;
    no_of_frames = 0;
    videoWriter.release();
    emit finished();
}
