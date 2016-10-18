#ifndef BUF_ENDO_H
#define BUF_ENDO_H
/*
 * Circular buffer for Endoscopy Camera -> Singleton class
 *
*/

#include <iostream>
#include <QtCore>
#include <QThread>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "params.h"
//12-12-12
using namespace std;
using namespace cv;

class buf_endo
{
public:
    // Threading Variables
    QWaitCondition notFull;
    QWaitCondition notEmpty;
    QMutex mutex;

    // Setters
    // Set the Head index of buffer
    inline void setHead(int h){this->head = h;}

    // Set the Tail index of buffer
    inline void setTail(int t){this->tail = t;}

    // Set the empty condition for buffer
    inline void setEmpty(bool e){ this->empty = e;}

    // Set the full condition for buffer
    inline void setFull(bool f){this->full = f;}

    // Set buffer input is cv::Mat captured from Endoscopic camera
    inline void setBuffer(const vector<cv::Mat> &vec)
    {
        buf[tail] = vec;
        tail++;
        if(tail == bufSize)
            tail = 0;
        if(tail == head)
            full = true;
        empty = false;
    }

    //getters
    // Get the Head index of buffer
    inline int getHead(){return (this->head);}

    // Get the tail index of buffer
    inline int getTail(){return (this->tail);}

    // Get the empty condition for the buffer
    inline bool getEmpty(){return (this->empty);}

    // Get the full condition for the buffer
    inline bool getFull(){return (this->full);}

    // Get the buffer size
    inline int getBufSize(){return (this->bufSize);}


    // Get the cv::Mat from the buffer to write on the videowriter
    inline void getBuffer(vector<cv::Mat> &v)
    {
        v = buf[head];
        head++;

        if(head == bufSize)
            head = 0;

        if(head == tail)
            empty = true;

        full = false;
    }
    // Get the global instance
    static buf_endo *instance(const params &param)
    {
        if(!s_instance)
            s_instance = new buf_endo(param);
        return s_instance;
    }

private:
    //std::vector<vector<uchar> > buf;
    vector<vector<Mat> > buf;

    uint head, tail, bufSize, binSize;
    bool full, empty;
    static buf_endo *s_instance;
    buf_endo(const params &param)
    {
        binSize = param.cap_binSize;
        bufSize = param.cap_queueSize;
        buf.resize(bufSize);
        for(uint i = 0; i < bufSize; ++i)
        {
            buf[i].resize(binSize);
        }
        empty = true;
        full = false;
        head = 0;
        tail = 0;
    }
};
#endif // BUF_ENDO_H
