#include "timeClass.h"
//12-12-12
/*
 * Assuming string time is in the following format
 * Hour:Minute:Second:MilliSecond
 */
timeClass::timeClass(const string &t)
{
    std::string::size_type index1 = t.find(':', 0);
    std::string::size_type index2 = t.find(':', index1+1);
    std::string::size_type index3 = t.find(':', index2+1);


    int Hour = std::atoi(t.substr(0, index1).c_str());
    int Minute = std::atoi(t.substr(index1+1, index2-index1-1).c_str());
    int Second = std::atoi(t.substr(index2+1, index3-index2-1).c_str());
    int Milli = std::atoi(t.substr(index3+1).c_str());

    this->H = Hour;
    this->M = Minute;
    this->S = Second;
    this->ms = Milli;
}

void timeClass::setTime(int H, int M, int S, int ms)
{
    this->H = H;
    this->M = M;
    this->S = S;
    this->ms = ms;
}

void timeClass::setTime(const string &t)
{
    std::string::size_type index1 = t.find(':', 0);
    std::string::size_type index2 = t.find(':', index1+1);
    std::string::size_type index3 = t.find(':', index2+1);

    int Hour = std::atoi(t.substr(0, index1).c_str());
    int Minute = std::atoi(t.substr(index1+1, index2-index1-1).c_str());
    int Second = std::atoi(t.substr(index2+1, index3-index2-1).c_str());
    int Milli = std::atoi(t.substr(index3+1).c_str());
    setTime(Hour, Minute, Second, Milli);
}

int timeClass::Hours() const
{
    return H;
}
int timeClass::Minutes() const
{
    return M;
}
int timeClass::Seconds() const
{
    return S;
}
int timeClass::Millis() const
{
    return ms;
}

/*
 * t1>t2 gives true else false
 *
 */
bool timeClass::greaterThan(const string &t1, const string &t2)
{
    timeClass c1(t1);
    timeClass c2(t2);
    return greaterThan(c1, c2);
}
bool timeClass::greaterThan(const timeClass &t1, const timeClass &t2)
{
    bool result;
    int H1 = t1.Hours();
    int M1 = t1.Minutes();
    int S1 = t1.Seconds();
    int ms1 = t1.Millis();

    int H2 = t2.Hours();
    int M2 = t2.Minutes();
    int S2 = t2.Seconds();
    int ms2 = t2.Millis();

    if(H1 > H2)
    {
        result = true;
    }
    else if(H1 == H2) // compare M1 and M2
    {
        if(M1 > M2)
        {
            result = true;
        }
        else if(M1 == M2) // compare S1 and S2
        {
            if(S1 > S2)
            {
                result = true;
            }
            else if(S1 == S2) // compare ms1 and ms2
            {
                if(ms1 > ms2)
                {
                    result = true;
                }
                else
                {
                    result = false;
                }
            }
            else
            {
                result = false;
            }
        }
        else
        {
            result = false;
        }
    }
    else
    {
        result = false;
    }
    return result;
}

bool timeClass::greaterThan(const string &t1)
{
    timeClass c1(t1);
    return greaterThan(c1);
}

/*
 * Gives whether current time is greater than the given time
 */

bool timeClass::greaterThan(const timeClass &t1)
{
    bool result;
    int H1 = Hours();
    int M1 = Minutes();
    int S1 = Seconds();
    int ms1 = Millis();

    int H2 = t1.Hours();
    int M2 = t1.Minutes();
    int S2 = t1.Seconds();
    int ms2 = t1.Millis();

    if(H1 > H2)
    {
        result = true;
    }
    else if(H1 == H2) // compare M1 and M2
    {
        if(M1 > M2)
        {
            result = true;
        }
        else if(M1 == M2) // compare S1 and S2
        {
            if(S1 > S2)
            {
                result = true;
            }
            else if(S1 == S2) // compare ms1 and ms2
            {
                if(ms1 > ms2)
                {
                    result = true;
                }
                else
                {
                    result = false;
                }
            }
            else
            {
                result = false;
            }
        }
        else
        {
            result = false;
        }
    }
    else
    {
        result = false;
    }
    return result;
}

int timeClass::timeSpentinMillis(const string &startTime, const string &endTime)
{
    timeClass start(startTime);
    timeClass end(endTime);

    int hrs = (end.Hours() - start.Hours())     * 60*60*1000;
    int min = (end.Minutes() - start.Minutes()) * 60*1000;
    int sec = (end.Seconds() - start.Seconds()) * 1000;
    int ms = (end.Millis() - start.Millis());

    int total = hrs+min+sec+ms;
    return total;
}

int timeClass::timeSpentinMillis(const timeClass &start, const timeClass &end)
{
    int hrs = (end.Hours() - start.Hours())     * 60*60*1000;
    int min = (end.Minutes() - start.Minutes()) * 60*1000;
    int sec = (end.Seconds() - start.Seconds()) * 1000;
    int ms = (end.Millis() - start.Millis());

    int total = hrs+min+sec+ms;
    return total;
}


bool timeClass::lessThan(const string &t1, const string &t2)
{
    timeClass c1(t1);
    timeClass c2(t2);
    return lessThan(c1, c2);
}

bool timeClass::lessThan(const timeClass &t1, const timeClass &t2)
{
    bool result;
    int H1 = t1.Hours();
    int M1 = t1.Minutes();
    int S1 = t1.Seconds();
    int ms1 = t1.Millis();

    int H2 = t2.Hours();
    int M2 = t2.Minutes();
    int S2 = t2.Seconds();
    int ms2 = t2.Millis();

    if(H1 > H2)
    {
        result = false;
    }
    else if(H1 == H2) // compare M1 and M2
    {
        if(M1 > M2)
        {
            result = false;
        }
        else if(M1 == M2) // compare S1 and S2
        {
            if(S1 > S2)
            {
                result = false;
            }
            else if(S1 == S2) // compare ms1 and ms2
            {
                if(ms1 > ms2)
                {
                    result = false;
                }
                else
                {
                    result = true;
                }
            }
            else
            {
                result = true;
            }
        }
        else
        {
            result = true;
        }
    }
    else
    {
        result = true;
    }
    return result;
}

bool timeClass::lessThan(const string &t)
{
    timeClass c(t);
    return lessThan(c);
}

bool timeClass::lessThan(const timeClass &t)
{
    bool result;
    int H1 = Hours();
    int M1 = Minutes();
    int S1 = Seconds();
    int ms1 = Millis();

    int H2 = t.Hours();
    int M2 = t.Minutes();
    int S2 = t.Seconds();
    int ms2 = t.Millis();
    if(H1 > H2)
    {
        result = false;
    }
    else if(H1 == H2) // compare M1 and M2
    {
        if(M1 > M2)
        {
            result = false;
        }
        else if(M1 == M2) // compare S1 and S2
        {
            if(S1 > S2)
            {
                result = false;
            }
            else if(S1 == S2) // compare ms1 and ms2
            {
                if(ms1 > ms2)
                {
                    result = false;
                }
                else
                {
                    result = true;
                }
            }
            else
            {
                result = true;
            }
        }
        else
        {
            result = true;
        }
    }
    else
    {
        result = true;
    }
    return result;
}


bool timeClass::equalTo(const string &t1, const string &t2)
{
    timeClass c1(t1);
    timeClass c2(t2);
    return equalTo(c1, c2);
}

bool timeClass::equalTo(const timeClass &t1, const timeClass &t2)
{
    int H1 = t1.Hours();
    int M1 = t1.Minutes();
    int S1 = t1.Seconds();
    int ms1 = t1.Millis();

    int H2 = t2.Hours();
    int M2 = t2.Minutes();
    int S2 = t2.Seconds();
    int ms2 = t2.Millis();
    if(H1 == H2 && M1 == M2 && S1 == S2 && ms1 == ms2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool timeClass::equalTo(const string &t)
{
    timeClass c(t);
    return equalTo(c);
}

bool timeClass::equalTo(const timeClass &t)
{
    int H1 = Hours();
    int M1 = Minutes();
    int S1 = Seconds();
    int ms1 = Millis();

    int H2 = t.Hours();
    int M2 = t.Minutes();
    int S2 = t.Seconds();
    int ms2 = t.Millis();
    if(H1 == H2 && M1 == M2 && S1 == S2 && ms1 == ms2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool timeClass::getRange(const vector<pair<string, string> > &Hitting,
              const string &t1,
              const string &t2,
              pair<int, int > &indices)
{
    indices.first = -1;
    indices.second = -1;
    if(equalTo(t1, t2))
        return false;
    else if(greaterThan(t1, t2))
        return false;

    bool lowerBound = false;
    bool upperBound = false;
    for(uint i = 0; i < Hitting.size(); ++i)
    {
        string time =  Hitting[i].first;
        if((greaterThan(time, t1) || equalTo(time, t1)) && !lowerBound)
        {
            lowerBound = true;
            indices.first = i;
        }
        if((greaterThan(time, t2) || equalTo(time, t2)) && !upperBound)
        {
            upperBound = true;
            indices.second = i-1;
        }
    }
    if(!lowerBound)
    {
        return false;
    }
    if(!upperBound)
    {
        indices.second = Hitting.size()-1;
    }
    return true;
}


bool timeClass::getRange(const vector<pair<string, string> > &Hitting,
              const timeClass &t1,
              const timeClass &t2,
              pair<int, int > &indices)
{
    indices.first = -1;
    indices.second = -1;
    if(equalTo(t1, t2))
        return false;
    else if(greaterThan(t1, t2))
        return false;

    bool lowerBound = false;
    bool upperBound = false;
    for(uint i = 0; i < Hitting.size(); ++i)
    {
        timeClass time(Hitting[i].first);
        if((greaterThan(time, t1) || equalTo(time, t1)) && !lowerBound)
        {
            lowerBound = true;
            indices.first = i;
        }
        if((greaterThan(time, t2) || equalTo(time, t2)) && !upperBound)
        {
            upperBound = true;
            indices.second = i-1;
        }
    }
    if(!lowerBound)
    {
        return false;
    }
    if(!upperBound)
    {
        indices.second = Hitting.size()-1;
    }
    return true;
}


bool timeClass::getRange(const vector<string> &timeData,
              const timeClass &t1,
              const timeClass &t2,
              pair<int, int > &indices)
{
    indices.first = -1;
    indices.second = -1;

    if(equalTo(t1, t2))
        return false;
    else if(greaterThan(t1, t2))
        return false;

    bool lowerBound = false;
    bool upperBound = false;
    for(uint i = 0; i < timeData.size(); ++i)
    {
        timeClass time(timeData[i]);
        if((greaterThan(time, t1) || equalTo(time, t1)) && !lowerBound)
        {
            lowerBound = true;
            indices.first = i;
        }
        if((greaterThan(time, t2) || equalTo(time, t2)) && !upperBound)
        {
            upperBound = true;
            indices.second = i-1;
        }
    }
    if(!lowerBound)
    {
        return false;
    }
    if(!upperBound)
    {
        indices.second = timeData.size()-1;
    }
    return true;

}

bool timeClass::getRange(const vector<string > &timeData,
              const string &t1,
              const string &t2,
              pair<int, int > &indices)
{
    indices.first = -1;
    indices.second = -1;
    if(equalTo(t1, t2))
        return false;
    else if(greaterThan(t1, t2))
        return false;

    bool lowerBound = false;
    bool upperBound = false;
    for(uint i = 0; i < timeData.size(); ++i)
    {
        string time =  timeData[i];
        if((greaterThan(time, t1) || equalTo(time, t1)) && !lowerBound)
        {
            lowerBound = true;
            indices.first = i;
        }
        if((greaterThan(time, t2) || equalTo(time, t2)) && !upperBound)
        {
            upperBound = true;
            indices.second = i-1;
        }
    }
    if(!lowerBound)
    {
        return false;
    }
    if(!upperBound)
    {
        indices.second = timeData.size()-1;
    }
    return true;

}

bool timeClass::getRange(const vector<pair<string, pair<double, double> > > &timeData,
              const timeClass &t1,
              const timeClass &t2,
              pair<int, int > &indices)
{

    indices.first = -1;
    indices.second = -1;

    if(equalTo(t1, t2))
        return false;
    else if(greaterThan(t1, t2))
        return false;

    bool lowerBound = false;
    bool upperBound = false;
    for(uint i = 0; i < timeData.size(); ++i)
    {
        timeClass time(timeData[i].first);
        if((greaterThan(time, t1) || equalTo(time, t1)) && !lowerBound)
        {
            lowerBound = true;
            indices.first = i;
        }
        if((greaterThan(time, t2) || equalTo(time, t2)) && !upperBound)
        {
            upperBound = true;
            indices.second = i-1;
        }
    }
    if(!lowerBound)
    {
        return false;
    }
    if(!upperBound)
    {
        indices.second = timeData.size()-1;
    }
    return true;
}

bool timeClass::getRange(const vector<pair<string, pair<double, double> > > &timeData,
              const string &t1,
              const string &t2,
              pair<int, int > &indices)
{
    indices.first = -1;
    indices.second = -1;
    if(equalTo(t1, t2))
        return false;
    else if(greaterThan(t1, t2))
        return false;

    bool lowerBound = false;
    bool upperBound = false;
    for(uint i = 0; i < timeData.size(); ++i)
    {
        string time =  timeData[i].first;
        if((greaterThan(time, t1) || equalTo(time, t1)) && !lowerBound)
        {
            lowerBound = true;
            indices.first = i;
        }
        if((greaterThan(time, t2) || equalTo(time, t2)) && !upperBound)
        {
            upperBound = true;
            indices.second = i-1;
        }
    }
    if(!lowerBound)
    {
        return false;
    }
    if(!upperBound)
    {
        indices.second = timeData.size()-1;
    }
    return true;
}

