#include "settings.h"
#include "ui_settings.h"
//12-12-12
#include <QtSerialPort/QSerialPortInfo>

settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);

    dataStopped = false;
    serial = new QSerialPort(this);
    ui->baudRateBox->setInsertPolicy(QComboBox::NoInsert);

    ui->baudRateBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->baudRateBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->baudRateBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->baudRateBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);


    ui->dataBitsBox->addItem(QStringLiteral("8"), QSerialPort::Data8);
    ui->dataBitsBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    ui->dataBitsBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    ui->dataBitsBox->addItem(QStringLiteral("5"), QSerialPort::Data5);

    ui->parityBox->addItem(tr("None"), QSerialPort::NoParity);
    ui->parityBox->addItem(tr("Even"), QSerialPort::EvenParity);
    ui->parityBox->addItem(tr("Odd"), QSerialPort::OddParity);
    ui->parityBox->addItem(tr("Mark"), QSerialPort::MarkParity);
    ui->parityBox->addItem(tr("Space"), QSerialPort::SpaceParity);

    ui->stopBitsBox->addItem(QStringLiteral("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
    ui->stopBitsBox->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
#endif
    ui->stopBitsBox->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

    ui->flowControlBox->addItem(tr("None"), QSerialPort::NoFlowControl);
    ui->flowControlBox->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    ui->flowControlBox->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);


    ui->serialPortInfoListBox->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QStringList list;
        list << info.portName();
        ui->serialPortInfoListBox->addItem(list.first(), list);
    }

    connect(this, SIGNAL(enablePushButtonSig(bool)), this, SLOT(enablePushButtonSlot(bool)));
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));

//! [2]
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    //connect(serial, SIGNAL(readChannelFinished()), this, SLOT(readData()));

    calibCounter = -1;
    Ring_false.resize(12, 0);
    Ring_true.resize(12, 0);
//    vector<int> nos;
//    parseStringtoNumbers("CNO:278,1001,906,956,513,1007,997,352,978,962,1006,560,\r\n", nos, 12);
//    parseStringtoNumbers("C01:315\r\n", nos, 1);
//    for(int i = 0; i < nos.size(); ++i)
//    {
//        cout << "no->" << nos[i] << endl;
//    }

    updateSettings();
}

void settings::parseStringtoNumbers(const QString & str1, vector<int> &numbers, int numOfValues)
{
    numbers.clear();
    numbers.resize(numOfValues);
    int count = 0;
    QString str = str1;
    str.remove(0, 4);
    QStringList pieces = str.split( "," );
    foreach(QString num, pieces)
    {
        numbers[count++] = num.toInt();
        if(count == numOfValues)
            break;
    }
}


settings::~settings()
{
    closeSerialPort();
    delete ui;
    delete serial;
}

void settings::on_buttonBox_accepted()
{
    cout << "Update to parameters\n";
    params par;

    par.tr_name = ui->tr_nameTracker->text().toUtf8().constData();
    par.cap_auxCam = ui->cap_auxCam->text().toUtf8().constData();

    par.cap_binSize = ui->cap_binSize->text().toUInt();
    par.cap_camID_IDS = ui->cap_camID_IDS->text().toUInt();
    par.cap_colsAux = ui->cap_colsAux->text().toUtf8().toUInt();
    par.cap_fpsAux = ui->cap_fpsAux->text().toUtf8().toUInt();
    par.cap_fpsEndo = ui->cap_fps_endo->text().toUtf8().toUInt();
    par.cap_queueSize = ui->cap_queueSize->text().toUtf8().toUInt();
    par.cap_rowsAux = ui->cap_rowAux->text().toUtf8().toUInt();
    par.cap_rowsEndo = ui->cap_rows_endo->text().toUtf8().toUInt();


    // setting the capture path;
    par.cap_paths = ui->cap_path->text().toStdString();

    par.serial_name   = serial_settings.name ;
    par.serial_baudRate =  serial_settings.baudRate;
    par.serial_stringBaudRate = serial_settings.stringBaudRate;

    par.serial_dataBits = serial_settings.dataBits;
    par.serial_stringDataBits = serial_settings.stringDataBits ;

    par.serial_parity = serial_settings.parity ;
    par.serial_stringParity = serial_settings.stringParity ;

    par.serial_stopBits = serial_settings.stopBits ;
    par.serial_stringStopBits = serial_settings.stringStopBits ;

    par.serial_flowControl = serial_settings.flowControl ;
    par.serial_stringFlowControl = serial_settings.stringFlowControl ;

    emit makeUpdateParams(par);
    closeSerialPort();
}

void settings::on_buttonBox_rejected()
{
    closeSerialPort();
    cout << "No update to parameters\n";
}

void settings::updateSettings()
{
    serial_settings.name = ui->serialPortInfoListBox->currentText();
    serial_settings.baudRate = static_cast<QSerialPort::BaudRate>(ui->baudRateBox->itemData(ui->baudRateBox->currentIndex()).toInt());
    serial_settings.stringBaudRate = QString::number(serial_settings.baudRate);

    serial_settings.dataBits = static_cast<QSerialPort::DataBits>(ui->dataBitsBox->itemData(ui->dataBitsBox->currentIndex()).toInt());
    serial_settings.stringDataBits = ui->dataBitsBox->currentText();

    serial_settings.parity = static_cast<QSerialPort::Parity>(ui->parityBox->itemData(ui->parityBox->currentIndex()).toInt());
    serial_settings.stringParity = ui->parityBox->currentText();

    serial_settings.stopBits = static_cast<QSerialPort::StopBits>(ui->stopBitsBox->itemData(ui->stopBitsBox->currentIndex()).toInt());
    serial_settings.stringStopBits = ui->stopBitsBox->currentText();

    serial_settings.flowControl = static_cast<QSerialPort::FlowControl>(ui->flowControlBox->itemData(ui->flowControlBox->currentIndex()).toInt());
    serial_settings.stringFlowControl = ui->flowControlBox->currentText();

//    qDebug() << "serial_settings.name - " << serial_settings.name << endl;
//    qDebug() << "serial_settings.baudRate - " << serial_settings.baudRate << endl;
//    qDebug() << "serial_settings.stringBaudRate - " << serial_settings.stringBaudRate << endl;

//    qDebug() << "serial_settings.dataBits - " << serial_settings.dataBits << endl;
//    qDebug() << "serial_settings.stringDataBits - " << serial_settings.stringDataBits << endl;

//    qDebug() << "serial_settings.parity - " << serial_settings.parity << endl;
//    qDebug() << "serial_settings.stringParity - " << serial_settings.stringParity << endl;

//    qDebug() << "serial_settings.stopBits - " << serial_settings.stopBits << endl;
//    qDebug() << "serial_settings.stringStopBits - " << serial_settings.stringStopBits << endl;

//    qDebug() << "serial_settings.flowControl - " << serial_settings.flowControl << endl;
//    qDebug() << "serial_settings.stringFlowControl - " << serial_settings.stringFlowControl << endl;

}

void settings::readData()
{
//    usleep(1000);
//    serial_data = serial->readAll();
//    qDebug() << "data from the serial -> " << serial_data << endl;
    QByteArray data;
    while (serial->canReadLine())
    {
       data = serial->readLine();   //reads in data line by line, separated by \n or \r characters
       qDebug() << "data from the serial -> " << data << endl;
    }
    QString dataStr(data);
    QString dataStrPart = dataStr.mid(0,3);
    if(dataStrPart == "CNO")
    {
        CNO.push_back(dataStr);
        if(CNO.size() >= CALIB_BUF_SIZE_NoRing)
        {
            dataStopped = true;
        }
    }
    else if(dataStrPart == "C01")
    {
       C01.push_back(dataStr);
       qDebug() << "C01 size " << C01.size() <<endl;
       if(C01.size() >= CALIB_BUF_SIZE)
       {
           dataStopped = true;
       }
    }
    else if(dataStrPart == "C02")
    {
       C02.push_back(dataStr);
       qDebug() << "C02 size " << C02.size() <<endl;
       if(C02.size() >= CALIB_BUF_SIZE)
       {
           dataStopped = true;
       }
    }
    else if(dataStrPart == "C03")
    {
       C03.push_back(dataStr);
       qDebug() << "C03 size " << C03.size() <<endl;
       if(C03.size() >= CALIB_BUF_SIZE)
       {
           dataStopped = true;
       }
    }
    else if(dataStrPart == "C04")
    {
       C04.push_back(dataStr);
       qDebug() << "C04 size " << C04.size() <<endl;
       if(C04.size() >= CALIB_BUF_SIZE)
       {
           dataStopped = true;
       }
    }
    else if(dataStrPart == "C05")
    {
       C05.push_back(dataStr);
       qDebug() << "C05 size " << C05.size() <<endl;
       if(C05.size() >= CALIB_BUF_SIZE)
       {
           dataStopped = true;
       }
    }
    else if(dataStrPart == "C06")
    {
       C06.push_back(dataStr);
       qDebug() << "C06 size " << C06.size() <<endl;
       if(C06.size() >= CALIB_BUF_SIZE)
       {
           dataStopped = true;
       }
    }
    else if(dataStrPart == "C07")
    {
       C07.push_back(dataStr);
       qDebug() << "C07 size " << C07.size() <<endl;
       if(C07.size() >= CALIB_BUF_SIZE)
       {
           dataStopped = true;
       }
    }
    else if(dataStrPart == "C08")
    {
       C08.push_back(dataStr);
       qDebug() << "C08 size " << C08.size() <<endl;
       if(C08.size() >= CALIB_BUF_SIZE)
       {
           dataStopped = true;
       }
    }
    else if(dataStrPart == "C09")
    {
       C09.push_back(dataStr);
       qDebug() << "C09 size " << C09.size() <<endl;
       if(C09.size() >= CALIB_BUF_SIZE)
       {
           dataStopped = true;
       }
    }
    else if(dataStrPart == "C10")
    {
       C10.push_back(dataStr);
       qDebug() << "C10 size " << C10.size() <<endl;
       if(C10.size() >= CALIB_BUF_SIZE)
       {
           dataStopped = true;
       }
    }
    else if(dataStrPart == "C11")
    {
       C11.push_back(dataStr);
       qDebug() << "C11 size " << C11.size() <<endl;
       if(C11.size() >= CALIB_BUF_SIZE)
       {
           dataStopped = true;
       }
    }
    else if(dataStrPart == "C12")
    {
       C12.push_back(dataStr);
       qDebug() << "C12 size " << C12.size() <<endl;
       if(C12.size() >= CALIB_BUF_SIZE)
       {
           dataStopped = true;
       }
    }
    else if(dataStrPart == "Cal")
    {
        // first set of calibration done
        dataStopped = true;
    }
    emit enablePushButtonSig(dataStopped);
}

void settings::enablePushButtonSlot(bool val)
{
    //qDebug() << "val " << val << " calibCounter " << calibCounter << endl;
    if(val)
    {
        ui->btnCalib->setEnabled(true);
        dataStopped = false;

        if(calibCounter == 0)
        {
            ui->btnCalib->setText("Place Ring at position 1 and click");
            QPixmap pix(":/icons/endo-calib_1.png");
            ui->lblImg->setPixmap(pix);
        }
        else if(calibCounter == 1)
        {
            ui->btnCalib->setText("Place Ring at position 2 and click");
            QPixmap pix(":/icons/endo-calib_2.png");
            ui->lblImg->setPixmap(pix);
        }
        else if(calibCounter == 2)
        {
            ui->btnCalib->setText("Place Ring at position 3 and click");
            QPixmap pix(":/icons/endo-calib_3.png");
            ui->lblImg->setPixmap(pix);
        }
        else if(calibCounter == 3)
        {
            ui->btnCalib->setText("Place Ring at position 4 and click");
            QPixmap pix(":/icons/endo-calib_4.png");
            ui->lblImg->setPixmap(pix);
        }
        else if(calibCounter == 4)
        {
            ui->btnCalib->setText("Place Ring at position 5 and click");
            QPixmap pix(":/icons/endo-calib_5.png");
            ui->lblImg->setPixmap(pix);
        }
        else if(calibCounter == 5)
        {
            ui->btnCalib->setText("Place Ring at position 6 and click");
            QPixmap pix(":/icons/endo-calib_6.png");
            ui->lblImg->setPixmap(pix);
        }
        else if(calibCounter == 6)
        {
            ui->btnCalib->setText("Place Ring at position 7 and click");
            QPixmap pix(":/icons/endo-calib_7.png");
            ui->lblImg->setPixmap(pix);
        }
        else if(calibCounter == 7)
        {
            ui->btnCalib->setText("Place Ring at position 8 and click");
            QPixmap pix(":/icons/endo-calib_8.png");
            ui->lblImg->setPixmap(pix);
        }
        else if(calibCounter == 8)
        {
            ui->btnCalib->setText("Place Ring at position 9 and click");
            QPixmap pix(":/icons/endo-calib_9.png");
            ui->lblImg->setPixmap(pix);
        }
        else if(calibCounter == 9)
        {
            ui->btnCalib->setText("Place Ring at position 10 and click");
            QPixmap pix(":/icons/endo-calib_10.png");
            ui->lblImg->setPixmap(pix);
        }
        else if(calibCounter == 10)
        {
            ui->btnCalib->setText("Place Ring at position 11 and click");
            QPixmap pix(":/icons/endo-calib_11.png");
            ui->lblImg->setPixmap(pix);
        }
        else if(calibCounter == 11)
        {
            ui->btnCalib->setText("Place Ring at position 12 and click");
            QPixmap pix(":/icons/endo-calib_12.png");
            ui->lblImg->setPixmap(pix);
        }
        else if(calibCounter == 12)
        {
            ui->btnCalib->setText("Click to process calibration Data");
            QPixmap pix(":/icons/endo-calib_0.png");
            ui->lblImg->setPixmap(pix);
        }
        else if(calibCounter == 13)
        {
            ui->buttonBox->setEnabled(true);
            //closeSerialPort();
            ui->btnCalib->setText("Send the calibration data");
        }
    }
}

void settings::writeData(const QByteArray &data)
{
    serial->write(data);
}

void settings::sendSerialCommand(const QString & c)
{
    ui->btnCalib->setEnabled(false);
    QString s = c;
    QByteArray commandSerial = s.toLocal8Bit();
    usleep(1000);
    writeData(commandSerial);
    usleep(100000);
//    for(int i = 0; i < 9; ++i)
//    {
//        usleep(2000000);
//        writeData(commandSerial);
//    }
}

double settings::average(vector<double> const &v)
{
    vector<double>::size_type taille = v.size();
    double sum = 0;
    for(vector<double>::const_iterator it = v.begin(); it != v.end(); ++it)
        sum += *it;
    return sum/taille;
}
QString settings::calculateCalibrationValues(bool val)
{
    QString result = "";
    if(val)
    {
        if(C01.size())
        {
            vector<double> num1;
            for(int i = 1 ; i < C01.size(); ++i)
            {
                vector<int> nos;
                parseStringtoNumbers(C01[i], nos, 1);
                num1.push_back(static_cast<double>(nos[0]));
            }
            Ring_true[0] = average(num1);
        }
        if(C02.size())
        {
            vector<double> num1;
            for(int i = 1 ; i < C02.size(); ++i)
            {
                vector<int> nos;
                parseStringtoNumbers(C02[i], nos, 1);
                num1.push_back(static_cast<double>(nos[0]));
            }
            Ring_true[1] = average(num1);
        }
        if(C03.size())
        {
            vector<double> num1;
            for(int i = 1; i < C03.size(); ++i)
            {
                vector<int> nos;
                parseStringtoNumbers(C03[i], nos, 1);
                num1.push_back(static_cast<double>(nos[0]));
            }
            Ring_true[2] = average(num1);
        }
        if(C04.size())
        {
            vector<double> num1;
            for(int i = 1 ; i < C04.size(); ++i)
            {
                vector<int> nos;
                parseStringtoNumbers(C04[i], nos, 1);
                num1.push_back(static_cast<double>(nos[0]));
            }
            Ring_true[3] = average(num1);
        }
        if(C05.size())
        {
            vector<double> num1;
            for(int i = 1 ; i < C05.size(); ++i)
            {
                vector<int> nos;
                parseStringtoNumbers(C05[i], nos, 1);
                num1.push_back(static_cast<double>(nos[0]));
            }
            Ring_true[4] = average(num1);
        }
        if(C06.size())
        {
            vector<double> num1;
            for(int i = 1 ; i < C06.size(); ++i)
            {
                vector<int> nos;
                parseStringtoNumbers(C06[i], nos, 1);
                num1.push_back(static_cast<double>(nos[0]));
            }
            Ring_true[5] = average(num1);
        }
        if(C07.size())
        {
            vector<double> num1;
            for(int i = 1 ; i < C07.size(); ++i)
            {
                vector<int> nos;
                parseStringtoNumbers(C07[i], nos, 1);
                num1.push_back(static_cast<double>(nos[0]));
            }
            Ring_true[6] = average(num1);
        }
        if(C08.size())
        {
            vector<double> num1;
            for(int i = 1 ; i < C08.size(); ++i)
            {
                vector<int> nos;
                parseStringtoNumbers(C08[i], nos, 1);
                num1.push_back(static_cast<double>(nos[0]));
            }
            Ring_true[7] = average(num1);
        }
        if(C09.size())
        {
            vector<double> num1;
            for(int i = 1 ; i < C09.size(); ++i)
            {
                vector<int> nos;
                parseStringtoNumbers(C09[i], nos, 1);
                num1.push_back(static_cast<double>(nos[0]));
            }
            Ring_true[8] = average(num1);
        }
        if(C10.size())
        {
            vector<double> num1;
            for(int i = 1 ; i < C10.size(); ++i)
            {
                vector<int> nos;
                parseStringtoNumbers(C10[i], nos, 1);
                num1.push_back(static_cast<double>(nos[0]));
            }
            Ring_true[9] = average(num1);
        }
        if(C11.size())
        {
            vector<double> num1;
            for(int i = 1 ; i < C11.size(); ++i)
            {
                vector<int> nos;
                parseStringtoNumbers(C11[i], nos, 1);
                num1.push_back(static_cast<double>(nos[0]));
            }
            Ring_true[10] = average(num1);
        }
        if(C12.size())
        {
            vector<double> num1;
            for(int i = 1 ; i < C12.size(); ++i)
            {
                vector<int> nos;
                parseStringtoNumbers(C12[i], nos, 1);
                num1.push_back(static_cast<double>(nos[0]));
            }
            Ring_true[11] = average(num1);
        }

        // print the answer and form the result
        for (int i = 0; i < Ring_true.size(); ++i)
        {
            qDebug() << "With Ring " << i+1 <<   " Value : " << Ring_true[i];
            result += QString::number(Ring_true[i]) + ":";
        }

        result.remove(result.size()-1, 1);
        result += "\n";
        qDebug() << "Calibrated values host (Ring true) " << result << endl;

    }
    else
    {
        if(CNO.size())
        {
            vector<double> num1;
            vector<double> num2;
            vector<double> num3;
            vector<double> num4;
            vector<double> num5;
            vector<double> num6;
            vector<double> num7;
            vector<double> num8;
            vector<double> num9;
            vector<double> num10;
            vector<double> num11;
            vector<double> num12;
            for(int i = 3 ; i < CNO.size(); ++i)
            {
                vector<int> nos;
                parseStringtoNumbers(CNO[i], nos, 12);
                num1.push_back(static_cast<double>(nos[0]));
                num2.push_back(static_cast<double>(nos[1]));
                num3.push_back(static_cast<double>(nos[2]));
                num4.push_back(static_cast<double>(nos[3]));
                num5.push_back(static_cast<double>(nos[4]));
                num6.push_back(static_cast<double>(nos[5]));
                num7.push_back(static_cast<double>(nos[6]));
                num8.push_back(static_cast<double>(nos[7]));
                num9.push_back(static_cast<double>(nos[8]));
                num10.push_back(static_cast<double>(nos[9]));
                num11.push_back(static_cast<double>(nos[10]));
                num12.push_back(static_cast<double>(nos[11]));
            }
            Ring_false[0] = average(num1);
            Ring_false[1] = average(num2);
            Ring_false[2] = average(num3);
            Ring_false[3] = average(num4);
            Ring_false[4] = average(num5);
            Ring_false[5] = average(num6);
            Ring_false[6] = average(num7);
            Ring_false[7] = average(num8);
            Ring_false[8] = average(num9);
            Ring_false[9] = average(num10);
            Ring_false[10] = average(num11);
            Ring_false[11] = average(num12);
        }
        for (int i = 0; i < Ring_false.size(); ++i)
        {
            qDebug() << "Without Ring " << i+1 <<   " Value : " << Ring_false[i];
            result += QString::number(Ring_false[i]) + ":";
        }
        result.remove(result.size()-1, 1);
        result += "\n";
        qDebug() << "Calibrated values host (Ring false)" << result << endl;
    }
    return result;
}

void settings::on_btnCalib_clicked()
{
    if(ui->btnCalib->text() == "Start Calibration")
    {
        // start the calibration process
        ui->btnCalib->setText("Remove all the rings and click");
        usleep(100);
        ui->buttonBox->setEnabled(false);
        updateSettings();
        ui->parametersBox->setEnabled(false);
        ui->serialPortBox->setEnabled(false);
        openSerialPort();

        //reset first
        QString s = "z\n";
        QByteArray commandSerial = s.toLocal8Bit();
        usleep(1000000);
        writeData(commandSerial);
        s = "d\n";
        commandSerial = s.toLocal8Bit();
        usleep(1000000);
        writeData(commandSerial);
        usleep(1000000);
    }
    else if(ui->btnCalib->text() == "Remove all the rings and click")
    {
        // read the data without the rings
        calibCounter = 0;
        QString s = "e\n";
        sendSerialCommand(s);
    }
    else if(ui->btnCalib->text() == "Place Ring at position 1 and click")
    {
        calibCounter = 1;
        QString s = "f\n";
        sendSerialCommand(s);
    }
    else if(ui->btnCalib->text() == "Place Ring at position 2 and click")
    {
        calibCounter = 2;
        QString s = "g\n";
        sendSerialCommand(s);
    }
    else if(ui->btnCalib->text() == "Place Ring at position 3 and click")
    {
        calibCounter = 3;
        QString s = "h\n";
        sendSerialCommand(s);

    }
    else if(ui->btnCalib->text() == "Place Ring at position 4 and click")
    {
        calibCounter = 4;
        QString s = "i\n";
        sendSerialCommand(s);

    }
    else if(ui->btnCalib->text() == "Place Ring at position 5 and click")
    {
        calibCounter = 5;
        QString s = "j\n";
        sendSerialCommand(s);

    }
    else if(ui->btnCalib->text() == "Place Ring at position 6 and click")
    {
        calibCounter = 6;
        QString s = "k\n";
        sendSerialCommand(s);

    }
    else if(ui->btnCalib->text() == "Place Ring at position 7 and click")
    {
        calibCounter = 7;
        QString s = "l\n";
        sendSerialCommand(s);

    }
    else if(ui->btnCalib->text() == "Place Ring at position 8 and click")
    {
        calibCounter = 8;
        QString s = "m\n";
        sendSerialCommand(s);

    }
    else if(ui->btnCalib->text() == "Place Ring at position 9 and click")
    {
        calibCounter = 9;
        QString s = "n\n";
        sendSerialCommand(s);

    }
    else if(ui->btnCalib->text() == "Place Ring at position 10 and click")
    {
        calibCounter = 10;
        QString s = "o\n";
        sendSerialCommand(s);

    }
    else if(ui->btnCalib->text() == "Place Ring at position 11 and click")
    {
        calibCounter = 11;
        QString s = "p\n";
        sendSerialCommand(s);

    }
    else if(ui->btnCalib->text() == "Place Ring at position 12 and click")
    {
        calibCounter = 12;
        QString s = "q\n";
        sendSerialCommand(s);

    }
    else if(ui->btnCalib->text() == "Click to process calibration Data")
    {
        calibCounter = 13;
        ui->buttonBox->setEnabled(false);
        QString s = "r\n";
        QByteArray commandSerial = s.toLocal8Bit();
        usleep(1000000);
        writeData(commandSerial);
        usleep(3000000);
        //writeData(commandSerial);
        //usleep(1000000);
        //usleep(1000);
        //writeData(commandSerial);

        // process the data and send the result
        QString result = calculateCalibrationValues(true);
        //result.truncate(23);
        //result += "\n";
        commandSerial = result.toLocal8Bit();
        //qDebug() << "Command Serial Host " << commandSerial << endl;
        //usleep(300000);
        writeData(commandSerial);
        usleep(3000000);


        //result = calculateCalibrationValues(false);
        //result.truncate(23);
        //result += "\n";
        //commandSerial = result.toLocal8Bit();
        //qDebug() << "Command Serial Host " << commandSerial << endl;
        //usleep(1000000);
        //writeData(commandSerial);
        //usleep(100000);

    }
    else if( ui->btnCalib->text() == "Send the calibration data")
    {
        calibCounter = -1;
        QString s = "t\n";
        QByteArray commandSerial = s.toLocal8Bit();
        usleep(1000000);
        writeData(commandSerial);
        usleep(2000000);
        //writeData(commandSerial);
        //usleep(1000000);
        //usleep(1000);
        //writeData(commandSerial);

        // process the data and send the result
        QString result = calculateCalibrationValues(false);
        //result.truncate(23);
        //result += "\n";
        commandSerial = result.toLocal8Bit();
        //qDebug() << "Command Serial Host " << commandSerial << endl;
        //usleep(300000);
        writeData(commandSerial);
        usleep(1000000);


        //result = calculateCalibrationValues(false);
        //result.truncate(23);
        //result += "\n";
        //commandSerial = result.toLocal8Bit();
        //qDebug() << "Command Serial Host " << commandSerial << endl;
        //usleep(1000000);
        //writeData(commandSerial);
        //usleep(100000);




        ui->buttonBox->setEnabled(true);
        //closeSerialPort();
        ui->btnCalib->setText("Start Calibration");
        ui->parametersBox->setEnabled(true);
        ui->serialPortBox->setEnabled(true);
    }
}

void settings::setDB(const QSqlDatabase &endoDB)
{
    this->endoDB = endoDB;
}

void settings::openSerialPort()
{
    serial->setPortName(serial_settings.name);
    serial->setBaudRate(serial_settings.baudRate);
    serial->setDataBits(serial_settings.dataBits);
    serial->setParity(serial_settings.parity);
    serial->setStopBits(serial_settings.stopBits);
    serial->setFlowControl(serial_settings.flowControl);
    if (!serial->open(QIODevice::ReadWrite))
    {
       QMessageBox::critical(this, tr("Error"), serial->errorString());
    }
}
void settings::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
}
void settings::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}


void settings::on_btnAddtoDatabase_clicked()
{
    QString name = ui->txtName->text();
    QString title    = ui->cmbSalutation->currentText();
    QString details = ui->textDetails->toPlainText();
    QString email = ui->txtEmail->text();
    QString exp = ui->cmbExperience->currentText();
    if(title == "Other")
    {
        title = "";
    }
    if(name == "" || details == "" || email == "")
    {
        QMessageBox::critical(this, tr("Error"), "Please provide the Name, email and contact details");
        return;
    }
    endoDB.open();
    if(!endoDB.isOpen())
    {
        if(!endoDB.open())
        {
            QMessageBox::critical(this, tr("Error"), "Database Error !!!");
            return;
        }
    }
    QSqlQuery query;
    query.prepare( "SELECT * FROM nameID WHERE EmailID = ?" );
    query.bindValue( 0, email );
    resultQry = query.exec();
    if(resultQry && query.next())
    {
        QMessageBox::critical(this, tr("Error"), "Given EmailID already exist in the system. Please provide different EmailID");
        return;
    }
    else
    {
        query.prepare("INSERT INTO nameID (EmailID, Name, Experience, ContactDetails)"
                      "VALUES (:EmailID, :Name, :Experience, :ContactDetails)");
        query.bindValue(":EmailID", email);
        query.bindValue(":Name", title+ " "+name);
        query.bindValue(":Experience", exp);
        query.bindValue(":ContactDetails", details);
        resultQry = query.exec();
        if(!resultQry)
        {
            QMessageBox::critical(this, tr("Error"), "DB Error - see the log");
            qDebug() << "DB error:  " << query.lastError();
        }
        else
        {
            QMessageBox b;
            b.setText(title+ " "+name + " with eamilid (" + email + ") successfully added to the database");
            b.exec();
        }
    }
}


void settings::on_pushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    ui->cap_path->setText(dir);
}
