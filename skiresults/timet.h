#ifndef TIMET_H
#define TIMET_H
#include <string>
#include <memory>

class TimeT
{
public:

    /// Default constructor
    TimeT();
    ///
    /// \brief TimeT presents the times of skiers in competitions
    /// \param time: time as string in form h:mm:ss.ss
    ///
    TimeT(std::string& hrs, std::string& mins, std::string& secs);

    ///
    /// \brief TimeT presents the times of skiers in competitions.
    ///        This constructor for parameters as separated numbers
    /// \param hour given: h
    /// \param minute given: mm
    /// \param second given: ss:ss
    ///
    TimeT(const int& hour, const int& minute, const float& second);

    constexpr bool operator <(const TimeT& other) // operator <
    {
        if(hour_ != other.hour_)
        {
            return hour_ < other.hour_;
        }
        else // same hour
        {
            if(min_ != other.min_)
            {
                return min_ < other.min_;
            }
            else // same min
            {
                return sec_ < other.sec_;
            }
        }
    }

    constexpr bool operator>(const TimeT& other) // operator >
    {
        if(hour_ != other.hour_)
        {
            return hour_ > other.hour_;
        }
        else // same hour
        {
            if(min_ != other.min_)
            {
                return min_ > other.min_;
            }
            else // same min
            {
                return sec_ > other.sec_;
            }
        }
    }

    constexpr bool operator==(const TimeT other) // operator ==
    {
        return hour_ == other.hour_ &&
               sec_ == other.sec_ &&
               min_ == other.min_;
    }

    constexpr TimeT operator+(const TimeT& other) // operator +
    {    
        float sec = sec_ + other.sec_;
        int min = min_ + other.min_;
        if(sec >= 60)
        {
            sec -= 60;
            min += 1;
        }
        int hour = hour_ + other.hour_;
        if(min >= 60)
        {
            min -= 60;
            hour += 1;
        }
        TimeT sum(hour,min,sec);
        return sum;
    }


    ///
    /// \brief getAverageTime calculates average time of certain race
    /// \param competitorAmount, used as divisor
    /// \return poiter to timeT that is average time
    ///
    std::shared_ptr<TimeT> getAverageTime(const int& competitorAmount);

    ///
    /// \brief toString, converts timeT to string
    /// \return time as string
    ///
    std::string toString() const;

    ///
    /// \brief isZero
    /// \return return true if hour, min and sec are zeroes
    ///
    bool isZero() const;

    int getHour();
    int getMin();
    float getSec();

    void setHour(int h);
    void setMin(int m);
    void setSec(float s);

private:
    int hour_;
    int min_;
    float sec_;
    bool isNumber(const std::string &s);
};

const TimeT NO_TIME(-1,-1,-1);

#endif // TIMET_H
