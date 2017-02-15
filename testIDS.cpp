#include "testIDS.h"
//12-12-12
testIDS::testIDS()
{
    m_hCam = 0;
    m_pMemBuffer = NULL;
    m_nMemID = 0;
    m_abort = false;
    m_start = false;
}
testIDS::~testIDS()
{
    if( m_hCam != 0 )
    {
        // Disable messages
        is_EnableMessage( m_hCam, IS_FRAME, NULL );
        // Stop live video
        is_StopLiveVideo( m_hCam, IS_WAIT );
        // Free the allocated buffer
        if( m_pMemBuffer != NULL )
            is_FreeImageMem( m_hCam, m_pMemBuffer, m_nMemID );
        m_pMemBuffer = NULL;
        // Close camera
        is_ExitCamera( m_hCam );
        m_hCam = NULL;
    }
}
bool testIDS::initialize(params &param, string &errmsg)
{
    camid = param.cap_camID_IDS;//(int) fs["camID_ids"];
    rows = param.cap_rowsAux;//(int) fs["rows_ids"]; // 1024 / divider;
    cols = param.cap_colsAux;//(int) fs["cols_ids"]; // 1280 / divider;
    n_channels = 3;
    size_1_rgb = rows * cols * n_channels;
    size_1_yuv = rows * cols * 2;
    bool retval = false;
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
        nRet = is_AllocImageMem(m_hCam, m_SensorInfo.nMaxWidth, m_SensorInfo.nMaxHeight, 24, &m_pMemBuffer, &m_nMemID);
        nRet = is_SetImageMem(m_hCam, m_pMemBuffer, m_nMemID);

        // Set the BGR8 capturing mode
        nRet = is_SetColorMode(m_hCam, IS_CM_BGR8_PACKED);


        // to do the top-left and top-bottom mirror
        //is_SetRopEffect (m_hCam, IS_SET_ROP_MIRROR_UPDOWN, true, 0);
        //is_SetRopEffect (m_hCam, IS_SET_ROP_MIRROR_LEFTRIGHT, true, 0);


        cout<< "Memory Allocation Done \n";
        is_CaptureVideo(m_hCam, IS_DONT_WAIT);
        retval =  true;
    }
    else if (nRet == IS_DEVICE_ALREADY_PAIRED)
    {
        // Do nothing
        retval =  true;
    }
    else
    {
        //cout << "Error code - " << nRet << endl;
        cout<< "Fail to open camera IDS UI-5240CP-C-HQ - Check if it is connected" << endl;
        errmsg = "Fail to open camera IDS UI-5240CP-C-HQ - Check if it is connected";
        retval =  false;
    }
    return retval;  
}


void testIDS::process()
{
    //std::vector<unsigned char> temp_rgb(size_1_rgb);
    std::vector<unsigned char> vec_frame(size_1_rgb);
   	Mat img3u = Mat::zeros(rows, cols, CV_8UC3);
    Mat img3u_disp = Mat::zeros(280, 350, CV_8UC3);
    char *lastBuffer;
    INT nRet;
    while(!m_abort)
    {
        if(m_start)
        {
            if(m_hCam == 0) break;
            nRet = is_GetActSeqBuf(m_hCam, 0, 0, &lastBuffer);
            if (nRet == IS_SUCCESS)
            {
                std::copy (lastBuffer, lastBuffer + (size_1_rgb), vec_frame.begin());
            }
            else
            {
                cout << "Getting the frame error ... exiting \n";
                exit(1);
            }
            unsigned char* color = img3u.ptr<unsigned char>(0);
            std::copy (vec_frame.begin(), vec_frame.begin() + size_1_rgb, color);
            //resize(img3u, img3u_disp, img3u_disp.size());
            //QImage qimg((uchar*)img3u_disp.data, 350, 280, img3u_disp.step, QImage::Format_RGB888);
            emit sendtoUI(img3u);
            usleep(1000);
            //cout << "End statement; val of m_abort (prcocess producer IDS) - " << m_abort << endl;
        }
    }
    cout << "Out of Auxillary Producer\n";
    // close the camera
    //cout << "process Producer - mHCam - " << m_hCam << endl;
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
    //cout << "finish the thread -- \n";
    emit finished();
}

