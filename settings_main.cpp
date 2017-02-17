#include "settings_main.h"
#include "ui_settings_main.h"
#include "timeClass.h"
//12-12-12
Q_DECLARE_METATYPE(QCameraInfo)

settings_main::settings_main(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings_main)
{
    ui->setupUi(this);
    clearUI();
    mSettings = new settings();

    connect(ui->pbSettings, SIGNAL(clicked()), this, SLOT(openSettingsDialog()));
    //qRegisterMetaType< myMat>("const myMat &");
    connect(mSettings, SIGNAL(makeUpdateParams(params)), this, SLOT(updateParameters(params)));
    //connect(mainWindow, SIGNAL(ReinitializeSettings_Main()), this, SLOT(initialSetup()));
    initialSetup();

    img3u_disp = Mat::zeros(256, 320, CV_8UC3);
    img3u_disp1 = Mat::zeros(256, 320, CV_8UC3);

    pegGroupROI = Rect(100, 100, 500, 400);
    scene_aux = new QGraphicsScene;
    scene_endo = new QGraphicsScene;
    ui->view_aux->setInteractive(true);

    connect(ui->view_aux, SIGNAL(sendMouseClickEvent(string &, vector<int>&)), this, SLOT(mouseClickOnAuxCam(string &, vector<int>&)));
    connect(ui->view_aux, SIGNAL(sendMouseMoveData(vector<int>&)), this, SLOT(mouseMoveOnAuxCam(vector<int>&)));
    connect(ui->view_aux, SIGNAL(sendMouseReleaseEvent(vector<int>&)), this, SLOT(mouseReleaseOnAuxCam(vector<int>&)));
    mouseDrag = false;
    x_left_start = -1;
    y_left_start = -1;
    boundingRectangle = QRect(-1, -1, -1, -1);
    segment_peg = false;
    segment_ring = false;
    segment_tool = false;
    pegs_small.resize(12);
    pegs_big.resize(12);
    withRingThresh.resize(12);
    withoutRingThresh.resize(12);

    element[0] = getStructuringElement(MORPH_ELLIPSE, Size(8, 8), Point(0, 0));
    element[1] = getStructuringElement(MORPH_ELLIPSE, Size(8, 8), Point(0, 0));
    element[2] = getStructuringElement(MORPH_ELLIPSE, Size(3, 3), Point(0, 0));
    element[3] = getStructuringElement(MORPH_ELLIPSE, Size(3, 3), Point(0, 0));

//    endoDB = QSqlDatabase::addDatabase("QMYSQL");
//    endoDB.setHostName("192.168.1.2");
//    endoDB.setDatabaseName("endodb");
//    endoDB.setUserName("root");
//    endoDB.setPassword("netsaiims");
//    endoDB.open();
//    mSettings->setDB(endoDB);
//    if(!endoDB.isOpen())
//    {
//        QMessageBox::critical(this, tr("Error"), "<pre>Database Error. Please make sure that Rasberry-PI is turned on. <br>"
//                                                 "If the problem persists call admin (+91-7827078568).Exiting the application </pre>");
//        exit(0);
//    }

    path_to_db = QDir::currentPath() + "/db/endoDB.sqlite";
    endoDB = QSqlDatabase::addDatabase("QSQLITE");
    endoDB.setDatabaseName(path_to_db);
    QFileInfo checkFile(path_to_db);
    if(!checkFile.isFile() || !endoDB.open())
    {
        QMessageBox::critical(this, tr("Error"), "Database connection failure. Exiting the application...");
        exit(0);
    }


    ui->txtDetails->setText(QDate::currentDate().toString());

    //serial port stuff
    serial = new QSerialPort(this);
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
    openSerialPort();
    usleep(1000000);
    ui->groupBox_2->hide();
    updateNames();

    //qDebug() << "time in ms " << timeClass::timeSpentinMillis("13:16:25:500", "13:14:10:999") << endl;

    filename_auxCamCalib = "/calib_files/aux_CamCalib_Straight.txt";
    parse_AuxCamCalib(filename_auxCamCalib);
    //writeData("z\n");
    //writeData("s\n");
    //writeData("y\n");
    showOverlay = false;
}

void settings_main::updateNames()
{
    ui->boxName->clear();
    QSqlQuery query;
    query.prepare("SELECT * FROM nameID");
    resultQry = query.exec();
    int counter = 0;
    QVector<QString> names;
    names.clear();
    if(resultQry)
    {
        while(query.next())
        {
            QString pp = QString::number(++counter) + ". " + query.value(1).toString() + "(" + query.value(0).toString() + ")";
            names.push_back(pp);
        }
        for(int i = names.size()-1; i >= 0; --i)
        {
            ui->boxName->addItem(names[i]);
        }
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), "No Doctors in the database. click on settings to add doctors");
        qDebug() << "DB error:  " << query.lastError();
        return;
    }
}

void settings_main::openSerialPort()
{
    serial->setPortName(parameters.serial_name);
    serial->setBaudRate(parameters.serial_baudRate);
    serial->setDataBits(parameters.serial_dataBits);
    serial->setParity(parameters.serial_parity);
    serial->setStopBits(parameters.serial_stopBits);
    serial->setFlowControl(parameters.serial_flowControl);
    if (!serial->open(QIODevice::ReadWrite))
    {
       QMessageBox::critical(this, tr("Error"), serial->errorString());
    }
}

void settings_main::closeSerialPort()
{
    if(serial->isOpen())
    {
        qDebug() << "Closing serial port \n";
        writeData("z\n");
        usleep(1000);
        serial->close();
    }
}

void settings_main::writeData(const QString str)
{
    qDebug() << "writing data " << str;
    QByteArray commandSerial = str.toLocal8Bit();
    //qDebug() << "before write ";
    serial->write(commandSerial);
    //qDebug() << "after write ";
    usleep(10000);
}
void settings_main::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError)
    {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void settings_main::parse_AuxCamCalib(const QString &filename)
{
    QString fileCalib = QDir::currentPath()+ filename;
//    qDebug() << "fileCalib" << fileCalib;
    QFile file(fileCalib);
    if(ui->tabWidget->currentIndex() == 0)
    {
//        qDebug() << "Before Calibration\n";
//        qDebug() << "Bounding Box\n" << boundingRectangle << endl;
//        qDebug() << "pegs_small\n" << pegs_small << endl;
//        qDebug() << "pegs_big\n" << pegs_big << endl;
//        qDebug() << "with ring thresh\n" << withRingThresh << endl;
//        qDebug() << "without ring thresh\n" << withoutRingThresh << endl;
//        qDebug() << "thresh ring\n" << ring_segment << endl;
//        qDebug() << "tool_segment\n" << tool_segment << endl;
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(0, "error", "Aux-Cam Calibration File not found; Do the auxiliary camera calibration to proceed");
            ui->pbOnline->setEnabled(false);
            ui->checkCalib->setChecked(true);
            ui->groupBox_2->show();
            usleep(100000);
            ui->comboSelectLevel->setEnabled(true);
            ui->comboSelectLevel->setCurrentIndex(0);
            writeData("z\n");
            writeData("s\n");
            //writeData("s\n");
            ui->label_status->clear();
            ui->label_status->setText("Select the plate angle");
        }
        else
        {
            QTextStream in(&file);
            int count1 = 0;
            int count2 = 0;
            int count3 = 0;
            int count4 = 0;
            while(!in.atEnd())
            {
                QString line = in.readLine();
                QStringList fields = line.split(",");
                if(fields[0] == "Bounding Rect")
                {
                    int x = fields[1].toInt();
                    int y = fields[2].toInt();
                    int w = fields[3].toInt();
                    int h = fields[4].toInt();
                    boundingRectangle.setRect(x, y, w, h);
                }
                else if(fields[0] == "Pegs Rect small")
                {
                    int x = fields[1].toInt();
                    int y = fields[2].toInt();
                    int w = fields[3].toInt();
                    int h = fields[4].toInt();
                    pegs_small[count1++].setRect(x, y, w, h);
                }
                else if(fields[0] == "Pegs Rect big")
                {
                    int x = fields[1].toInt();
                    int y = fields[2].toInt();
                    int w = fields[3].toInt();
                    int h = fields[4].toInt();
                    pegs_big[count2++].setRect(x, y, w, h);
                }
                else if(fields[0] == "with ring thresh")
                {
                    double small = fields[1].toDouble();
                    double big = fields[2].toDouble();
                    withRingThresh[count3++] = make_pair(small, big);
                }
                else if(fields[0] == "without ring thresh")
                {
                    double small = fields[1].toDouble();
                    double big = fields[2].toDouble();
                    withoutRingThresh[count4++] = make_pair(small, big);
                }
                else if(fields[0] == "Threshold Ring")
                {
                    ring_segment = fields[1].toInt();
                }
                else if(fields[0] == "Threshold Tool")
                {
                     tool_segment = fields[1].toInt();
                }
                //qDebug() <<  "fields" << fields << endl;
            }
            double max1 = withoutRingThresh[0].first;
            double max2 = withoutRingThresh[0].second;
            double min1 = withRingThresh[0].first;
            double min2 = withRingThresh[0].second;
            for(int i = 1; i < withoutRingThresh.size(); i++)
            {
                if(max1 <= withoutRingThresh[i].first)
                {
                    max1 = withoutRingThresh[i].first;
                }
                if(max2 <= withoutRingThresh[i].second)
                {
                    max2 = withoutRingThresh[i].second;
                }
            }
            for(int i = 0; i < withRingThresh.size(); i++)
            {
                if(min1 >= withRingThresh[i].first)
                {
                    min1 = withRingThresh[i].first;
                }
                if(min2 >= withRingThresh[i].second)
                {
                    min2 = withRingThresh[i].second;
                }
            }
            withoutRing_smallRectThresh = max1;
            withoutRing_bigRectThresh = max2;
            withRing_smallRectThresh = min1;
            withRing_bigRectThresh = min2;
            //writeData("z\n");
            //usleep(100000);
            //writeData("s\n");
            //usleep(100000);
//            qDebug() << "After Calibration\n";
//            qDebug() << "Bounding Box\n" << boundingRectangle << endl;
//            qDebug() << "pegs_small\n" << pegs_small << endl;
//            qDebug() << "pegs_big\n" << pegs_big << endl;
//            qDebug() << "with ring thresh\n" << withRingThresh << endl;
//            qDebug() << "without ring thresh\n" << withoutRingThresh << endl;
//            qDebug() << "thresh ring\n" << ring_segment << endl;
//            qDebug() << "tool_segment\n" << tool_segment << endl;
        }
    }
}



void settings_main::mouseClickOnAuxCam(string &clk, vector<int> &d)
{
    string clickData = clk;
    if(clickData == "left")
    {
        mouseDrag = true;
        x_left_start = d[0];
        y_left_start = d[1];
    }
    if(segment_peg)
    {
        scene_aux->clear();
        scene_aux->addPixmap(QPixmap::fromImage(AuxImg));
        temp_rect = QRect(d[0]-10, d[1]-10, 20, 15);
        temp_rectBig = QRect(d[0]-20, d[1]-35, 35, 35);
        scene_aux->addRect(temp_rect,QPen(QColor(0, 0,255)));
        scene_aux->addRect(temp_rectBig,QPen(QColor(0, 255,0)));
    }
}

void settings_main::mouseMoveOnAuxCam(vector<int> &d)
{
    if(mouseDrag && ui->radioBoundingBox->isChecked() && ui->radioBoundingBox->isEnabled())
    {
        boundingRectangle = QRect(x_left_start, y_left_start, d[0]-x_left_start, d[1]-y_left_start);
        scene_aux->clear();
        scene_aux->addPixmap(QPixmap::fromImage(AuxImg));
        scene_aux->addRect(boundingRectangle,QPen(QColor(255, 0,0)));
    }
}

void settings_main::mouseReleaseOnAuxCam(vector<int> &d)
{
    mouseDrag = false;
    if(ui->radioBoundingBox->isChecked() && ui->radioBoundingBox->isEnabled())
    {
        ui->label_status->clear();
        ui->label_status->setText("Redraw or press confirm");
        ui->btnBoundingBox->setEnabled(true);
    }
}

void settings_main::clearUI()
{
    endoInitialized = false;
    auxInitialized = false;
    cameraCountEndo = 0;
    cameraCountAux = 0;
    camBaslerFound = false;
    camIDSFound = false;
    camEndoFound = false;
    camAuxFound = false;
    ui->listWidgetEndoOnline->clear();
    ui->listWidgetAuxOnline->clear();
    ui->listWidgetEndoOffline->clear();
    ui->listWidgetEndoOnline->clear();
    ui->listWidgetPractice->clear();
}

bool settings_main::initialSetup()
{
    // setup for the endoscopy camera
    if(!endoInitialized)
    {
        //cout << "a\n";
        mTest_USB    = new testUSB;
        thread_endo = new QThread;
        cameraCountEndo =mTest_USB->initialize(parameters, devs_endo);
        camEndoFound = cameraCountEndo>0 ? true:false;
    }


    if(camEndoFound && !endoInitialized)
    {
        //cout << "b\n";
        for(int i = 0; i < devs_endo.size(); ++i)
        {
            ui->listWidgetEndoOnline->addItem(QString::fromStdString(devs_endo[i]));
            ui->listWidgetEndoOffline->addItem(QString::fromStdString(devs_endo[i]));
            ui->listWidgetPractice->addItem(QString::fromStdString(devs_endo[i]));
        }

        mTest_USB->moveToThread(thread_endo);
        connect(thread_endo, SIGNAL(started()), mTest_USB, SLOT(process()));
        connect(mTest_USB, SIGNAL(finished()), thread_endo, SLOT(quit()));

        qRegisterMetaType< myMat>("const myMat &");
        connect(mTest_USB, SIGNAL(sendtoUI(const myMat &)), this, SLOT(updatelblEndo(const myMat &)), Qt::QueuedConnection);
        thread_endo->start();

        usleep(10000);
        mTest_USB->m_start = true;
        ui->pbPractice->setEnabled(true);
        endoInitialized = true;
    }
    else
    {
        //cout << "c\n";
        if(!endoInitialized)
        {
            const QString msg = "Endoscopy camera not found. Can't run online evaluation";
            ui->label_status->clear();
            ui->label_status->setText(msg);
            delete mTest_USB; mTest_USB = NULL;
            delete thread_endo; thread_endo = NULL;
            return false;
        }
   }

    // setup for the endoscopy camera

    if(!auxInitialized)
    {
        //cout << "d\n";
        mTest_Basler = new testBasler;
        mTest_IDS    = new testIDS;
        thread_aux  = new QThread;

        // check if any GIGE camera is connected
        camBaslerFound = mTest_Basler->initialize(parameters, errmsg);
        camIDSFound =mTest_IDS->initialize(parameters, errmsg);
        camAuxFound = (camBaslerFound || camIDSFound) ?true:false;
        devAux      = camBaslerFound?"basler":camIDSFound?"ids":"";
        parameters.cap_auxCam = devAux;
    }

    if(camAuxFound && !auxInitialized)
    {
        //cout << "e\n";
        if(camIDSFound)
        {
            cout << "f\n";
            ui->listWidgetAuxOnline->addItem("IDS UI-5240CP-C-HQ");
            ui->listWidgetAuxOffline->addItem("IDS UI-5240CP-C-HQ");
            mTest_IDS->moveToThread(thread_aux);
            connect(thread_aux, SIGNAL(started()), mTest_IDS, SLOT(process()));
            connect(mTest_IDS, SIGNAL(finished()), thread_aux, SLOT(quit()));

            qRegisterMetaType< myMat>("const myMat &");
            connect(mTest_IDS, SIGNAL(sendtoUI(const myMat &)), this, SLOT(updatelblAux(const myMat &)), Qt::QueuedConnection);

            mTest_IDS->m_start = true;
            usleep(10000);
            delete mTest_Basler; mTest_Basler = NULL;
        }
        if(camBaslerFound)
        {
            //cout << "g\n";
            ui->listWidgetAuxOnline->addItem("Basler acA1300-60gc");
            ui->listWidgetAuxOffline->addItem("Basler acA1300-60gc");
            mTest_Basler->moveToThread(thread_aux);
            connect(thread_aux, SIGNAL(started()), mTest_Basler, SLOT(process()));
            connect(mTest_Basler, SIGNAL(finished()), thread_aux, SLOT(quit()));

            qRegisterMetaType< myMat>("const myMat &");
            connect(mTest_Basler, SIGNAL(sendtoUI(const myMat &)), this, SLOT(updatelblAux(const myMat &)), Qt::QueuedConnection);
            mTest_Basler->m_start = true;
            usleep(10000);
            delete mTest_IDS; mTest_IDS = NULL;
        }
        //cout << "h\n";
        thread_aux->start();
        ui->pbOnline->setEnabled(true);
        //ui->pbOffline->setEnabled(true);

        auxInitialized = true;
        const QString msg1 = "Ready to go for online evaluation";
        ui->label_status->clear();
        ui->label_status->setText(msg1);
    }
    else
    {
        //cout << "i\n";
        if(!auxInitialized)
        {
            const string msg = "Auxiliary camera not found. Can't run online evaluation";
            ui->label_status->clear();
            ui->label_status->setText(QString::fromStdString(msg));
            delete mTest_IDS; mTest_IDS = NULL;
            delete mTest_Basler; mTest_Basler = NULL;
            delete thread_aux; thread_aux = NULL;
            return false;
        }
    }
    //cout << "j\n";
    return true;
}


void settings_main::keyPressEvent(QKeyEvent* event)
{
    QString key =  event->text();
    if(key == "\r" && !mouseDrag && ui->radioBoundingBox->isChecked() && ui->radioBoundingBox->isEnabled() && boundingRectangle.x() != -1)
    {
        //scene_aux->clear();
        scene_aux->addPixmap(QPixmap::fromImage(AuxImg));
        ui->view_aux->show();
    }
    else
    {
        //qDebug() << "Any other key is pressed \n";
    }
}
void settings_main::updatelblAux(const myMat &lblImg)
{
    //cvtColor(lblImg, AuxImg, CV_BGR2RGB);
    AuxImg_full = lblImg.clone();
    cv::resize(lblImg, img3u_disp, img3u_disp.size());
    AuxImg =  QImage((uchar*)img3u_disp.data, SmallRect_Width, SmallRect_Height, img3u_disp.step, QImage::Format_RGB888);
    scene_aux->clear();
    scene_aux->addPixmap(QPixmap::fromImage(AuxImg));
    if(showOverlay)
    {
        for(int i = 0; i < pegs_small.size(); i++)
        {

            QRect r(pegs_small[i].x()/4, pegs_small[i].y()/4, pegs_small[i].width()/4, pegs_small[i].height()/4);
            scene_aux->addRect(r, QPen(QColor(255, 255,0)));
            //r.setRect(pegs_big[i].x()/4, pegs_big[i].y()/4, pegs_big[i].width()/4, pegs_big[i].height()/4);
            //scene_aux->addRect(r, QPen(QColor(255, 0,255)));
        }
    }
    if(thread_aux->isRunning())
    {
        if(ui->tabWidget->currentIndex() == 0)
        {
            //ui->label_aux->setPixmap(QPixmap::fromImage(qimg));
            ui->view_aux->setScene(scene_aux);
            ui->view_aux->show();
        }
        else if(ui->tabWidget->currentIndex() == 1)
        {
            //ui->label_aux_2->setPixmap(QPixmap::fromImage(qimg));
            ui->view_aux_2->setScene(scene_aux);
            ui->view_aux_2->show();
        }
    }
}

void settings_main::updatelblEndo(const myMat &lblImg)
{
    cvtColor(lblImg, EndoImg, CV_BGR2RGB);
    cv::resize(EndoImg, img3u_disp1, img3u_disp1.size());
    QImage qimg((uchar*)img3u_disp1.data, SmallRect_Width, SmallRect_Height, img3u_disp1.step, QImage::Format_RGB888);

    scene_endo->addPixmap(QPixmap::fromImage(qimg));
    if(thread_endo->isRunning())
    {
        if(ui->tabWidget->currentIndex() == 0)
        {
            //ui->label_endo->setPixmap(QPixmap::fromImage(qimg));
            ui->view_endo->setScene(scene_endo);
            ui->view_endo->show();
        }
        else if(ui->tabWidget->currentIndex() == 1)
        {
            //ui->label_endo_2->setPixmap(QPixmap::fromImage(qimg));
            ui->view_endo_2->setScene(scene_endo);
            ui->view_endo_2->show();
        }
        else if(ui->tabWidget->currentIndex() == 2)
        {
            //ui->label_endo_3->setPixmap(QPixmap::fromImage(qimg));
            ui->view_endo_3->setScene(scene_endo);
            ui->view_endo_3->show();
        }
    }
}


void settings_main::on_tabWidget_tabBarClicked(int index)
{
    if(index == 0)
    {
        if(!camEndoFound)
        {
            const QString msg = "Endoscopy camera not found.Can't run online evaluation";
            ui->label_status->clear();
            ui->label_status->setText(msg);
            ui->pbOnline->setEnabled(false);
        }
        else if(!(camAuxFound))
        {
            const QString msg = "Auxiliary camera not found.Can't run offline evaluation";
            ui->label_status->clear();
            ui->label_status->setText(msg);
            ui->pbOnline->setEnabled(false);
        }
        else
        {
            const QString msg = "Ready to go for online evaluation";
            ui->label_status->clear();
            ui->label_status->setText(msg);
            ui->pbOnline->setEnabled(true);
        }
    }
    else if (index == 1)
    {
        if(!camEndoFound)
        {
            const QString msg = "Endoscopy camera not found.Can't record activity";
            ui->label_status->clear();
            ui->label_status->setText(msg);
            ui->pbOffline->setEnabled(false);
        }
        else if(!(camAuxFound))
        {
            const QString msg = "Auxiliary camera not found.Can't record activity";
            ui->label_status->clear();
            ui->label_status->setText(msg);
            ui->pbOffline->setEnabled(false);
        }
        else
        {
            //const QString msg = "Press Record for the recording";
            //ui->label_status->clear();
            //ui->label_status->setText(msg);
            //ui->pbOffline->setEnabled(true);
        }
    }
    else if(index == 2)
    {
         if(!camEndoFound)
         {
             const QString msg = "Endoscopy camera not found.Can't go to practise session";
             ui->label_status->clear();
             ui->label_status->setText(msg);
             ui->pbPractice->setEnabled(false);
         }
         else if(!(camAuxFound))
         {
             const QString msg = "Auxiliary camera not found.Can't go to practise session";
             ui->label_status->clear();
             ui->label_status->setText(msg);
             ui->pbPractice->setEnabled(false);
         }
         else
         {
             const QString msg = "Ready to go for Practice session";
             ui->label_status->clear();
             ui->label_status->setText(msg);
             ui->pbPractice->setEnabled(true);
         }
    }
    else if(index == 3)
    {
        ui->boxName->clear();
        QSqlQuery query;
        query.prepare("SELECT * FROM nameID");
        resultQry = query.exec();
        int counter = 0;
        QVector<QString> names;
        names.clear();
        if(resultQry)
        {
            while(query.next())
            {
                QString pp = QString::number(++counter) + ". " + query.value(1).toString() + "(" + query.value(0).toString() + ")";
                names.push_back(pp);
            }
            for(int i = names.size()-1; i >= 0; --i)
            {
                ui->cmbName->addItem(names[i]);
            }
        }
        else
        {
            QMessageBox::critical(this, tr("Error"), "Nothing in the database");
            qDebug() << "DB error:  " << query.lastError();
            return;
        }
    }
}

void settings_main::on_listWidgetEndoOnline_clicked(const QModelIndex &index)
{
    if(camEndoFound)
    {
        mTest_USB->m_start = true;
    }
}

void settings_main::on_listWidgetAuxOnline_clicked(const QModelIndex &index)
{

    if(camAuxFound)
    {
        if(devAux == "basler")
        {
            mTest_Basler->m_start = true;
        }
        else if (devAux == "ids")
        {
            mTest_IDS->m_start = true;
        }
    }
}

void settings_main::on_listWidgetAuxOffline_clicked(const QModelIndex &index)
{
    if(camAuxFound)
    {
        if(devAux == "basler")
        {
            mTest_Basler->m_start = true;
        }
        else if (devAux == "ids")
        {
            mTest_IDS->m_start = true;
        }
    }
}

void settings_main::on_listWidgetEndoOffline_clicked(const QModelIndex &index)
{
    if(camEndoFound)
    {
        mTest_USB->m_start = true;
    }
}

void settings_main::on_listWidgetPractice_clicked(const QModelIndex &index)
{
    if(camEndoFound)
    {
        mTest_USB->m_start = true;
    }
}


void settings_main::on_pbPractice_clicked()
{
    cleanup();
    string DrName = ui->boxName->currentText().toUtf8().constData();
    int level = ui->selectLevel->currentIndex();
    string experimentType = ui->boxType->currentText().toStdString();
    string details        = ui->txtDetails->text().toStdString();
    //this->setVisible(false);
    clearUI();
    mainWindow = new qMainWindow(parameters, "practice", level, DrName, devAux, boundingRectangle,
                                 pegs_small, pegs_big,endoDB, withoutRing_smallRectThresh, withoutRing_bigRectThresh,
                                 withRing_smallRectThresh, withRing_bigRectThresh,
                                 experimentType, details, false, false, false, false, ring_segment, tool_segment);
    mainWindow->setWindowTitle("Neuro-Endo-Trainer");
    mainWindow->setAttribute(Qt::WA_DeleteOnClose, true);
    mainWindow->showMaximized();
    mainWindow->show();
}

bool settings_main::checkSettings()
{
    if(!QDir(QString::fromStdString(parameters.cap_paths)).exists())
    {
        QMessageBox::critical(this, tr("Error"), "Capture path doesn't exist. Set the capture path in the Settings.");
        return false;
    }
    if(ui->boxName->count() == 0)
    {
        QMessageBox::critical(this, tr("Error"), "No users in the database. Add users in the Settings");
        return false;
    }

    if(ui->txtDetails->text() == "")
    {
        QMessageBox::critical(this, tr("Error"), "Provide details of the experiement.");
        return false;
    }
    return true;
}

void settings_main::on_pbOnline_clicked()
{
    if(!checkSettings())
    {
        return;
    }
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Ready to go", "Have you selected the right settings. You sure to proceed?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        closeSerialPort();
        cleanup();
        string DrName = ui->boxName->currentText().toStdString();
        int level = ui->selectLevel->currentIndex();
        bool recordEndo = ui->checkBoxRecordEndo->isChecked();
        bool recordAux  = ui->checkBoxRecordAux->isChecked();
        string experimentType = ui->boxType->currentText().toStdString();
        string details        = ui->txtDetails->text().toStdString();

        //this->setVisible(false);
        clearUI();//parameters, "online", level, DrName, devAux, boundingRectangle, pegs, recordEndo, recordAux
        mainWindow = new qMainWindow(parameters, "online", level, DrName, devAux, boundingRectangle,
                                     pegs_small, pegs_big, endoDB,
                                     withoutRing_smallRectThresh, withoutRing_bigRectThresh,
                                     withRing_smallRectThresh, withRing_bigRectThresh,
                                     experimentType, details,
                                     recordEndo, recordAux, false, false, ring_segment, tool_segment);
        mainWindow->setWindowTitle("Neuro-Endo-Trainer");
        mainWindow->setAttribute(Qt::WA_DeleteOnClose, true);
        mainWindow->showMaximized();
        mainWindow->show();
    }

}

void settings_main::on_pbOffline_clicked()
{
    if(!checkSettings())
    {
        return;
    }
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Upload project", "Have you selected the right settings. You sure to proceed?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        writeData("z\n");
        usleep(1000);
        cleanup();
        string DrName = ui->boxName->currentText().toUtf8().constData();
        int level = ui->selectLevel->currentIndex();
        bool recordEndo = ui->checkBoxRecordEndo->isChecked();
        bool recordAux  = ui->checkBoxRecordAux->isChecked();
        string experimentType = ui->boxType->currentText().toStdString();
        string details        = ui->txtDetails->text().toStdString();
        //this->setVisible(false);
        clearUI();
        mainWindow = new qMainWindow(parameters, "record", level, DrName, devAux, boundingRectangle,
                                     pegs_small, pegs_big, endoDB,
                                     withoutRing_smallRectThresh, withoutRing_bigRectThresh,
                                     withRing_smallRectThresh, withRing_bigRectThresh,
                                     experimentType, details,recordEndo, recordAux,
                                     false, false, ring_segment, tool_segment);
        mainWindow->setWindowTitle("Neuro-Endo-Trainer");
        mainWindow->setAttribute(Qt::WA_DeleteOnClose, true);
        mainWindow->showMaximized();
        mainWindow->show();
    }
}


void settings_main::cleanup()
{
    cout << "cleanup triggered \n";
    writeData("z\n");
    usleep(1000);
    closeSerialPort();
    if(camAuxFound)
    {
        if(devAux == "basler")
        {
            cout << "cleaning basler camera \n";
            if(mTest_Basler != NULL)
            {
                mTest_Basler->m_abort = true;
            }
            usleep(100000);
            if(thread_aux->isRunning())
                thread_aux->quit();
            usleep(500000);
            //delete thread_aux;
            if(mTest_Basler != NULL)
            {
                delete mTest_Basler;
                mTest_Basler = NULL;
            }

        }
        else if (devAux == "ids")
        {
            cout << "cleaning ids camera\n";
            if(mTest_IDS != NULL)
            {
                mTest_IDS->m_abort = true;
            }
            usleep(100000);
            if(thread_aux->isRunning())
                thread_aux->quit();
            usleep(500000);
            //delete thread_aux;
            if(mTest_IDS != NULL)
            {
                delete mTest_IDS;
                mTest_IDS = NULL;
            }
        }
    }
    if(camEndoFound)
    {
        cout << "cleaning endo camera\n";
        if(mTest_USB != NULL)
        {
            mTest_USB->m_abort = true;
        }
        usleep(100000);
        if(thread_endo->isRunning())
            thread_endo->quit();
        usleep(500000);
        //delete thread_endo;
        if(mTest_USB != NULL)
        {
            delete mTest_USB;
            mTest_USB = NULL;
        }
    }
}

void settings_main::on_pbQuit_clicked()
{
    QApplication::instance()->exit();
}

settings_main::~settings_main()
{
    // ""

    cout << "Destructor Triggered \n";
    cleanup();
    delete scene_aux ;
    delete scene_endo ;
    delete ui;
}

void settings_main::on_pbRefresh_clicked()
{
    initialSetup();
}
void settings_main::openSettingsDialog()
{
    mSettings->exec();
}

void settings_main::updateParameters(const params &params)
{
    this->parameters = params;
    updateNames();
}
void settings_main::on_checkCalib_clicked(bool checked)
{
    if(checked)
    {
        //mTest_Basler->m_pause = true;
        ui->groupBox_2->show();
        usleep(100000);
        ui->comboSelectLevel->setEnabled(true);
        ui->comboSelectLevel->setCurrentIndex(0);
        writeData("s\n");
        writeData("y\n");
        ui->label_status->clear();
        ui->label_status->setText("Select the plate angle");
    }
    else
    {
        //mTest_Basler->m_pause = false;
        ui->radioBoundingBox->setEnabled(false);
        ui->groupBox_2->hide();
    }
}


void settings_main::on_radioPegSegment_clicked(bool checked)
{
    //mTest_Basler->m_pause = false;
    //usleep(100000);
    //mTest_Basler->m_pause = true;
    if(checked)
    {
        segment_peg = true;
        ui->label_status->clear();
        ui->label_status->setText("Place all the rings. Click near the peg 1 and click");
        ui->btnPegSegment->setEnabled(true);
    }
    else
    {
        segment_peg = false;
    }
}

void settings_main::on_radioRingSegment_clicked(bool checked)
{
    scene_aux->clear();
    scene_aux->addPixmap(QPixmap::fromImage(AuxImg));
    segment_ring = checked;
    ui->btnRingSegment->setEnabled(true);
    on_sliderRingSegment_valueChanged(0);
}

void settings_main::on_radioToolTipSegment_clicked(bool checked)
{
    //mTest_Basler->m_pause = false;
    usleep(1000);
    ui->label_status->clear();
    ui->label_status->setText("Bring the tool and change the slider");
    ui->btnToolSegment->setEnabled(true);
    scene_aux->clear();
    scene_aux->addPixmap(QPixmap::fromImage(AuxImg));
    segment_tool = checked;
}


void settings_main::on_checkBox_3_clicked(bool checked)
{
    if(checked)
    {
        ui->pbOnline->setEnabled(true);
    }
    else
    {
        ui->pbOnline->setEnabled(false);
    }
}



//void settings_main::on_sliderPegSegment_valueChanged(int value)
//{
//    cv::Mat element[1];
//    Mat im1, fgMaskPeg;
//    Mat channel[3];
//    element[0] = getStructuringElement(MORPH_ELLIPSE, Size(8, 8), Point(0, 0));
//    if(ui->radioPegSegment->isChecked())
//    {
//        //ui->label_status->clear();
//        //ui->label_status->setText("val is " + QString::number(value));
//        //Mat im1 = img3u_disp.clone();
//        cv::medianBlur(AuxImg_full, AuxImg_full, 3);
//        cvtColor(AuxImg_full, im1,  CV_RGB2HSV);
//        split(im1, channel);
//        inRange(im1, cv::Scalar(0, 50, 50), cv::Scalar(value, 250, 250), fgMaskPeg);
//        Rect r = cv::Rect(boundingRectangle.x(), boundingRectangle.y(), boundingRectangle.width(), boundingRectangle.height());
//        for (int y = 0; y < fgMaskPeg.rows; y++)
//        {
//            for (int x = 0; x < fgMaskPeg.cols; x++)
//            {
//                if (!(x >= r.tl().x && x <= r.br().x && y >= r.tl().y && y <= r.br().y))
//                {
//                    fgMaskPeg.at<uchar>(Point(x, y)) = 0;
//                }
//            }
//        }

//        erode(fgMaskPeg, fgMaskPeg, element[0]);
//        dilate(fgMaskPeg, fgMaskPeg, element[0]);
//        erode(fgMaskPeg, fgMaskPeg, element[0]);
//        dilate(fgMaskPeg, fgMaskPeg, element[0]);

//        cv::resize(fgMaskPeg, img3u_disp, img3u_disp.size());
//        AuxImg =  QImage((uchar*)img3u_disp.data, 350, 280, img3u_disp.step, QImage::Format_Grayscale8);
//        //AuxImg =  QImage((uchar*)img3u_disp.data, 350, 280, img3u_disp.step, QImage::Format_RGB888);
//        scene_aux->clear();
//        scene_aux->addPixmap(QPixmap::fromImage(AuxImg));
//    }
//}

void settings_main::on_btnBoundingBox_clicked()
{
    ui->radioBoundingBox->setEnabled(false);
    ui->btnBoundingBox->setEnabled(false);

    ui->radioRingSegment->setEnabled(true);
    ui->sliderRingSegment->setEnabled(true);
    boundingRectangle.setRect(boundingRectangle.x()*RatioRect, boundingRectangle.y()*RatioRect, boundingRectangle.width()*RatioRect, boundingRectangle.height()*RatioRect);
}

cv::Rect settings_main::rect(const QRect &r)
{
    return cv::Rect(r.x(), r.y(), r.width(), r.height());
}

double settings_main::sumAfterRingSegment(const cv::Mat &img, int value, const QRect &r)
{
    Mat diff_hsv, mask_out;
    Mat im1 = img.clone();
    cv::Mat im = im1(rect(r));

    cv::medianBlur(im, im, 3);
    cvtColor(im, diff_hsv, CV_RGB2HSV);
    Mat channel[3];
    split(diff_hsv, channel);

    ////Mat fgMaskRing;
    cv::threshold(channel[0], mask_out, value, 255, THRESH_TOZERO_INV); //b1((b1 >= T))= 0;
    cv::threshold(mask_out, mask_out, 1, 255, THRESH_BINARY); //b1((b1 > 0))= 255;


    erode(mask_out, mask_out, element[2]);
    dilate(mask_out, mask_out, element[0]);
    erode(mask_out, mask_out, element[2]);
    dilate(mask_out, mask_out, element[0]);

    //imshow("temp-mask_out", mask_out);
    double s = cv::sum(mask_out)[0];
    return s;
}

void settings_main::on_btnPegSegment_clicked()
{
    if(ui->btnPegSegment->text() == "Place Ring at 1 and click")
    {
        ui->btnPegSegment->setText("Place Ring at 2 and click");
        writeData("b\n");
        QRect r, r1;
        r.setRect(temp_rect.x()*RatioRect, temp_rect.y()*RatioRect, temp_rect.width()*RatioRect, temp_rect.height()*RatioRect);
        r1.setRect(temp_rectBig.x()*RatioRect, temp_rectBig.y()*RatioRect, temp_rectBig.width()*RatioRect, temp_rectBig.height()*RatioRect);
        double sum_small = sumAfterRingSegment(AuxImg_full, ring_segment, r);
        double sum_big = sumAfterRingSegment(AuxImg_full, ring_segment, r1);
        pegs_small[0] = r;
        pegs_big[0] = r1;
        withRingThresh[0] = make_pair(sum_small, sum_big);
        qDebug()<< "sum -> " << sum_small << " " << sum_big << endl;
        ui->label_status->clear();
        ui->label_status->setText("Click near the peg 2 and click");
    }
    else if(ui->btnPegSegment->text() == "Place Ring at 2 and click")
    {
        ui->btnPegSegment->setText("Place Ring at 3 and click");
        writeData("c\n");
        QRect r,r1;
        r.setRect(temp_rect.x()*RatioRect, temp_rect.y()*RatioRect, temp_rect.width()*RatioRect, temp_rect.height()*RatioRect);
        r1.setRect(temp_rectBig.x()*RatioRect, temp_rectBig.y()*RatioRect, temp_rectBig.width()*RatioRect, temp_rectBig.height()*RatioRect);
        double sum_small = sumAfterRingSegment(AuxImg_full, ring_segment, r);
        double sum_big = sumAfterRingSegment(AuxImg_full, ring_segment, r1);
        pegs_small[1] = r;
        pegs_big[1] = r1;
        withRingThresh[1] = make_pair(sum_small, sum_big);
        qDebug() << "sum -> " << sum_small << " " << sum_big << endl;
        ui->label_status->clear();
        ui->label_status->setText("Click near the peg 3 and click");
    }
    else if(ui->btnPegSegment->text() == "Place Ring at 3 and click")
    {
        ui->btnPegSegment->setText("Place Ring at 4 and click");
        writeData("d\n");
        QRect r,r1;
        r.setRect(temp_rect.x()*RatioRect, temp_rect.y()*RatioRect, temp_rect.width()*RatioRect, temp_rect.height()*RatioRect);
        r1.setRect(temp_rectBig.x()*RatioRect, temp_rectBig.y()*RatioRect, temp_rectBig.width()*RatioRect, temp_rectBig.height()*RatioRect);
        double sum_small = sumAfterRingSegment(AuxImg_full, ring_segment, r);
        double sum_big = sumAfterRingSegment(AuxImg_full, ring_segment, r1);
        pegs_small[2] = r;
        pegs_big[2] = r1;
        withRingThresh[2] = make_pair(sum_small, sum_big);
        qDebug() << "sum -> " << sum_small << " " << sum_big << endl;
        ui->label_status->clear();
        ui->label_status->setText("Click near the peg 4 and click");
    }
    else if(ui->btnPegSegment->text() == "Place Ring at 4 and click")
    {
        ui->btnPegSegment->setText("Place Ring at 5 and click");
        writeData("e\n");
        QRect r,r1;
        r.setRect(temp_rect.x()*RatioRect, temp_rect.y()*RatioRect, temp_rect.width()*RatioRect, temp_rect.height()*RatioRect);
        r1.setRect(temp_rectBig.x()*RatioRect, temp_rectBig.y()*RatioRect, temp_rectBig.width()*RatioRect, temp_rectBig.height()*RatioRect);
        double sum_small = sumAfterRingSegment(AuxImg_full, ring_segment, r);
        double sum_big = sumAfterRingSegment(AuxImg_full, ring_segment, r1);
        pegs_small[3] = r;
        pegs_big[3] = r1;
        withRingThresh[3] = make_pair(sum_small, sum_big);
        qDebug() << "sum -> " << sum_small << " " << sum_big << endl;
        ui->label_status->clear();
        ui->label_status->setText("Click near the peg 5 and click");
    }
    else if(ui->btnPegSegment->text() == "Place Ring at 5 and click")
    {
        ui->btnPegSegment->setText("Place Ring at 6 and click");
        writeData("f\n");
        QRect r,r1;
        r.setRect(temp_rect.x()*RatioRect, temp_rect.y()*RatioRect, temp_rect.width()*RatioRect, temp_rect.height()*RatioRect);
        r1.setRect(temp_rectBig.x()*RatioRect, temp_rectBig.y()*RatioRect, temp_rectBig.width()*RatioRect, temp_rectBig.height()*RatioRect);
        double sum_small = sumAfterRingSegment(AuxImg_full, ring_segment, r);
        double sum_big = sumAfterRingSegment(AuxImg_full, ring_segment, r1);
        pegs_small[4] = r;
        pegs_big[4] = r1;
        withRingThresh[4] = make_pair(sum_small, sum_big);
        qDebug() << "sum -> " << sum_small << " " << sum_big << endl;
        ui->label_status->clear();
        ui->label_status->setText("Place Ring at 6 and click");
    }
    else if(ui->btnPegSegment->text() == "Place Ring at 6 and click")
    {
        ui->btnPegSegment->setText("Place Ring at 7 and click");
        writeData("g\n");
        QRect r,r1;
        r.setRect(temp_rect.x()*RatioRect, temp_rect.y()*RatioRect, temp_rect.width()*RatioRect, temp_rect.height()*RatioRect);
        r1.setRect(temp_rectBig.x()*RatioRect, temp_rectBig.y()*RatioRect, temp_rectBig.width()*RatioRect, temp_rectBig.height()*RatioRect);
        double sum_small = sumAfterRingSegment(AuxImg_full, ring_segment, r);
        double sum_big = sumAfterRingSegment(AuxImg_full, ring_segment, r1);
        pegs_small[5] = r;
        pegs_big[5] = r1;
        withRingThresh[5] = make_pair(sum_small, sum_big);
        qDebug() << "sum -> " << sum_small << " " << sum_big << endl;
        ui->label_status->clear();
        ui->label_status->setText("Click near the peg 7 and click");
    }
    else if(ui->btnPegSegment->text() == "Place Ring at 7 and click")
    {
        ui->btnPegSegment->setText("Place Ring at 8 and click");
        writeData("h\n");
        QRect r,r1;
        r.setRect(temp_rect.x()*RatioRect, temp_rect.y()*RatioRect, temp_rect.width()*RatioRect, temp_rect.height()*RatioRect);
        r1.setRect(temp_rectBig.x()*RatioRect, temp_rectBig.y()*RatioRect, temp_rectBig.width()*RatioRect, temp_rectBig.height()*RatioRect);
        double sum_small = sumAfterRingSegment(AuxImg_full, ring_segment, r);
        double sum_big = sumAfterRingSegment(AuxImg_full, ring_segment, r1);
        pegs_small[6] = r;
        pegs_big[6] = r1;
        withRingThresh[6] = make_pair(sum_small, sum_big);
        qDebug() << "sum -> " << sum_small << " " << sum_big << endl;
        ui->label_status->clear();
        ui->label_status->setText("Click near the peg 8 and click");
    }
    else if(ui->btnPegSegment->text() == "Place Ring at 8 and click")
    {
        ui->btnPegSegment->setText("Place Ring at 9 and click");
        writeData("i\n");
        QRect r,r1;
        r.setRect(temp_rect.x()*RatioRect, temp_rect.y()*RatioRect, temp_rect.width()*RatioRect, temp_rect.height()*RatioRect);
        r1.setRect(temp_rectBig.x()*RatioRect, temp_rectBig.y()*RatioRect, temp_rectBig.width()*RatioRect, temp_rectBig.height()*RatioRect);
        double sum_small = sumAfterRingSegment(AuxImg_full, ring_segment, r);
        double sum_big = sumAfterRingSegment(AuxImg_full, ring_segment, r1);
        pegs_small[7] = r;
        pegs_big[7] = r1;
        withRingThresh[7] = make_pair(sum_small, sum_big);
        qDebug() << "sum -> " << sum_small << " " << sum_big << endl;
        ui->label_status->clear();
        ui->label_status->setText("Click near the peg 9 and click");
    }
    else if(ui->btnPegSegment->text() == "Place Ring at 9 and click")
    {
        ui->btnPegSegment->setText("Place Ring at 10 and click");
        writeData("j\n");
        QRect r,r1;
        r.setRect(temp_rect.x()*RatioRect, temp_rect.y()*RatioRect, temp_rect.width()*RatioRect, temp_rect.height()*RatioRect);
        r1.setRect(temp_rectBig.x()*RatioRect, temp_rectBig.y()*RatioRect, temp_rectBig.width()*RatioRect, temp_rectBig.height()*RatioRect);
        double sum_small = sumAfterRingSegment(AuxImg_full, ring_segment, r);
        double sum_big = sumAfterRingSegment(AuxImg_full, ring_segment, r1);
        pegs_small[8] = r;
        pegs_big[8] = r1;
        withRingThresh[8] = make_pair(sum_small, sum_big);
        qDebug() << "sum -> " << sum_small << " " << sum_big << endl;
        ui->label_status->clear();
        ui->label_status->setText("Click near the peg 10 and click");
    }
    else if(ui->btnPegSegment->text() == "Place Ring at 10 and click")
    {
        ui->btnPegSegment->setText("Place Ring at 11 and click");
        writeData("k\n");
        QRect r,r1;
        r.setRect(temp_rect.x()*RatioRect, temp_rect.y()*RatioRect, temp_rect.width()*RatioRect, temp_rect.height()*RatioRect);
        r1.setRect(temp_rectBig.x()*RatioRect, temp_rectBig.y()*RatioRect, temp_rectBig.width()*RatioRect, temp_rectBig.height()*RatioRect);
        double sum_small = sumAfterRingSegment(AuxImg_full, ring_segment, r);
        double sum_big = sumAfterRingSegment(AuxImg_full, ring_segment, r1);
        pegs_small[9] = r;
        pegs_big[9] = r1;
        qDebug() << "sum -> " << sum_small << " " << sum_big << endl;
        withRingThresh[9] = make_pair(sum_small, sum_big);
        ui->label_status->clear();
        ui->label_status->setText("Click near the peg 11 and click");
    }
    else if(ui->btnPegSegment->text() == "Place Ring at 11 and click")
    {
        ui->btnPegSegment->setText("Place Ring at 12 and click");
        writeData("l\n");
        QRect r,r1;
        r.setRect(temp_rect.x()*RatioRect, temp_rect.y()*RatioRect, temp_rect.width()*RatioRect, temp_rect.height()*RatioRect);
        r1.setRect(temp_rectBig.x()*RatioRect, temp_rectBig.y()*RatioRect, temp_rectBig.width()*RatioRect, temp_rectBig.height()*RatioRect);
        double sum_small = sumAfterRingSegment(AuxImg_full, ring_segment, r);
        double sum_big = sumAfterRingSegment(AuxImg_full, ring_segment, r1);
        pegs_small[10] = r;
        pegs_big[10] = r1;
        qDebug() << "sum -> " << sum_small << " " << sum_big << endl;
        withRingThresh[10] = make_pair(sum_small, sum_big);
        ui->label_status->clear();
        ui->label_status->setText("Click near the peg 12 and click");
    }
    else if(ui->btnPegSegment->text() == "Place Ring at 12 and click")
    {
        ui->btnPegSegment->setText("Remove all the rings and click");
        QRect r,r1;
        r.setRect(temp_rect.x()*RatioRect, temp_rect.y()*RatioRect, temp_rect.width()*RatioRect, temp_rect.height()*RatioRect);
        r1.setRect(temp_rectBig.x()*RatioRect, temp_rectBig.y()*RatioRect, temp_rectBig.width()*RatioRect, temp_rectBig.height()*RatioRect);
        double sum_small = sumAfterRingSegment(AuxImg_full, ring_segment, r);
        double sum_big = sumAfterRingSegment(AuxImg_full, ring_segment, r1);
        pegs_small[11] = r;
        pegs_big[11] = r1;
        qDebug() << "sum -> " << sum_small << " " << sum_big << endl;
        withRingThresh[11] = make_pair(sum_small, sum_big);
        ui->label_status->clear();
        ui->label_status->setText("Peg segmenation done. Do the Ring Segmentation");
    }
    else if(ui->btnPegSegment->text() == "Remove all the rings and click")
    {
        //mTest_Basler->m_pause = false;
        //usleep(100000);
        //mTest_Basler->m_pause = true;
        ui->btnPegSegment->setText("Done");
        for(int i = 0; i < pegs_big.size(); i++)
        {
            QRect r = pegs_small[i];
            QRect r1 = pegs_big[i];
            double sum_small = sumAfterRingSegment(AuxImg_full, ring_segment, r);
            double sum_big = sumAfterRingSegment(AuxImg_full, ring_segment, r1);
            qDebug() << "sum w/o-> " << sum_small << " " << sum_big << endl;
            withoutRingThresh[i] = make_pair(sum_small, sum_big);
        }
        ui->label_status->clear();
        ui->label_status->setText("Peg segmenation done. Do the Tool Segmentation");
        ui->btnPegSegment->setEnabled(false);
        ui->radioPegSegment->setEnabled(false);
        ui->radioToolTipSegment->setEnabled(true);
        ui->sliderToolSegment->setEnabled(true);
    }
}

void settings_main::ringSegment(const cv::Mat &img, int value)
{
    Mat diff_hsv, mask_out;
    Mat im = img.clone();

    cv::medianBlur(im, im, 3);
    cvtColor(im, diff_hsv, CV_RGB2HSV);
    Mat channel[3];
    split(diff_hsv, channel);

    ////Mat fgMaskRing;
    cv::threshold(channel[0], mask_out, value, 255, THRESH_TOZERO_INV); //b1((b1 >= T))= 0;
    cv::threshold(mask_out, mask_out, 1, 255, THRESH_BINARY); //b1((b1 > 0))= 255;


    erode(mask_out, mask_out, element[2]);
    dilate(mask_out, mask_out, element[0]);
    erode(mask_out, mask_out, element[2]);
    dilate(mask_out, mask_out, element[0]);

    Rect r = cv::Rect(boundingRectangle.x(), boundingRectangle.y(), boundingRectangle.width(), boundingRectangle.height());
    for (int y = 0; y < mask_out.rows; y++)
    {
        for (int x = 0; x < mask_out.cols; x++)
        {
            if (!(x >= r.tl().x && x <= r.br().x && y >= r.tl().y && y <= r.br().y))
            {
                mask_out.at<uchar>(Point(x, y)) = 0;
            }
        }
    }
    cv::resize(mask_out, img3u_disp, img3u_disp.size());
    AuxImg =  QImage((uchar*)img3u_disp.data, SmallRect_Width, SmallRect_Height, img3u_disp.step, QImage::Format_Grayscale8);
    //AuxImg =  QImage((uchar*)img3u_disp.data, 350, 280, img3u_disp.step, QImage::Format_RGB888);
    scene_aux->clear();
    scene_aux->addPixmap(QPixmap::fromImage(AuxImg));
}

void settings_main::on_sliderRingSegment_valueChanged(int value)
{
    if(segment_ring)
    {
        // absolute diffrence between successive frames
        ringSegment(AuxImg_full, value);
        ring_segment = value;
        qDebug() << "ring_segment value" << ring_segment << endl;
    }
}

void settings_main::on_btnRingSegment_clicked()
{
    ui->label_status->clear();
    ui->label_status->setText("Ring segmenation done. Do the Tool Segmentation");
    ui->btnRingSegment->setEnabled(false);
    ui->radioRingSegment->setEnabled(false);
    ui->sliderRingSegment->setEnabled(false);

    ui->radioPegSegment->setEnabled(true);
}

void settings_main::on_sliderToolSegment_valueChanged(int value)
{
    if(segment_tool)
    {
        //mTest_Basler->m_pause = true;
        usleep(1000);
        Mat diff_hsv, mask_out;
        cv::medianBlur(AuxImg_full, AuxImg_full, 3);
        cvtColor(AuxImg_full, diff_hsv, CV_RGB2HSV);
        //Mat channel[3];
        //split(diff_hsv, channel);


        inRange(diff_hsv, cv::Scalar(50, 130, 100), cv::Scalar(value, 255, 255), mask_out);

        ////Mat fgMaskRing;
//        cv::threshold(channel[0], mask_out, value, 255, THRESH_TOZERO_INV); //b1((b1 >= T))= 0;
//        cv::threshold(mask_out, mask_out, 1, 255, THRESH_BINARY); //b1((b1 > 0))= 255;


        erode(mask_out, mask_out, element[2]);
        dilate(mask_out, mask_out, element[0]);
        erode(mask_out, mask_out, element[2]);
        dilate(mask_out, mask_out, element[0]);


        cv::resize(mask_out, img3u_disp, img3u_disp.size());
        AuxImg =  QImage((uchar*)img3u_disp.data, SmallRect_Width, SmallRect_Height, img3u_disp.step, QImage::Format_Grayscale8);
        //AuxImg =  QImage((uchar*)img3u_disp.data, 350, 280, img3u_disp.step, QImage::Format_RGB888);
        scene_aux->clear();
        scene_aux->addPixmap(QPixmap::fromImage(AuxImg));
        tool_segment = value;
    }
}

void settings_main::on_btnToolSegment_clicked()
{
    mTest_Basler->m_pause = false;
    ui->label_status->clear();
    ui->label_status->setText("Calibration Done. Click Run to go for the Online Evaluation");
    ui->radioToolTipSegment->setEnabled(false);
    ui->btnToolSegment->setEnabled(false);
    ui->sliderToolSegment->setEnabled(false);
    QFile file(QDir::currentPath() + filename_auxCamCalib);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    out << "Bounding Rect,";
    out << boundingRectangle.x()<< "," << boundingRectangle.y()<< "," << boundingRectangle.width()<< "," <<  boundingRectangle.height() << endl;
    for(int i = 0; i < pegs_small.size(); i++)
    {
        out << "Pegs Rect small,";
        out << pegs_small[i].x()<< "," << pegs_small[i].y()<< "," << pegs_small[i].width()<< "," << pegs_small[i].height() << endl;
    }
    for(int i = 0; i < pegs_big.size(); i++)
    {
        out << "Pegs Rect big,";
        out << pegs_big[i].x()<< "," << pegs_big[i].y()<< "," << pegs_big[i].width()<< "," << pegs_big[i].height() << endl;
    }
    for(int i = 0; i < withRingThresh.size(); i++)
    {
        out << "with ring thresh,";
        out << withRingThresh[i].first<< "," << withRingThresh[i].second << endl;
    }
    for(int i = 0; i < withoutRingThresh.size(); i++)
    {
        out << "without ring thresh,";
        out << withoutRingThresh[i].first<< "," << withoutRingThresh[i].second << endl;
    }
    out << "Threshold Ring,";
    out << ring_segment << endl;
    out << "Threshold Tool,";
    out << tool_segment << endl;
    file.close();
}

void settings_main::on_boxType_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "Study")
    {
        ui->txtDetails->setText("");
        QMessageBox b;
        b.setText("Give name of the study in the Details.");
        b.exec();
    }
    else if(arg1 == "Conference")
    {
        ui->txtDetails->setText("");
        QMessageBox b;
        b.setText("Give name of the Conference in the Details.");
        b.exec();
    }
    else if(arg1 == "Regular")
    {
        ui->txtDetails->setText(QDate::currentDate().toString());
    }
}

void settings_main::on_comboSelectLevel_activated(int index)
{
    if(index == 0)
    {
        filename_auxCamCalib = "/calib_files/aux_CamCalib_Straight.txt";
        writeData("y\n");
        ui->radioBoundingBox->setEnabled(true);
        ui->comboSelectLevel->setEnabled(false);
        ui->label_status->clear();
        ui->label_status->setText("Draw the bounding box around the pegs and confirm");
        //usleep(3000000);
        //mTest_Basler->m_pause = true;
    }
    else if(index == 1)
    {
        filename_auxCamCalib = "/calib_files/aux_CamCalib_LeftTilt+15.txt";
        writeData("3\n");
        ui->radioBoundingBox->setEnabled(true);
        ui->comboSelectLevel->setEnabled(false);
        ui->label_status->clear();
        ui->label_status->setText("Draw the bounding box around the pegs and confirm");
        //usleep(3000000);
        //mTest_Basler->m_pause = true;
    }
    else if(index == 2)
    {
        filename_auxCamCalib = "/calib_files/aux_CamCalib_RightTilt-15.txt";
        writeData("4\n");
        ui->radioBoundingBox->setEnabled(true);
        ui->comboSelectLevel->setEnabled(false);
        ui->label_status->clear();
        ui->label_status->setText("Draw the bounding box around the pegs and confirm");
        //usleep(3000000);
        //mTest_Basler->m_pause = true;
    }
    else if(index == 3)
    {
        filename_auxCamCalib = "/calib_files/aux_CamCalib_LeftTilt+20.txt";
        writeData("5\n");
        ui->radioBoundingBox->setEnabled(true);
        ui->comboSelectLevel->setEnabled(false);
        ui->label_status->clear();
        ui->label_status->setText("Draw the bounding box around the pegs and confirm");
        //usleep(3000000);
        //mTest_Basler->m_pause = true;
    }
    else if(index == 4)
    {
        filename_auxCamCalib = "/calib_files/aux_CamCalib_RightTilt-20.txt";
        writeData("6\n");
        ui->radioBoundingBox->setEnabled(true);
        ui->comboSelectLevel->setEnabled(false);
        ui->label_status->clear();
        ui->label_status->setText("Draw the bounding box around the pegs and confirm");
        //usleep(3000000);
        //mTest_Basler->m_pause = true;
    }
    else if(index == 5)
    {
        filename_auxCamCalib = "/calib_files/aux_CamCalib_LeftTilt+30.txt";
        writeData("7\n");
        ui->radioBoundingBox->setEnabled(true);
        ui->comboSelectLevel->setEnabled(false);
        ui->label_status->clear();
        ui->label_status->setText("Draw the bounding box around the pegs and confirm");
        //usleep(3000000);
        //mTest_Basler->m_pause = true;
    }
    else if(index == 6)
    {
        filename_auxCamCalib = "/calib_files/aux_CamCalib_RightTilt-30.txt";
        writeData("8\n");
        ui->radioBoundingBox->setEnabled(true);
        ui->comboSelectLevel->setEnabled(false);
        ui->label_status->clear();
        ui->label_status->setText("Draw the bounding box around the pegs and confirm");
        //usleep(3000000);
        //mTest_Basler->m_pause = true;
    }
}

void settings_main::on_selectLevel_activated(int index)
{
    if(index == 0 || index == 7 || index == 14)
    {
        filename_auxCamCalib = "/calib_files/aux_CamCalib_Straight.txt";
        parse_AuxCamCalib(filename_auxCamCalib);
        writeData("s\n");
        writeData("y\n");
    }
    else if(index == 1 || index == 8 || index == 15)
    {
        filename_auxCamCalib = "/calib_files/aux_CamCalib_LeftTilt+15.txt";
        parse_AuxCamCalib(filename_auxCamCalib);
        writeData("s\n");
        writeData("3\n");
    }
    else if(index == 2 || index == 9 || index == 16)
    {
        filename_auxCamCalib = "/calib_files/aux_CamCalib_RightTilt-15.txt";
        parse_AuxCamCalib(filename_auxCamCalib);
        writeData("s\n");
        writeData("4\n");
    }
    else if(index == 3 || index == 10 || index == 17)
    {
        filename_auxCamCalib = "/calib_files/aux_CamCalib_LeftTilt+20.txt";
        parse_AuxCamCalib(filename_auxCamCalib);
        writeData("s\n");
        writeData("5\n");
    }
    else if(index == 4 || index == 11 || index == 18)
    {
        filename_auxCamCalib = "/calib_files/aux_CamCalib_RightTilt-20.txt";
        parse_AuxCamCalib(filename_auxCamCalib);
        writeData("s\n");
        writeData("6\n");
    }
    else if(index == 5 || index == 12 || index == 19)
    {
        filename_auxCamCalib = "/calib_files/aux_CamCalib_LeftTilt+30.txt";
        parse_AuxCamCalib(filename_auxCamCalib);
        writeData("s\n");
        writeData("7\n");
    }
    else if(index == 6 || index == 13 || index == 20)
    {
        filename_auxCamCalib = "/calib_files/aux_CamCalib_RightTilt-30.txt";
        parse_AuxCamCalib(filename_auxCamCalib);
        writeData("s\n");
        writeData("8\n");
    }
}

void settings_main::on_checkPauseVideo_clicked(bool checked)
{
    if(checked)
    {
        mTest_Basler->m_pause = true;
        usleep(1000);
    }
    else
    {
        mTest_Basler->m_pause = false;
        usleep(1000);
    }
}

void settings_main::on_checkOverlay_clicked(bool checked)
{
    showOverlay = checked;
}
