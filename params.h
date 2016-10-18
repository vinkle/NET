#ifndef PARAMS_H
#define PARAMS_H

#include <string>
#include <vector>
#include <QtSerialPort/QSerialPort>
using namespace std;
//12-12-12
class params
{
public:
    params(string cap_auxCam = "basler",
    unsigned int cap_queueSize = 10,
    unsigned int cap_binSize = 20,
    unsigned int cap_rowsAux = 1024,
    unsigned int cap_colsAux = 1280,
    unsigned int cap_fpsAux  = 25,
    unsigned int cap_camID_IDS = 2,
    unsigned int cap_colsEndo = 1280,
    unsigned int cap_rowsEndo = 720,
    unsigned int cap_fpsEndo = 25,
    std::string tr_name = "tld",
    int dev_plateAngle = 0
    ):cap_auxCam(cap_auxCam),
      cap_queueSize(cap_queueSize),
      cap_binSize(cap_binSize),
      cap_rowsAux(cap_rowsAux),
      cap_colsAux(cap_colsAux),
      cap_fpsAux(cap_fpsAux),
      cap_camID_IDS(cap_camID_IDS),
      cap_colsEndo(cap_colsEndo),
      cap_rowsEndo(cap_rowsEndo),
      cap_fpsEndo(cap_fpsEndo),
      tr_name(tr_name),
      dev_plateAngle(dev_plateAngle)
    {
        cap_paths.clear();
        cap_paths = "/home/terminalx/Desktop";
        // serial port settings
        serial_name =  "ttyUSB0";
        serial_baudRate =  static_cast<QSerialPort::BaudRate>(9600);
        serial_stringBaudRate = "115200";
        serial_dataBits = static_cast<QSerialPort::DataBits>(8);
        serial_stringDataBits = "8";
        serial_parity = static_cast<QSerialPort::Parity>(0);
        serial_stringParity = "None";
        serial_stopBits = static_cast<QSerialPort::StopBits>(1);
        serial_stringStopBits = "1";
        serial_flowControl = static_cast<QSerialPort::FlowControl>(0);
        serial_stringFlowControl = "None";
    }

// capture parameters
    string cap_paths;
    string cap_auxCam;
    unsigned int cap_queueSize;
    unsigned int cap_binSize;
    unsigned int cap_rowsAux;
    unsigned int cap_colsAux;
    unsigned int cap_fpsAux;
    unsigned int cap_camID_IDS;
    unsigned int cap_colsEndo;
    unsigned int cap_rowsEndo;
    unsigned int cap_fpsEndo;
// tracker paramters
    string tr_name;

// endo trainer device settings
    int dev_plateAngle;
// endo trainer serial port settings
    QString serial_name;

    qint32 serial_baudRate;
    QString serial_stringBaudRate;

    QSerialPort::DataBits serial_dataBits;
    QString serial_stringDataBits;

    QSerialPort::Parity serial_parity;
    QString serial_stringParity;

    QSerialPort::StopBits serial_stopBits;
    QString serial_stringStopBits;

    QSerialPort::FlowControl serial_flowControl;
    QString serial_stringFlowControl;

};

#endif // PARAMS_H
