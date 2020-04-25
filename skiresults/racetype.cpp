#include "racetype.h"
#include <algorithm>

raceType::raceType(int year, std::string racetag)
{
    _year = year;
    _raceTag = racetag;
}

std::map<TimeT, std::shared_ptr<Athlete> > raceType::getCompetitors()
{
    return _competitors;
}

std::map<TimeT, std::shared_ptr<Athlete> > *raceType::getCompetitorsPtr()
{
    std::map<TimeT, std::shared_ptr<Athlete> > * ptr = &_competitors;
    return ptr;

}

std::string raceType::getRaceTag()
{
    return _raceTag;
}

void raceType::addCompetitors(const TimeT &time, std::shared_ptr<Athlete> &athlete)
{
    _competitors.insert({time, athlete});
}

const TimeT raceType::getCompetitorTime(Athlete& athlete)
{
    std::string id = athlete.getID();
    for(auto competitor : _competitors)
    {
        if(competitor.second->getID() == id)
        {
            return competitor.first;
        }
    }
    return NO_TIME;
}

TimeT raceType::getSumOf(int &topCompetitors)
{
    TimeT sum(0,0,0);
    int counter = 1;
    for(auto& competitor : _competitors)
    {
        if(counter <= topCompetitors)
        {
            sum = sum + competitor.first;
        }
        else
        {
            return sum;
        }
        ++counter;
    }
    return sum;
}
