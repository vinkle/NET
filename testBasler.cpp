#include "testBasler.h"
//12-12-12
testBasler::testBasler()
{
}
testBasler::~testBasler()
{
    camera.Close();
}

bool testBasler::initialize(params &param, string &errmsg)
{
    c_countOfImagesToGrab = 180000;//(int) fs["countOfImagesToGrab"];
    frame_rate = 25; //(int) fs["frame_rate_basler"]; //25;
    bool retVal = false;
    m_abort = false;
    m_start = false;
    m_pause = false;
    try
    {
        if(!camera.IsOpen())
        {
            info.SetDeviceClass(Camera_t::DeviceClass());
            camera.Attach(CTlFactory::GetInstance().CreateFirstDevice(info));
            camera.Open();
            camera.PixelFormat.SetValue(PixelFormat_YUV422Packed);
            camera.AcquisitionFrameRateAbs.SetValue(frame_rate);


            camera.MaxNumBuffer = 10; //(int) fs["max_num_buffer_basler"]; //25;
            camera.StartGrabbing(c_countOfImagesToGrab);
            camera.RetrieveResult( 5000, ptrGrabResult, TimeoutHandling_ThrowException);

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

            cout << "basler width ->" << ptrGrabResult->GetWidth();
            cout << "basler height ->" << ptrGrabResult->GetHeight();
            param.cap_colsAux = ptrGrabResult->GetWidth();
            param.cap_rowsAux = ptrGrabResult->GetHeight();
            rows = param.cap_rowsAux; // (int) fs["rows_Basler"]; // 1024 / divider;
            cols = param.cap_colsAux;
            n_channels = 3;
            size_1_rgb = rows * cols * n_channels;
            size_1_yuv = rows * cols * 2;
        }
        errmsg = "Using device " + camera.GetDeviceInfo().GetModelName();
        retVal = true;
    }
    catch (GenICam::GenericException &e)
    {
        // Error handling.
        errmsg = e.GetDescription();
        retVal = false;
    }
    return retVal;
}

void testBasler::process()
{
    std::vector<unsigned char> temp_rgb(size_1_rgb);
    Mat img3u = Mat::zeros(rows, cols, CV_8UC3);
    //Mat img3u_disp = Mat::zeros(280, 350, CV_8UC3);
    while(!m_abort)
    {
        if(m_start)
        {
            if(!camera.IsGrabbing()) break;
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
                    temp_rgb[p] = r1; temp_rgb[p + 1] = g1; temp_rgb[p + 2] = b1;
                    temp_rgb[p + 3] = r2; temp_rgb[p + 4] = g2; temp_rgb[p + 5] = b2;
                }
//                cout << "conversion complete\n";
                  unsigned char* color = img3u.ptr<unsigned char>(0);
                  std::copy (temp_rgb.begin(), temp_rgb.begin() + size_1_rgb, color);
//                resize(img3u, img3u_disp, img3u_disp.size());
//                //cv::flip( img3u,img3u, 0);
//                QImage qimg((uchar*)img3u_disp.data, 350, 280, img3u_disp.step, QImage::Format_RGB888);
                  if(!m_pause)
                    emit sendtoUI(img3u);


            }
            else
            {
                cout << "Auxillary Camera->Error: " << ptrGrabResult->GetErrorCode() << " " << ptrGrabResult->GetErrorDescription() << endl;
                exit(1);
            }
        }
        usleep(1000);
    }
    if(camera.IsOpen())
        camera.Close();
    emit finished();
}
