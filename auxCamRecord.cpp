#include "auxCamRecord.h"

auxCamRecord_producer::auxCamRecord_producer()
{
    sendFrame = false;
    old_index = -1;
    current_index =  4;//(rand() % (int)(No_pegs)) + 1;
    //current_index = 7;
    element[0] = getStructuringElement(MORPH_ELLIPSE, Size(3, 3), Point(0, 0));
    element[1] = getStructuringElement(MORPH_ELLIPSE, Size(5, 5), Point(0, 0));
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
    thresh = 50;
    ledIndexCount = 0;
    kernel = (Mat_<uchar>(3, 3) << 0, 1, 0, 1, 1, 1, 0, 1, 0);
    nextLEDindexVector.resize(25);
    nextLEDindexVector[0] = 1;
    nextLEDindexVector[1] = 2;
    nextLEDindexVector[2] = 6;
    nextLEDindexVector[3] = 8;
    nextLEDindexVector[4] = 12;
    nextLEDindexVector[5] = 11;
    nextLEDindexVector[6] = 3;
    nextLEDindexVector[7] = 9;
    nextLEDindexVector[8] = 4;
    nextLEDindexVector[9] = 11;
    nextLEDindexVector[10] = 1;
    nextLEDindexVector[11] = 9;
    nextLEDindexVector[12] = 12;
    nextLEDindexVector[13] = 4;
    nextLEDindexVector[14] = 1;
    nextLEDindexVector[15] = 12;
    nextLEDindexVector[16] = 9;
    nextLEDindexVector[17] = 4;
    nextLEDindexVector[18] = 12;
    nextLEDindexVector[19] = 11;
    nextLEDindexVector[20] = 3;
    nextLEDindexVector[21] = 6;
    nextLEDindexVector[22] = 11;
    nextLEDindexVector[23] = 8;
    nextLEDindexVector[24] = 4;
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

    img3u = Mat::zeros(rows/2, cols/2, CV_8UC3);
    img3u_prv = Mat::zeros(rows/2, cols/2, CV_8UC3);
    smallImage_width = int(boundingRectangle.width() / 10.0);
    smallImage_height = int(boundingRectangle.height() / 10.0);
    // vars declaration
    smallSize = cv::Size(smallImage_width, smallImage_height);

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
                camera.ExposureTimeAbs.SetValue(1000);
                camera.ExposureTimeRaw.SetValue(1000);
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
//            if(old_index == current_index)
//            {
//                do
//                {
//                    current_index =  nextLEDindexVector[ledIndexCount++];
//                }while(old_index == current_index);
//            }
        }
        changeLEDIndex(current_index);
        usleep(10000);
        changeLEDIndex(current_index);
    }
    qDebug() << "old_index " << old_index << " current_index " << current_index << " status " << QString::fromStdString(status) << endl;
    if(old_index != -1)
    {
        double sum_oldIndex_small = cv::sum(mask_out(rect(pegRectBoxSmall[old_index-1])))[0];
        double sum_oldIndex_big = cv::sum(mask_out(rect(pegRectBoxBig[old_index-1])))[0];
        double sum_currentIndex_small = cv::sum(mask_out(rect(pegRectBoxSmall[current_index -1])))[0];
        //double sum_currentIndex_big = mask_out(rect(pegRectBoxBig[current_index-1]));
        qDebug() << "old_index_sum_small " << sum_oldIndex_small << "old_index_sum_big" << sum_oldIndex_big << "sum_currentindex_small" << sum_currentIndex_small << endl;
        Mat temp = mask_out(rect(pegRectBoxBig[current_index-1]));
        if(sendFrame)
            emit sendtoUI(temp);
        usleep(20);

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
                //current_index =  (rand() % (int)(No_pegs)) + 1;
                current_index =  nextLEDindexVector[ledIndexCount++];
                if(ledIndexCount == 24)
                {
                    ledIndexCount = 0;
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
            //current_index =  (rand() % (int)(No_pegs)) + 1;
            current_index =  nextLEDindexVector[ledIndexCount++];
            if(ledIndexCount == 24)
            {
                ledIndexCount = 0;
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

int auxCamRecord_producer::hittingDetection(const cv::Mat &prv_frame, const cv::Mat &current_frame)
{
    vector<unsigned int> hittingData;
    cv::absdiff(prv_frame, current_frame, diff);
    diff = diff(rect(boundingRectangle));
    // cout << "diff size->" << diff.size() << endl;
    // edge detection and normalization
    cv::Canny(diff, canny_output, thresh, thresh * 4, 3);
    cv::normalize(canny_output, canny_output, 0, 1, cv::NORM_MINMAX);
    cv::dilate(canny_output, dst, kernel);
    cv::dilate(dst, dst, kernel);
    cv::normalize(dst, dst, 0, 255, cv::NORM_MINMAX);

//    if(sendFrame)
//        emit sendtoUI(dst);
//    usleep(20);
    hittingData.clear();
    for (int y = 0; y < dst.rows - smallSize.height + 1; y += smallSize.height)
    {
        for (int x = 0; x < dst.cols - smallSize.width + 1; x += smallSize.width)
        {
            cv::Rect rect = cv::Rect(x, y, smallSize.width, smallSize.height);
            Mat temp = dst(rect);
            findContours(temp, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
            if (contours.size())
            {
                hittingData.push_back(contours.size());
            }
        }
    }
//   qDebug() << "Hitting Intensity -> " << hittingData.size() << endl;;
//   qDebug() << "hittingData size -> " << hittingData.size() << endl;;
//    if(sendFrame)
//        emit sendtoUI(dst);
//    usleep(20);

    return hittingData.size();
}

void auxCamRecord_producer::tuggingDetection(const cv::Mat &current_frame, vector<vector<Point> > &contours_tug)
{
    Mat diff_hsv, mask_out;
    Mat channel[3];
    cv::Mat ringSeg = current_frame.clone();
    //ringSeg = ringSeg(rect(boundingRectangle));

    cv::medianBlur(ringSeg, ringSeg, 3);
    cvtColor(ringSeg, diff_hsv, CV_BGR2HSV);
    split(diff_hsv, channel);
    cv::threshold(channel[0], mask_out, thresh_ring, 255, THRESH_TOZERO_INV); //b1((b1 >= T))= 0;
    cv::threshold(mask_out, mask_out, 1, 255, THRESH_BINARY); //b1((b1 > 0))= 255;
    erode(mask_out, mask_out, element[2]);
    dilate(mask_out, mask_out, element[0]);
    erode(mask_out, mask_out, element[2]);
    dilate(mask_out, mask_out, element[1]);
    findContours(mask_out, contours_tug, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
//    qDebug() << "Contours ..";
//    for(int i = 0; i < contours_tug.size(); ++i)
//    {
//        qDebug() << contours_tug[i].size() << " ; ";
//    }
//    qDebug() << "\n";
//    if(sendFrame)
//        emit sendtoUI(ringSeg);
//    usleep(20);
}

void auxCamRecord_producer::processFrame(const cv::Mat &prv_frame, const cv::Mat &current_frame)
{
    stat.clear();
    getState(current_frame);
    if(m_eval)
    {
        // invoke hitting subroutine
        int hittingOut = hittingDetection(prv_frame, current_frame);

        // invoke tracking subroutine
        Rect trackOut = blobTrack(current_frame);

        // invoke tugging routine
        contours_tug.clear();
        tuggingDetection(current_frame, contours_tug);

//        Mat aa = current_frame.clone();
//        for(int i = 0; i < pegRectBoxSmall.size(); i++)
//        {
//            cv::rectangle(aa, rect(pegRectBoxSmall[i]),Scalar(0,255,0),1);
//        }
//        if(sendFrame)
//            emit sendtoUI(aa);
//        usleep(20);

        // get the current datetime
        string dt = currentDateTime();
        // save tracking
        if(trackOut.width != -1)
        {
            trackingData.push_back(make_pair(dt, make_pair(((trackOut.x + ((double)trackOut.width/2.0)) / (cols/2.0)), ((trackOut.y + ((double)trackOut.height/2.0)) / (rows/2.0)) )));
            stat = "Tracking active: Status -> " + QString::fromStdString(status) + " ";
        }
        else
        {
            trackingData.push_back(make_pair(dt, make_pair(-1, -1)));
            stat = "Tracking LOST : Status -> " + QString::fromStdString(status) + " ";
        }

        // save hitting
        if(hittingOut > HITTING_THRESHOLD)
        {
            hittingData_fdiff.push_back(make_pair(dt, hittingOut));
            stat += "Hitting Detected ";
        }
        // save tugging
        tuggingData.push_back(make_pair(dt, contours_tug));
        // save current status
        if(status == "stationary")
        {
            stateInfo.push_back(make_pair(make_pair(dt, ++countFrame), "St:S"));
        }
        else if(status == "picking")
        {
            QString v = "St:P," + QString::number(old_index);
            stateInfo.push_back(make_pair(make_pair(dt, ++countFrame), v.toStdString()));
        }
        else if(status == "moving")
        {
            QString v = "St:M," + QString::number(old_index) + "," + QString::number(current_index);
            stateInfo.push_back(make_pair(make_pair(dt, ++countFrame), v.toStdString()));
        }
        sendTrackingStatus(stat);
    }
}

void auxCamRecord_producer::process()
{
    //std::vector<unsigned char> temp_rgb(size_1_rgb);
    std::vector<Mat> vec_frame_ax_rgb(size_bin_aux);
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
                    const uchar *pImageBuffer = (uchar *)ptrGrabResult->GetBuffer();
                    unsigned int eff_yuv_width = cols*2;
                    unsigned int eff_rgb_width = (cols/2)*3;
                    for(unsigned int d = 0, dd = 0; d < rows - 1; dd = dd + 1, d = d + 2)
                    {
                        for(unsigned int k = 0, p = 0; k < eff_yuv_width; k = k + 4, p = p + 3)
                        {
                            int zero = 0; int max_1 = 255;
                            float Cr = static_cast<float>(static_cast<unsigned int>(pImageBuffer[(d * eff_yuv_width) + (k)]));
                            float Y0 = static_cast<float>(static_cast<unsigned int>(pImageBuffer[(d * eff_yuv_width) + (k + 1)]));
                            float Cb = static_cast<float>(static_cast<unsigned int>(pImageBuffer[(d * eff_yuv_width) + (k + 2)]));
                            float Y1 = static_cast<float>(static_cast<unsigned int>(pImageBuffer[(d * eff_yuv_width) + (k + 3)]));
                            float Cr_1 = static_cast<float>(static_cast<unsigned int>(pImageBuffer[((d+1) * eff_yuv_width) + (k)]));
                            float Y0_1 = static_cast<float>(static_cast<unsigned int>(pImageBuffer[((d+1) * eff_yuv_width) + (k + 1)]));
                            float Cb_1 = static_cast<float>(static_cast<unsigned int>(pImageBuffer[((d+1) * eff_yuv_width) + (k + 2)]));
                            float Y1_1 = static_cast<float>(static_cast<unsigned int>(pImageBuffer[((d+1) * eff_yuv_width) + (k + 3)]));
                            float rr1 = (Y0)+1.403f*(Cb - 128);
                            float gg1 = (Y0)-0.344f*(Cr - 128) - 0.714f*(Cb - 128);
                            float bb1 = (Y0)+1.773f*(Cr - 128);
                            float rr2 = (Y1)+1.403f*(Cb - 128);
                            float gg2 = (Y1)-0.344f*(Cr - 128) - 0.714f*(Cb - 128);
                            float bb2 = (Y1)+1.773f*(Cr - 128);
                            float rr3 = (Y0_1)+1.403f*(Cb_1 - 128);
                            float gg3 = (Y0_1)-0.344f*(Cr_1 - 128) - 0.714f*(Cb_1 - 128);
                            float bb3 = (Y0_1)+1.773f*(Cr_1 - 128);
                            float rr4 = (Y1_1)+1.403f*(Cb_1 - 128);
                            float gg4 = (Y1_1)-0.344f*(Cr_1 - 128) - 0.714f*(Cb_1 - 128);
                            float bb4 = (Y1_1)+1.773f*(Cr_1 - 128);
                            float rr = (rr1 + rr2 + rr3 + rr4) / 4.0;
                            float gg = (gg1 + gg2 + gg3 + gg4) / 4.0;
                            float bb = (bb1 + bb2 + bb3 + bb4) / 4.0;
                            uint8_t r = (uint8_t)max(zero, min(max_1, static_cast<int>(rr)));
                            uint8_t g = (uint8_t)max(zero, min(max_1, static_cast<int>(gg)));
                            uint8_t b = (uint8_t)max(zero, min(max_1, static_cast<int>(bb)));
                            color[(dd * eff_rgb_width) + (p)] = b;
                            color[(dd * eff_rgb_width) + (p + 1)] = g;
                            color[(dd * eff_rgb_width)+ (p + 2)] = r;
                        }
                    }
//                    if(sendFrame)
//                        emit sendtoUI(img3u);
//                    usleep(20);
//                    trackingTimer.start();
                    processFrame(img3u_prv, img3u);
//                    int nMilliseconds = trackingTimer.elapsed();
//                    qDebug() << "Elapsed time per frame ->" << nMilliseconds << endl;

                    img3u.copyTo(img3u_prv);
                    vec_frame_ax_rgb[i] = img3u;

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
                        videoWriter.open(videoFullpath.c_str(), CV_FOURCC('F','M','P','4'), 25, Size(cols/2, rows/2), true);
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
