#ifndef RACETYPE_H
#define RACETYPE_H

#include <iostream>
#include <vector>
#include <map>
#include <memory>

#include "athlete.h"
#include "timet.h"


class raceType
{
public:

    ///
    /// \brief Constructor
    /// \param year, the year when the race was held
    /// \param ravetag, the tag of the race
    ///
    raceType(int year, std::string racetag);

    ///
    /// \brief getCompetitors, gets all competetors from this race
    /// \return A map with Time-object as key and Athlete-object as value
    ///
    std::map<TimeT, std::shared_ptr<Athlete>> getCompetitors();

    ///
    /// \brief getCompetitorsPtr
    /// \return pointer to _competitors
    ///
    std::map<TimeT, std::shared_ptr<Athlete>>* getCompetitorsPtr();

    ///
    /// \brief getRaceTag, gets the tag of this race
    /// \return Race tag as a string
    ///
    std::string getRaceTag();

    ///
    /// \brief addCompetotors, adds competitors for this race
    /// \param time, the time the ahlete took to finish the race
    /// \param athlete, the competitor
    ///
    void addCompetitors(const TimeT & time, std::shared_ptr<Athlete>& athlete);

    ///
    /// \brief getCompetitorTime check if this race has certain competitor
    /// \param athlete reference to the athlete object
    /// \return time if found
    ///         NO_TIME if not found
    ///
    const TimeT getCompetitorTime(Athlete& athlete);

    ///
    /// \brief getSumOf
    /// \param topCompetitors number of competitors from front(best athlete)
    /// \return
    ///
    TimeT getSumOf(int& topCompetitors);

private:
    int _year;
    std::string _raceTag;
    std::map<TimeT, std::shared_ptr<Athlete>> _competitors; // in order by time, first is smallest
};

#endif // RACETYPE_H
