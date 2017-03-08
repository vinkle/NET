#ifndef TIME_H
#define TIME_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
//12-12-12
using namespace std;
using namespace cv;

class timeClass
{
public:
    timeClass(int H = 0, int M = 0, int S = 0, int ms = 0):H(H), M(M), S(S), ms(ms)
    {}
    timeClass(const string &t);

    void setTime(int H = 0, int M = 0, int S = 0, int ms = 0);
    void setTime(const string &t);
    bool getRange(const vector<pair<string, string> > &Hitting,
                  const timeClass &t1,
                  const timeClass &t2,
                  pair<int, int > &indices);
    bool getRange(const vector<pair<string, string> > &Hitting,
                  const string &time1,
                  const string &time2,
                  pair<int, int > &indices);

    bool getRange(const vector<pair<string, int> > &Hitting,
                  const timeClass &t1,
                  const timeClass &t2,
                  pair<int, int > &indices);

    bool getRange(const vector<pair<string, int> > &Hitting,
                  const string &time1,
                  const string &time2,
                  pair<int, int > &indices);

    bool getRange(vector< pair<string, vector<vector<Point> > > > &tugging,
                  const timeClass &t1,
                  const timeClass &t2,
                  pair<int, int > &indices);
    bool getRange(vector< pair<string, vector<vector<Point> > > > &tugging,
                  const string &time1,
                  const string &time2,
                  pair<int, int > &indices);


    bool getRange(const vector<string> &timeData,
                  const timeClass &t1,
                  const timeClass &t2,
                  pair<int, int > &indices);
    bool getRange(const vector<string > &timeData,
                  const string &time1,
                  const string &time2,
                  pair<int, int > &indices);

    bool getRange(const vector<pair<string, pair<double, double> > > &timeData,
                  const timeClass &t1,
                  const timeClass &t2,
                  pair<int, int > &indices);
    bool getRange(const vector<pair<string, pair<double, double> > > &timeData,
                  const string &time1,
                  const string &time2,
                  pair<int, int > &indices);

    static int timeSpentinMillis(const string &time1, const string &time2);
    static int timeSpentinMillis(const timeClass &start, const timeClass &end);

    bool greaterThan(const string &t1, const string &t2);
    bool greaterThan(const timeClass &t1, const timeClass &t2);
    bool greaterThan(const string &t1);
    bool greaterThan(const timeClass &t1);

    bool lessThan(const string &t1, const string &t2);
    bool lessThan(const timeClass &t1, const timeClass &t2);
    bool lessThan(const string &t1);
    bool lessThan(const timeClass &t1);


    bool equalTo(const string &t1, const string &t2);
    bool equalTo(const timeClass &t1, const timeClass &t2);
    bool equalTo(const string &t1);
    bool equalTo(const timeClass &t1);


    int Hours() const;
    int Minutes() const;
    int Seconds() const;
    int Millis() const;



private:
    int H;
    int M;
    int S;
    int ms;
};

#endif // TIME_H
