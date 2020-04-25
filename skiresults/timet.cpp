#include "timet.h"
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <QDebug>

TimeT::TimeT()
{
    hour_ = 0;
    min_ = 0;
    sec_ = 0;
}

TimeT::TimeT(std::string& hrs, std::string& mins, std::string& secs)
{
    std::string delim = ":";
    std::vector<std::string> splittedTime;
    if(isNumber(hrs) && isNumber(mins)){
        hour_ = std::stoi(hrs);
        min_ = std::stoi(mins);
        sec_ = std::stof(secs);
    }
}

TimeT::TimeT(const int& hour, const int& minute, const float& second)
{
    hour_ = hour;
    min_ = minute;
    sec_ = second;
}

std::shared_ptr<TimeT> TimeT::getAverageTime(const int &competitorAmount)
{
    // 'this' contains summarized time of race
    std::shared_ptr<TimeT> averageTime = std::make_shared<TimeT>(0,0,0);
    double sec = (hour_*60*60 + min_*60 + sec_) / competitorAmount;
    int hour = sec / 3600;
    if(hour > 0)
    {
        averageTime->setHour(hour);
        sec -= hour * 3600;
    }
    int min = sec / 60;
    if(min > 0)
    {
        averageTime->setMin(min);
        sec -= min * 60;
    }
    averageTime->setSec(sec);
    return averageTime;
}

std::string TimeT::toString() const
{
    std::string sec = std::to_string(sec_);
    std::string secRounded = sec.substr(0,sec.find(".")+2); // one decimal
    if(secRounded.length() < 4)
    {
        secRounded = "0" + secRounded;
    }
    std::string min = std::to_string(min_);
    if(min.length() < 2)
    {
        min = "0" + min;
    }
    return std::to_string(hour_) +":"+ min +":"+ secRounded;
}

bool TimeT::isZero() const
{
    return hour_ == 0 && min_ == 0 && sec_ == 0;
}


int TimeT::getHour()
{
    return hour_;
}

int TimeT::getMin()
{
    return min_;
}

float TimeT::getSec()
{
    return sec_;
}

void TimeT::setHour(int h)
{
    hour_ = h;
}

void TimeT::setMin(int m)
{
    min_ = m;
}

void TimeT::setSec(float s)
{
    sec_ = s;
}

bool TimeT::isNumber(const std::string &s)
{
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}
