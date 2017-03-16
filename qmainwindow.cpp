#include "qmainwindow.h"
#include "ui_qmainwindow.h"
#include <QCameraInfo>
#include <QtSerialPort/QSerialPortInfo>
//12-12-12

qMainWindow::qMainWindow(/*settings_main &obj, */const params &par, string type, int level, string drName, string camAux,
                         QRect boundingRectangle,
                         QVector<QRect> pegRectBoxSmall, QVector<QRect> pegRectBoxBig,
                         const QSqlDatabase &db,
                         double withoutRing_smallRectThresh, double withoutRing_bigRectThresh,
                         double withRing_smallRectThresh, double withRing_bigRectThresh,
                         string experimentType,
                         string details,
                         bool RecordOnlineEndo, bool RecordOnlineAux, bool FlipVert, bool FlipHorz,
                         int thresh_ring, int thresh_tool,
                         QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qMainWindow),
    /*mSettingMain(&obj),*/
    param(par),
    type(type),
    level(level),
    drName(drName),
    camAux(camAux),
    boundingRectangle(boundingRectangle),
    pegRectBoxSmall(pegRectBoxSmall),
    pegRectBoxBig(pegRectBoxBig),
    endoDB(db),
    withoutRing_smallRectThresh(withoutRing_smallRectThresh),
    withoutRing_bigRectThresh(withoutRing_bigRectThresh),
    withRing_smallRectThresh(withRing_smallRectThresh),
    withRing_bigRectThresh(withRing_bigRectThresh),
    experimentType(experimentType),
    details(details),
    RecordOnlineEndo(RecordOnlineEndo),
    RecordOnlineAux(RecordOnlineAux),
    mFlipVert(FlipVert),
    mFlipHoriz(FlipHorz),
    thresh_ring(thresh_ring),
    thresh_tool(thresh_tool)
    {
        TotalTimeinMs = 3*60*1000;
        sendtoDB = false;
        camState = true;
        // serial port settings and stuff
        serial = new QSerialPort(this);
        openSerialPort();
        usleep(100000);
        connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
        connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
        connect(serial, SIGNAL(readChannelFinished()), this, SLOT(readData()));
        start_serial_logging = false;
        stopProcessing = false;

        ui->setupUi(this);
        // set up the camera and start streaming on the central widget
        mFlipVert=true;
        mFlipHoriz=false;
        switchCam = false;
        if(type == "practice")
        {
            // create auxiliary and endoscopy camera object and stream the endoscopy video
            mProducer_endo = new usbCamRecordDisp_producer();
            mProducer_aux  = new auxCamRecord_producer();

            mThread_endo_producer = new QThread;
            mThread_aux_producer  = new QThread;

            mProducer_endo->moveToThread(mThread_endo_producer);
            mProducer_aux->moveToThread(mThread_aux_producer);

            connect(mThread_endo_producer, SIGNAL(started()), mProducer_endo, SLOT(process()));
            connect(mProducer_endo, SIGNAL(finished()), mThread_endo_producer, SLOT(quit()));

            connect(mThread_aux_producer, SIGNAL(started()), mProducer_aux, SLOT(process()));
            connect(mProducer_aux, SIGNAL(finished()), mThread_aux_producer, SLOT(quit()));
            connect(mProducer_aux, SIGNAL(changeLEDIndex(int)), this, SLOT(LEDindexChange(int)));

            qRegisterMetaType< myMat>("const myMat &");
            connect(mProducer_endo, SIGNAL(sendtoUI(const myMat &)), this, SLOT(updateScreen(const myMat &)), Qt::QueuedConnection);
            connect(mProducer_aux, SIGNAL(sendtoUI(const myMat &)), this, SLOT(updateScreen(const myMat &)), Qt::QueuedConnection);

            bool success = mProducer_endo->initialize(param);
            if(!success)
            {
                ui->statusBar->showMessage("Error initializing endoscopic camera.");
                return;
            }
            string errmsg;
            success = mProducer_aux->initialize(param, errmsg, boundingRectangle,
                                                pegRectBoxSmall, pegRectBoxBig,
                                                withoutRing_smallRectThresh, withoutRing_bigRectThresh,
                                                withRing_smallRectThresh, withRing_bigRectThresh,
                                                thresh_ring, thresh_tool);
            if(!success)
            {
                ui->statusBar->showMessage(QString::fromStdString("Error initializing auxiliary camera ") + QString::fromStdString(errmsg));
                return;
            }
            mThread_endo_producer->start();
            mThread_aux_producer->start();
            usleep(1000);
            ui->statusBar->showMessage("Practice session has started. Follow the Red LED to put the ring. Press exit to return to main menu");
        }
        if(type == "record" || type == "online" )
        {
            // create auxiliary and endoscopy camera object and stream the endoscopy video
            mProducer_endo = new usbCamRecordDisp_producer();
            mConsumer_endo = new usbCamRecordDisp_consumer();
            mProducer_aux  = new auxCamRecord_producer();
            mConsumer_aux  = new auxCamRecord_consumer();


            mThread_endo_producer = new QThread;
            mThread_endo_consumer = new QThread;
            mThread_aux_producer = new QThread;
            mThread_aux_consumer = new QThread;


            mProducer_endo->moveToThread(mThread_endo_producer);
            mConsumer_endo->moveToThread(mThread_endo_consumer);

            mProducer_aux->moveToThread(mThread_aux_producer);
            mConsumer_aux->moveToThread(mThread_aux_consumer);


            connect(mThread_endo_producer, SIGNAL(started()), mProducer_endo, SLOT(process()));
            connect(mProducer_endo, SIGNAL(finished()), mThread_endo_producer, SLOT(quit()));

            connect(mThread_endo_consumer, SIGNAL(started()), mConsumer_endo, SLOT(process()));
            connect(mConsumer_endo, SIGNAL(finished()), mThread_endo_consumer, SLOT(quit()));

            connect(mThread_aux_producer, SIGNAL(started()), mProducer_aux, SLOT(process()));
            connect(mProducer_aux, SIGNAL(finished()), mThread_aux_producer, SLOT(quit()));
            //connect(mProducer_aux, SIGNAL(sendEvalData(vector<pair<string,pair<double, double> > >)), this, SLOT(processEvaluationData(vector<pair<string, pair<double, double> > >)));
            connect(mProducer_aux, SIGNAL(changeLEDIndex(int)), this, SLOT(LEDindexChange(int)));


            connect(mThread_aux_consumer, SIGNAL(started()), mConsumer_aux, SLOT(process()));
            connect(mConsumer_aux, SIGNAL(finished()), mThread_aux_consumer, SLOT(quit()));


            qRegisterMetaType< myMat>("const myMat &");
            connect(mProducer_endo, SIGNAL(sendtoUI(const myMat &)), this, SLOT(updateScreen(const myMat &)), Qt::QueuedConnection);
            connect(mProducer_aux, SIGNAL(sendtoUI(const myMat &)), this, SLOT(updateScreen(const myMat &)), Qt::QueuedConnection);


            bool success = mProducer_endo->initialize(param);
            if(!success)
            {
                ui->statusBar->showMessage("Error initializing endoscopic camera.");
                return;
            }

            QRegExp rx("(\\(|\\))");
            QStringList temp = QString::fromStdString(drName).split(rx);
            emailID = temp[1];
            QString saveDir = QString::fromStdString(param.cap_paths) + "/" + emailID;
            if(!QDir(saveDir).exists())
            {
                QDir().mkdir(saveDir);
            }
            saveDirectory = saveDir.toStdString();
            timestamp = currentDateTime();
            endoFilename =  saveDirectory + "/" + drName + "_" + timestamp + "_level_"+ to_string(level) + "_endo.avi";
            mConsumer_endo->initialize(param, endoFilename);

            string errmsg;
            success = mProducer_aux->initialize(param, errmsg, boundingRectangle,
                                                pegRectBoxSmall, pegRectBoxBig,
                                                withoutRing_smallRectThresh, withoutRing_bigRectThresh,
                                                withRing_smallRectThresh, withRing_bigRectThresh,
                                                thresh_ring, thresh_tool);
            if(!success)
            {
                ui->statusBar->showMessage(QString::fromStdString("Error initializing auxiliary camera ") + QString::fromStdString(errmsg));
                return;
            }

            connect(mProducer_aux, SIGNAL(sendTrackingStatus(const QString &)), this, SLOT(updateStatus(const QString &)));

            auxFilename = saveDirectory + "/" + drName + "_" + timestamp + "_level_"+ to_string(level) +"_aux.avi";
            mConsumer_aux->initialize(param, auxFilename);

            mThread_endo_producer->start();

            if(type == "record" )
            {
                ui->statusBar->showMessage("Press Start to Start the recording; Follow the Red LED to put the ring");
            }
            else if (type == "online" )
            {
                ui->statusBar->showMessage("Press Start to Start your online evaluation. Follow the Red LED to put the ring");
            }
            ui->actionStart_Activity->setEnabled(true);
        }
        m_showResult = new showResult;
        modelResult = new QStandardItemModel;
}

void qMainWindow::updateStatus(const QString & trackingMsg)
{
    QString msg = trackingMsg;
    int currentTimeMS = startTime.elapsed();
    int timeRemain = TotalTimeinMs - currentTimeMS;

    unsigned int h = timeRemain / 1000 / 60 / 60;
    unsigned int m = (timeRemain / 1000 / 60) - (h * 60);
    unsigned int s = (timeRemain / 1000) - ((m + (h * 60))* 60);
    unsigned int ms = timeRemain - (s + ((m + (h * 60))* 60)) * 1000;

    const QString diff = QString("%1:%2:%3,%4")
                            .arg(h,  2, 10, QChar('0'))
                            .arg(m,  2, 10, QChar('0'))
                            .arg(s,  2, 10, QChar('0'))
                            .arg(ms, 3, 10, QChar('0'));
    msg += "       Time Remaining -> " + diff;
    ui->statusBar->showMessage(msg);
    if(timeRemain <= 0 && !stopProcessing)
    {
        sendtoDB = true;
        stopProcessing = true;
        ui->statusBar->showMessage("Time finished. Wait for the processing of the result");
        on_actionStop_2_triggered();
    }
}

void qMainWindow::on_actionStart_Activity_triggered()
{
    if(type == "practice")
    {
         ui->statusBar->showMessage("Practice session has started. Follow the Red LED to put the ring. Press exit to return to main menu");
    }
    else if(type == "record" ||  type == "online")
    {
         start_serial_logging = true;
         usleep(1000);
         mThread_aux_producer->start();
         mProducer_aux->evaluate();
         if(type == "record")
         {
             mThread_endo_consumer->start();
             mThread_aux_consumer->start();
             mProducer_aux->grab();
             mProducer_endo->grab();
             mConsumer_aux->startGrabbing();
             mConsumer_endo->startGrabbing();
             ui->statusBar->showMessage("Press Stop to Stop the recording; Follow the Red LED to put the ring");
         }
         else if(type == "online")
         {
             if(RecordOnlineEndo)
             {
                 mThread_endo_consumer->start();
                 mProducer_endo->grab();
                 mConsumer_endo->startGrabbing();
             }
             if(RecordOnlineAux)
             {
                 mThread_aux_consumer->start();
                 mProducer_aux->grab();
                 mConsumer_aux->startGrabbing();
             }
             ui->statusBar->showMessage("Press Stop to stop your online evaluation. Follow the Red LED to put the ring");
             startTime.start();
         }
         startTime = QTime::currentTime();
         ui->actionStop_2->setEnabled(true);
         ui->actionStart_Activity->setEnabled(false);
         ui->actionQuit->setEnabled(false);
         writeData("s\n");
         usleep(10000);
    }
}

void qMainWindow::saveData()
{
    string resActivity;
    // write the result onto database instead of writing to file
    string filenameActivity = saveDirectory + "/" + drName + "_" + timestamp + "_level_"+ to_string(level) +"_ActivityData.txt";
    Activity_Data.open(filenameActivity);
    for(uint i = 0 ; i < activities.size(); ++i)
    {
        string aa = activities[i].write(Activity_Data);
        resActivity.append(aa);
    }
    Activity_Data.close();
    string filenameResult = saveDirectory + "/" + drName + "_" + timestamp + "_level_"+ to_string(level) +"_ResultData.txt";
    Activity_Data.open(filenameResult);
    ResultString = result.write(Activity_Data);
    Activity_Data.close();

    filenameActivity = saveDirectory + "/" + drName + "_" + timestamp + "_level_"+ to_string(level) +"_AuxTimeStamp.txt";
    Activity_Data.open(filenameActivity);
    for(uint i = 0 ; i < mConsumer_aux->timestamp_aux.size(); ++i)
    {
        string aa = mConsumer_aux->timestamp_aux[i] ;
        Activity_Data << aa << endl;
    }
    Activity_Data.close();

    filenameActivity = saveDirectory + "/" + drName + "_" + timestamp + "_level_"+ to_string(level) +"_EndoTimeStamp.txt";
    Activity_Data.open(filenameActivity);
    for(uint i = 0 ; i < mConsumer_endo->timestamp_endo.size(); ++i)
    {
        string aa = mConsumer_endo->timestamp_endo[i] ;
        Activity_Data << aa << endl;
    }
    Activity_Data.close();

//    if(sendtoDB)
//    {
//        if(!endoDB.open())
//        {
//            if(!endoDB.isOpen())
//            {
//                QMessageBox::critical(this, tr("Error"), "Database Error !!!");
//                return;
//            }
//        }
//        QSqlQuery query;
//        query.prepare("INSERT INTO recordDB (EmailID, level, EndoVid, AuxVid, Result, ActivityInfo, ResultInfo, TimeStamp, Type, Details, Score)"
//                      "VALUES (:EmailID, :level, :EndoVid, :AuxVid, :Result, :ActivityInfo, :ResultInfo, :TimeStamp, :Type, :Details, :Score)");
//        query.bindValue(":EmailID", emailID);
//        query.bindValue(":level", level);
//        query.bindValue(":EndoVid", QString::fromStdString(endoFilename));
//        query.bindValue(":AuxVid", QString::fromStdString(auxFilename));
//        query.bindValue(":Result", true);
//        query.bindValue(":ActivityInfo", QString::fromStdString(filenameActivity));
//        query.bindValue(":ResultInfo", QString::fromStdString(ResultString));
//        query.bindValue(":TimeStamp", QString::fromStdString(timestamp));
//        query.bindValue(":Type", QString::fromStdString(type));
//        query.bindValue(":Details", QString::fromStdString(details));
//        query.bindValue(":Score", result.totalScore);
//        resultQry = query.exec();
//        if(!resultQry)
//        {
//            QMessageBox::critical(this, tr("Error"), "DB Error - see the log");
//            qDebug() << "DB error:  " << query.lastError();
//        }
//        sendtoDB = false;
//        ui->statusBar->showMessage("Activity completed and saved in the database");
//    }
//    else
//    {
//        ui->statusBar->showMessage("Activity not completed in time. Not saving in the database");
//    }

}

void qMainWindow::processData()
{
    vector<pair<string, string> > Hitting;
    vector<pair<string, int> > Hitting_fdiff;
    vector< pair<string, vector<vector<Point> > > >tuggingData;
    vector<pair<pair<string, int>, string> > State;
    vector<pair<string, pair<double, double> > > trackingDataWithTime;

    Hitting = hittingInfo;
    State = mProducer_aux->stateInfo;
    trackingDataWithTime = mProducer_aux->trackingData;
    Hitting_fdiff = mProducer_aux->hittingData_fdiff;
    tuggingData = mProducer_aux->tuggingData;

    string status;
    uint size = State.size();
    bool No_activity_start = false;
    bool picking_activity_start = false;
    bool moving_activity_start = false;
    bool update_startFrameAndType = true;
    Activity objActivity;
    //qDebug() << "processing start - Getting state info\n";
    for(uint i = 0; i < size; ++i)
    {
        string p = State[i].second;
        if(p.substr(3,1) == "S")
        {
            status = "stationary";
        }
        else if(p.substr(3,1) == "P")
        {
            status = "picking";
        }
        else if(p.substr(3,1) == "M")
        {
            status = "moving";
        }
        if(status == "stationary")
        {
            if(moving_activity_start)
            {
                objActivity.m.endTime = State[i-1].first.first;
                objActivity.m.endIndex = State[i-1].first.second;
                pair<int, int> values;
                stringToValues(State[i-1].second, values, ',');
                objActivity.m.to_peg = values.second;
                activities.push_back(objActivity);
                objActivity.clear();
                moving_activity_start = false;
                update_startFrameAndType = true;
            }
            if(update_startFrameAndType)
            {
                objActivity.type = "stationary";
                objActivity.s.startTime = State[i].first.first;
                objActivity.s.startIndex = State[i].first.second;
                update_startFrameAndType = false;
            }
            No_activity_start = true;
        }
        else if(status == "picking")
        {
            if(No_activity_start)
            {
                objActivity.s.endTime = State[i-1].first.first;
                objActivity.s.endIndex = State[i-1].first.second;
                activities.push_back(objActivity);
                objActivity.clear();
                No_activity_start = false;
                update_startFrameAndType = true;
            }
            if(update_startFrameAndType)
            {
                objActivity.type = "picking";
                objActivity.p.startTime = State[i].first.first;
                objActivity.p.startIndex = State[i].first.second;
                pair<int, int> values;
                stringToValues(State[i].second, values, ',');
                objActivity.p.from_peg = values.first;
                update_startFrameAndType = false;
            }
            picking_activity_start = true;
        }
        else if(status == "moving")
        {
            if(picking_activity_start)
            {
                objActivity.p.endTime = State[i-1].first.first;
                objActivity.p.endIndex  = State[i-1].first.second;
                activities.push_back(objActivity);
                objActivity.clear();
                picking_activity_start = false;
                update_startFrameAndType = true;
            }
            if(No_activity_start)
            {
                objActivity.s.endTime = State[i-1].first.first;
                objActivity.s.endIndex = State[i-1].first.second;
                activities.push_back(objActivity);
                objActivity.clear();
                No_activity_start = false;
                update_startFrameAndType = true;
            }
            if(update_startFrameAndType)
            {
                objActivity.type = "moving";
                objActivity.m.startTime = State[i].first.first;
                objActivity.m.startIndex = State[i].first.second;
                pair<int, int> values;
                stringToValues(State[i].second, values, ',');
                objActivity.m.from_peg = values.first;
                update_startFrameAndType = false;
            }
            moving_activity_start = true;
        }
    }
    // save the last status also
//    if(activities.size() > 0)
//    {
        // remove the bug later. last stationary activity is not considered
//        if(status != activities[activities.size()-1].type)
//        {
//            if(status == "stationary")
//            {
//                objActivity.type = "stationary";
//                objActivity.s.endTime= State[State.size()-1].first.first;
//                objActivity.s.endIndex = State[State.size()-1].first.second;
//            }
//            else if(status == "picking")
//            {
//                objActivity.p.endTime = State[State.size()-1].first.first;
//                objActivity.p.endIndex = State[State.size()-1].first.second;
//            }
//            else if(status == "moving")
//            {
//                objActivity.m.endTime    = State[State.size()-1].first.first;
//                objActivity.m.endIndex = State[State.size()-1].first.second;
//                pair<int, int> values;
//                stringToValues(State[State.size()-1].second, values, ',');
//                objActivity.m.to_peg = values.second;
//            }
//        }
//        activities.push_back(objActivity);
//    }


    //qDebug() << "processing start - Getting tracking and hitting info\n";
    // Process the tracking and Hitting data and put in the activity
    for(uint p = 0; p < activities.size(); ++p)
    {
        string starttime, endtime;
        timeClass temp;
        if(activities[p].type == "stationary")
        {
            qDebug() << "stationary\n";
            starttime = activities[p].s.startTime;
            endtime  = activities[p].s.endTime;
            pair<int, int> rangeHitting;
            bool resHitting = temp.getRange(Hitting, starttime, endtime, rangeHitting);

            pair<int, int> rangeTracking;
            bool resTracking = temp.getRange(trackingDataWithTime, starttime, endtime, rangeTracking);

            pair<int, int> rangeHittingFDiff;
            bool resHittingFDiff = temp.getRange(Hitting_fdiff, starttime, endtime, rangeHittingFDiff);

            pair<int, int> rangeTugging;
            bool resTugging = temp.getRange(tuggingData, starttime, endtime, rangeTugging);

            if(resHitting)
            {
                for(int i =  rangeHitting.first; i <= rangeHitting.second; i++)
                {
                    string date = Hitting[i].first;
                    string str1= Hitting[i].second;
                    string str = str1.substr(3, str1.size()-3);
                    //std::string::size_type index = str.find(',', 0);
                    //int n1 = std::atoi(str.substr(0, index).c_str());
                    int n = std::atoi(str.c_str());
                    activities[p].s.hitting.push_back(make_pair(date, n));
                }
            }

            if(resTracking)
            {
                for(int i =  rangeTracking.first; i < rangeTracking.second; i++)
                {
                    string date = trackingDataWithTime[i].first;
                    pair<double, double> vals = trackingDataWithTime[i].second;
                    activities[p].s.trackingData.push_back(make_pair(date, vals));
                }
            }

            if(resHittingFDiff)
            {
                for(int i =  rangeHittingFDiff.first; i <= rangeHittingFDiff.second; i++)
                {
                    string date = Hitting_fdiff[i].first;
                    int val = Hitting_fdiff[i].second;
                    activities[p].s.hittingData_fdiff.push_back(make_pair(date, val));
                }
            }
            if(resTugging)
            {
                for(int i =  rangeTugging.first; i <= rangeTugging.second; i++)
                {
                    string date = tuggingData[i].first;
                    vector<vector<Point> > val = tuggingData[i].second;
                    activities[p].s.tuggingData.push_back(make_pair(date, val));
                }
            }

        }
        else if (activities[p].type == "picking")
        {
            qDebug() << "picking\n";
            starttime = activities[p].p.startTime;
            endtime  = activities[p].p.endTime;
            pair<int, int> rangeHitting;
            bool resHitting = temp.getRange(Hitting, starttime, endtime, rangeHitting);

            pair<int, int> rangeTracking;
            bool resTracking = temp.getRange(trackingDataWithTime, starttime, endtime, rangeTracking);

            pair<int, int> rangeHittingFDiff;
            bool resHittingFDiff = temp.getRange(Hitting_fdiff, starttime, endtime, rangeHittingFDiff);

            pair<int, int> rangeTugging;
            bool resTugging = temp.getRange(tuggingData, starttime, endtime, rangeTugging);

            if(resHitting)
            {
                for(int i =  rangeHitting.first; i <= rangeHitting.second; i++)
                {
                    string date = Hitting[i].first;
                    string str1 = Hitting[i].second;
                    string str = str1.substr(3, str1.size()-3);
                    //std::string::size_type index = str.find(',', 0);
                    //int n1 = std::atoi(str.substr(0, index).c_str());
                    int n = std::atoi(str.c_str());
                    activities[p].p.hitting.push_back(make_pair(date, n));
                }
            }
            if(resTracking)
            {
                for(int i =  rangeTracking.first; i < rangeTracking.second; i++)
                {
                    string date = trackingDataWithTime[i].first;
                    pair<double, double> vals = trackingDataWithTime[i].second;
                    activities[p].p.trackingData.push_back(make_pair(date, vals));
                }
            }
            if(resHittingFDiff)
            {
                for(int i =  rangeHittingFDiff.first; i <= rangeHittingFDiff.second; i++)
                {
                    string date = Hitting_fdiff[i].first;
                    int val = Hitting_fdiff[i].second;
                    activities[p].p.hittingData_fdiff.push_back(make_pair(date, val));
                }
            }
            if(resTugging)
            {
                for(int i =  rangeTugging.first; i <= rangeTugging.second; i++)
                {
                    string date = tuggingData[i].first;
                    vector<vector<Point> > val = tuggingData[i].second;
                    activities[p].p.tuggingData.push_back(make_pair(date, val));
                }
            }
        }
        else if (activities[p].type == "moving")
        {
            qDebug() << "moving\n";
            starttime = activities[p].m.startTime;
            endtime  = activities[p].m.endTime;

            pair<int, int> rangeHitting;
            bool resHitting = temp.getRange(Hitting, starttime, endtime, rangeHitting);

            pair<int, int> rangeTracking;
            bool resTracking = temp.getRange(trackingDataWithTime, starttime, endtime, rangeTracking);

            pair<int, int> rangeHittingFDiff;
            bool resHittingFDiff = temp.getRange(Hitting_fdiff, starttime, endtime, rangeHittingFDiff);

            pair<int, int> rangeTugging;
            bool resTugging = temp.getRange(tuggingData, starttime, endtime, rangeTugging);

            if(resHitting)
            {
                for(int i =  rangeHitting.first; i <= rangeHitting.second; i++)
                {
                    string date = Hitting[i].first;
                    string str1 = Hitting[i].second;
                    string str = str1.substr(3, str1.size()-3);
                    //std::string::size_type index = str.find(',', 0);
                    //int n1 = std::atoi(str.substr(0, index).c_str());
                    int n = std::atoi(str.c_str());
                    activities[p].m.hitting.push_back(make_pair(date, n));
                }
            }
            if(resTracking)
            {
                for(int i =  rangeTracking.first; i < rangeTracking.second; i++)
                {
                    string date = trackingDataWithTime[i].first;
                    pair<double, double> vals = trackingDataWithTime[i].second;
                    activities[p].m.trackingData.push_back(make_pair(date, vals));
                }
            }

            if(resHittingFDiff)
            {
                for(int i =  rangeHittingFDiff.first; i <= rangeHittingFDiff.second; i++)
                {
                    string date = Hitting_fdiff[i].first;
                    int val = Hitting_fdiff[i].second;
                    activities[p].m.hittingData_fdiff.push_back(make_pair(date, val));
                }
            }
            if(resTugging)
            {
                for(int i =  rangeTugging.first; i <= rangeTugging.second; i++)
                {
                    string date = tuggingData[i].first;
                    vector<vector<Point> > val = tuggingData[i].second;
                    activities[p].m.tuggingData.push_back(make_pair(date, val));
                }
            }
        }
    }
   qDebug() << "out activity processing\n";
//   qDebug() << "Printing the Result \n";
//   for(uint p = 0; p < activities.size(); ++p)
//   {
//       activities[p].print();
//   }


   if(activities.size())
   {
       // start processing the activity data and put into result data
       for(uint p = 0; p < activities.size(); ++p)
       {
           Activity act = activities[p];
           if (act.type == "stationary")
           {
               // total time in No-Activity;
               result.noactivity.no_frames += act.s.endIndex - act.s.startIndex + 1;
               result.noactivity.time += timeClass::timeSpentinMillis(act.s.startTime, act.s.endTime);
               // Hitting during No-Activity
               for(int i = 0; i < act.s.hitting.size(); i++)
               {
                   if(act.s.hitting[i].second > HITTING_THRESHOLD_SENSOR )
                   {
                       result.hitting.hittingData.push_back(act.s.hitting[i]);
                   }
               }
           }
           else if(act.type == "picking")
           {
               result.grasping.NoFramesPicking.push_back(make_pair(act.p.from_peg, (act.p.endIndex-act.p.startIndex+1)));
               result.grasping.timePicking.push_back(make_pair(act.p.from_peg, (timeClass::timeSpentinMillis(act.p.startTime,act.p.endTime))));
               for(int i = 0; i < act.p.hitting.size(); i++)
               {
                   if(act.p.hitting[i].second > HITTING_THRESHOLD_SENSOR)
                   {
                       result.hitting.hittingData.push_back(act.p.hitting[i]);
                   }
               }

               vector<pair<double, double> > data;
               for (int i = 0; i < act.p.trackingData.size(); ++i)
               {
                   data.push_back(act.p.trackingData[i].second);
               }
               result.grasping.trackingData.push_back(make_pair(act.p.from_peg, data));
               data.clear();
           }
           else if(act.type == "moving")
           {
               result.wavymotion.NoFramesMoving.push_back(make_pair(make_pair(act.m.from_peg, act.m.to_peg), act.m.endIndex-act.m.startIndex+1));
               result.wavymotion.timeMoving.push_back(make_pair(make_pair(act.m.from_peg, act.m.to_peg), timeClass::timeSpentinMillis(act.m.startTime,act.m.endTime)));
               for(int i = 0; i < act.m.hitting.size(); i++)
               {
                   if(act.m.hitting[i].second > HITTING_THRESHOLD_SENSOR)
                   {
                       result.hitting.hittingData.push_back(act.m.hitting[i]);
                   }
               }
               vector<pair<double, double> > data;
               for (int i = 0; i < act.m.trackingData.size(); ++i)
               {
                   data.push_back(act.m.trackingData[i].second);
               }
               result.wavymotion.trackingData.push_back(make_pair(make_pair(act.m.from_peg, act.m.to_peg), data));
               data.clear();
           }
       }
   }
   qDebug() << "out activity processing E 1\n";
   if(result.grasping.trackingData.size())
   {
       for(int i = 0; i < result.grasping.trackingData.size(); i++)
       {
           double varX = 0;
           double varY = 0;
           double arcLength = 0;
           double curvatureMax = 0;
           int curvatureMaxCount = 0;
           vector<pair <double, double > > x;
           vector<pair <double, double > > dx;
           vector<pair <double, double > > ddx;
           vector<double> Curvature;

           vector<pair <double, double > > data = result.grasping.trackingData[i].second;
           //qDebug() << " grasping normalize enter\n";
           util::normalize2D(data, x);
           //qDebug() << " data size \n" << data.size();
           //qDebug() << " x normalized data \n" << x.size();
           //for(int i = 0; i < x.size(); i++)
           //{
           //    qDebug() << "x[i] - " << x[i] << endl;
           //}
           //qDebug() << " grasping diff2d enter 1\n";
           util::diff2D(x, dx);
           //qDebug() << "grasping diff2d enter 2\n";
           util::diff2D(dx, ddx);
           //qDebug() << " grasping var2d enter 1\n";
           util::var2D(dx, &varX, &varY);
           //qDebug() << "grasping curvature enter 1\n";
           util::curvature(dx, ddx, Curvature);
           //qDebug() << "grasping curvature max count enter\n";
           util::curvatureMaxnCount(Curvature, &curvatureMax, &curvatureMaxCount);
           //qDebug() << "grasping arclength enter\n";
           util::arclength(dx, &arcLength);

           result.grasping.curvatureMax.push_back(make_pair(result.grasping.trackingData[i].first, curvatureMax));
           result.grasping.arcLength.push_back(make_pair(result.grasping.trackingData[i].first, arcLength));
           result.grasping.curvatureMaxCount.push_back(make_pair(result.grasping.trackingData[i].first, curvatureMaxCount));
       }
   }
   qDebug() << "out activity processing E 2\n";
   if(result.wavymotion.trackingData.size())
   {
       for(int i = 0; i < result.wavymotion.trackingData.size(); i++)
       {
           double varX = 0;
           double varY = 0;
           double arcLength = 0;
           double curvatureMax = 0;
           int curvatureMaxCount = 0;
           vector<pair <double, double > > x;
           vector<pair <double, double > > dx;
           vector<pair <double, double > > ddx;
           vector<double> Curvature;

           vector<pair <double, double > > data = result.wavymotion.trackingData[i].second;
           util::normalize2D(data, x);
           util::diff2D(x, dx);
           util::diff2D(dx, ddx);
           util::var2D(dx, &varX, &varY);
           util::curvature(dx, ddx, Curvature);
           util::curvatureMaxnCount(Curvature, &curvatureMax, &curvatureMaxCount);
           util::arclength(dx, &arcLength);

           result.wavymotion.curvatureMax.push_back(make_pair(result.wavymotion.trackingData[i].first, curvatureMax));
           result.wavymotion.arcLength.push_back(make_pair(result.wavymotion.trackingData[i].first, arcLength));
           result.wavymotion.curvatureMaxCount.push_back(make_pair(result.wavymotion.trackingData[i].first, curvatureMaxCount));
       }
   }

   qDebug() << "out activity processing E 3\n";
    //qDebug() << "\nActivity-Info Size " << activities.size();
    //for(uint i = 0 ; i < activities.size(); ++i)
    //{
        //activities[i].print();
    //}
    //cout << "\nResult \n";
    //result.print();
}


void qMainWindow::showData()
{
    QTreeView *view = new QTreeView;
    //QDirModel *model = new QDirModel(this);
    QStringList headers;
    headers << "Result Component" << "Description";
    modelResult->setHorizontalHeaderLabels(headers);


    QStandardItem *item = new QStandardItem("Hitting");
    QStandardItem *child = new QStandardItem("Time-stamp, Sensor-1, Sensor-2");
    child->setEditable( false );
    item->appendRow( child );
    for(int i = 0; i < result.hitting.hittingData.size(); i++)
    {
        QString d = QString::fromStdString(result.hitting.hittingData[i].first) + "," +
                       QString::number(result.hitting.hittingData[i].second);

        QStandardItem *child = new QStandardItem(d);
        child->setEditable( false );
        item->appendRow( child );
    }
    modelResult->setItem(0,0, item);


    item = new QStandardItem("Grasping");
    child = new QStandardItem("from-peg, Time(S), No. of frames, Arc-lengh, Max-Curvature, Max-Curvature-Count");
    child->setEditable( false );
    item->appendRow( child );
    for(int i = 0; i < result.grasping.timePicking.size(); i++)
    {
        QString d = QString::number(result.grasping.timePicking[i].first) + "   ," +
                    QString::number(static_cast<double>(result.grasping.timePicking[i].second) /1000.0) + "   ," +
                    QString::number(result.grasping.NoFramesPicking[i].second) + "   ," +
                    QString::number(result.grasping.arcLength[i].second) + "   ," +
                    QString::number(result.grasping.curvatureMax[i].second) + "   ," +
                    QString::number(result.grasping.curvatureMaxCount[i].second);

        QStandardItem *child = new QStandardItem(d);
        child->setEditable( false );
        item->appendRow( child );
    }
    modelResult->setItem(1,0, item);



    item = new QStandardItem("Wavy-Motion");
    child = new QStandardItem("from-peg, to-peg, Time(S), No. of frames, Arc-lengh, Max-Curvature, Max-Curvature-Count");
    child->setEditable( false );
    item->appendRow( child );
    for(int i = 0; i < result.wavymotion.timeMoving.size(); i++)
    {
        QString d = QString::number(result.wavymotion.timeMoving[i].first.first) + "   ," +
                    QString::number(result.wavymotion.timeMoving[i].first.second) + "   ," +
                    QString::number(static_cast<double>(result.wavymotion.timeMoving[i].second) /1000.0) + "   ," +
                    QString::number(result.wavymotion.NoFramesMoving[i].second) + "   ," +
                    QString::number(result.wavymotion.arcLength[i].second) + "   ," +
                    QString::number(result.wavymotion.curvatureMax[i].second) + "   ," +
                    QString::number(result.wavymotion.curvatureMaxCount[i].second);

        QStandardItem *child = new QStandardItem(d);
        child->setEditable( false );
        item->appendRow( child );
    }
    modelResult->setItem(2,0, item);


    item = new QStandardItem("No-Activity");
    child = new QStandardItem("Time-taken in No activity");
    child->setEditable( false );
    item->appendRow( child );
    QString d = QString::number(static_cast<double>(result.noactivity.time)/1000.0);
    child = new QStandardItem(d);
    child->setEditable( false );
    item->appendRow( child );
    modelResult->setItem(3,0, item);
    view->setModel(modelResult);
    view->setUniformRowHeights(true);
    view->expandAll();
    this->centralWidget()->close();
    this->setCentralWidget(view);
    //m_showResult->setString(ResultString);
    //m_showResult->show();
}


void qMainWindow::on_actionStop_2_triggered()
{
    writeData("z\n");
    writeData("z\n");
    mProducer_aux->sendFrame = false;
    mProducer_endo->sendFrame = false;
    usleep(100000);
    //startTime.restart();
    if(type == "practice")
    {
        cout << "action exit in pracrice \n";
        mProducer_endo->abort();
    }
    else if(type == "record")
    {
        cout << "action exit in record \n";
        start_serial_logging = false;
        mProducer_endo->abort();
        mConsumer_endo->abort();
        mProducer_aux->abort();
        mConsumer_aux->abort();
        saveData();

        ui->statusBar->showMessage("Recording finished. Press exit for the main menu");
    }
    else if(type == "online")
    {
        start_serial_logging = false;
        mProducer_endo->abort();
        mConsumer_endo->abort();
        mProducer_aux->abort();
        mConsumer_aux->abort();
        ui->statusBar->showMessage("Activity done. Processing data for the scoring ...");

        processData();
        saveData();
        showData();
    }
    usleep(1000000);
    ui->actionStop_2->setEnabled(false);
    ui->actionStart_Activity->setEnabled(false);
    ui->actionSwitch_Camera->setEnabled(false);
    ui->actionQuit->setEnabled(true);
}

void qMainWindow::on_actionSwitch_Camera_triggered()
{
    qDebug() << "camState-> " << camState;
    camState = !camState;
    if(camState)
    {
        mProducer_aux->sendFrame = false;
        mProducer_endo->sendFrame = true;
    }
    else
    {
        mProducer_aux->sendFrame = true;
        mProducer_endo->sendFrame = false;
    }
}
void qMainWindow::LEDindexChange(int id)
{
    qDebug() << "id" << id << endl;
    if(id == 1)
    {
        writeData("a\n");
        usleep(10000);
    }
    else if(id == 2)
    {
        writeData("b\n");
        usleep(10000);
    }
    else if(id == 3)
    {
        writeData("c\n");
        usleep(10000);
    }
    else if(id == 4)
    {
        writeData("d\n");
        usleep(10000);
    }
    else if(id == 5)
    {
        writeData("e\n");
        usleep(10000);
    }
    else if(id == 6)
    {
        writeData("f\n");
        usleep(10000);
    }
    else if(id == 7)
    {
        writeData("g\n");
        usleep(10000);
    }
    else if(id == 8)
    {
        writeData("h\n");
        usleep(10000);
    }
    else if(id == 9)
    {
        writeData("i\n");
        usleep(10000);
    }
    else if(id == 10)
    {
        writeData("j\n");
        usleep(10000);
    }
    else if(id == 11)
    {
        writeData("k\n");
        usleep(10000);
    }
    else if(id == 12)
    {
        writeData("l\n");
        usleep(10000);
    }
}

void qMainWindow::stringToValues(const string &str, pair<int, int> &values, char separator)
{
    string s = str.substr(5, str.size()-5);
    cout << s << endl;
    std::string::size_type index = s.find(separator);
    if(index != string::npos)
    {
        values.first = std::atoi(s.substr(0, index).c_str());
        values.second = std::atoi(s.substr(index+1).c_str());
    }
    else
    {
        values.first = atoi(s.c_str());
    }
}



void qMainWindow::readData()
{
    QByteArray data;
    while (serial->canReadLine())
    {
       data = serial->readLine();   //reads in data line by line, separated by \n or \r characters
       if(start_serial_logging)
       {
           // start logging the hitting data and state info
           //qDebug() << "Serial Data -> " << data << endl;
           hittingInfo.push_back(make_pair(currentDateTime(), data.toStdString()));
       }
    }
}


void qMainWindow::updateScreen(const myMat &image)
{
    if( mFlipVert && mFlipHoriz )
        cv::flip( image,image, -1);
    else if( mFlipVert )
        cv::flip( image,image, 0);
    else if( mFlipHoriz )
        cv::flip( image,image, 1);
    ui->openCVviewer->showImage( image );

}

void qMainWindow::cleanup()
{
    cout << "cleanup mainwindow \n";

    if(type == "practice")
    {
        cout << "cleanup mainwindow(practice) \n";
        if(mThread_endo_producer->isRunning())
            mThread_endo_producer->quit();
        if(mProducer_endo != NULL)
        {
            delete mProducer_endo; mProducer_endo = NULL;
        }
        if(mThread_aux_producer->isRunning())
            mThread_aux_producer->quit();
        if(mProducer_aux)
        {
            delete mProducer_aux; mProducer_aux = NULL;
        }
    }
    if(type == "record" || type == "online")
    {
        cout << "cleanup mainwindow(record) \n";
        if(mThread_endo_producer->isRunning() )
            mThread_endo_producer->quit();
        if(mProducer_endo != NULL)
        {
            delete mProducer_endo; mProducer_endo = NULL;
        }
        if(mThread_endo_consumer->isRunning())
            mThread_endo_consumer->quit();
        if(mConsumer_endo)
        {
            delete mConsumer_endo; mConsumer_endo = NULL;
        }
        if(mThread_aux_producer->isRunning())
            mThread_aux_producer->quit();
        if(mProducer_aux)
        {
            delete mProducer_aux; mProducer_aux = NULL;
        }

        if(mThread_aux_consumer->isRunning())
            mThread_aux_consumer->quit();
        if(mConsumer_aux != NULL)
        {
            delete mConsumer_aux; mConsumer_aux = NULL;
        }
    }
}

qMainWindow::~qMainWindow()
{
    cleanup();
    closeSerialPort();
    delete serial;
    delete ui;
}

void qMainWindow::on_action_Vertical_Flip_toggled(bool checked)
{
    mFlipVert = checked;
}

void qMainWindow::on_action_Horizontal_Flip_triggered(bool checked)
{
    mFlipHoriz = checked;
}

void qMainWindow::on_actionQuit_triggered()
{
    if(type == "practice")
    {
         ui->statusBar->showMessage("Practice session finished. Exiting to main menu");
    }
    else if(type == "record")
    {
         ui->statusBar->showMessage("Recording done. Exiting to main menu");
    }
    else if(type == "online")
    {
         ui->statusBar->showMessage("Online evaluation done. Exiting to main menu");
    }
    cleanup();
    closeSerialPort();
    this->close();
    /*mSettingMain->show();*/
}

void qMainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError)
    {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void qMainWindow::openSerialPort()
{
    serial->setPortName(param.serial_name);
    serial->setBaudRate(param.serial_baudRate);
    serial->setDataBits(param.serial_dataBits);
    serial->setParity(param.serial_parity);
    serial->setStopBits(param.serial_stopBits);
    serial->setFlowControl(param.serial_flowControl);
    if (!serial->open(QIODevice::ReadWrite))
    {
       QMessageBox::critical(this, tr("Error"), serial->errorString());
    }
    //qDebug() << "\nusing serial port - " << param.serial_name << endl;
}

void qMainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
}

void qMainWindow::writeData(const QString str)
{
    qDebug() << "writing data " << str;
    QByteArray commandSerial = str.toLocal8Bit();
    serial->write(commandSerial);
    usleep(100000);
}

const string qMainWindow::currentDateTime()
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

void qMainWindow::on_actionTemp_triggered()
{
    //writeData("j\n");
}

void qMainWindow::on_actionTemp2_triggered()
{
    //qDebug() << "Aux producer running? -> " << mThread_aux_producer->isRunning();
    //qDebug() << "Aux producer finished? -> " << mThread_aux_producer->isFinished();

    //qDebug() << "Endo producer running? -> " << mThread_endo_producer->isRunning();
    //qDebug() << "Endo producer finished? -> " << mThread_endo_producer->isFinished();
}

