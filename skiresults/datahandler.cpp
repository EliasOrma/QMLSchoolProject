#include "datahandler.h"
#include "racetype.h"
#include "athlete.h"
#include "timet.h"
#include <memory>
#include <tuple>

DataHandler::DataHandler()
{
    initializeReader();
    _athletesByName = _reader->readAthletes();
    _racesByYear = _reader->readReaces();
}

std::map<TimeT, std::string> DataHandler::readByTime(int year, TimeT startTime, TimeT endTime, std::string raceTag)
{
    std::map<TimeT, std::string> result;
    raceType* race = getRaceWithTag(year,raceTag); // nullptr if not found
    if(race == nullptr) return result;

    for(auto const& competitor : race->getCompetitors())
    {
        if(competitor.first > startTime && competitor.first < endTime)
        {
            if(competitor.second != nullptr){ // ensure athlete poiner is not empty
                result.insert(std::pair<TimeT,std::string> (competitor.first, competitor.second->getName()) );
            }
        }
    }
    return result;
}

std::map<int, std::vector<TimeT> > DataHandler::compareResultByYear(std::string raceTag, int Year1, int Year2, int sizeOfList)
{
    std::map<int, std::vector<TimeT>> result;

    if( _racesByYear.find(Year1) == _racesByYear.end() || _racesByYear.find(Year2) == _racesByYear.end())
    {
        return result;
    }
    std::vector<TimeT> times1 = getTimesWithRaceTag(Year1,raceTag);
    std::vector<TimeT> times2 = getTimesWithRaceTag(Year2, raceTag);
    if(static_cast<int>(times1.size()) > sizeOfList) times1.resize(static_cast<unsigned int>(sizeOfList), NO_TIME); // remove all above sizeOfList
    if(static_cast<int>(times2.size()) > sizeOfList) times2.resize(static_cast<unsigned int>(sizeOfList), NO_TIME); //
    result[Year1] = times1;
    result[Year2] = times2;
    return result;
}

std::map<int, std::multimap<TimeT, std::string> > DataHandler::compareResultByYearNames(std::string raceTag, int Year1, int Year2, std::vector<std::string> names)
{
    std::map<int, std::multimap<TimeT, std::string> > result;
    if( _racesByYear.find(Year1) == _racesByYear.end() || _racesByYear.find(Year2) == _racesByYear.end())
    {
        return result;
    }
    std::multimap<TimeT,std::string> timesYear1 = getTimesWithTagAndNames(Year1,raceTag,names);
    std::multimap<TimeT,std::string> timesYear2 = getTimesWithTagAndNames(Year2,raceTag,names);
    if(static_cast<int>(timesYear1.size()) > 0) // nothing added to result if raceTag not found
    {
        result[Year1] = timesYear1;
    }
    if(static_cast<int>(timesYear2.size()) > 0) // nothing added to result if raceTag not found
    {
        result[Year2] = timesYear2;
    }
    return result;
}

std::map<std::string, std::vector<TimeT> > DataHandler::compareDistanceByYear(std::string raceTag1, std::string raceTag2, int year)
{
    std::map<std::string,std::vector<TimeT>> result;
    if( _racesByYear.find(year) == _racesByYear.end() )
    {
        return result;
    }
    result[raceTag1] = getTimesWithRaceTag(year,raceTag1);
    result[raceTag2] = getTimesWithRaceTag(year, raceTag2);
    return result;
}


std::map<int, std::vector<RaceStats> > DataHandler::statsByEachYear()
{
    std::map<int, std::vector<RaceStats>> result;
    //    raceType* singleRace = nullptr;

    for(auto& oneYearRaces : _racesByYear)
    {
        std::vector<RaceStats> raceStatsForOneYear;
        for(raceType& race : oneYearRaces.second)
        {
            //            singleRace = &oneYearRaces.second[i];
            raceStatsForOneYear.push_back(getRaceStats(race));
        }
        result[oneYearRaces.first] = raceStatsForOneYear;
    }
    return result;
}

std::map<int, std::vector<DataHandler::raceResult> > DataHandler::athleteTimeDevelopment(std::string athlete, int startYear, int endYear)
{
    std::map<int, std::vector<raceResult> > result;
    auto athleteIt = _athletesByName.find(athlete);
    if(athleteIt == _athletesByName.end()) return result; // return empty map if name not found
    Athlete* ath = &athleteIt->second;

    if(endYear < startYear) std::swap(startYear,endYear);
    for(int &year = startYear; year <= endYear; ++year)
    {
        auto oneYearRaces = _racesByYear.find(year);
        if(oneYearRaces != _racesByYear.end())
        {
            std::vector<raceResult> raceResults = {};
            for(auto race = oneYearRaces->second.begin(); race != oneYearRaces->second.end(); ++race)
            {
                TimeT time = race->getCompetitorTime(*ath);
                if( !(time == NO_TIME) )
                {
                    raceResults.push_back(std::make_tuple(race->getRaceTag() ,time));
                }
            }
            result[year] = raceResults;
        }

    }
    return result;
}

std::map<int, TimeT> DataHandler::averageSpeedByRanking(int startYear, int endYear, int sizeOfList, std::string raceTag)
{
    std::map<int, TimeT> result;
    if(sizeOfList < 1) return result;
    if(endYear < startYear) std::swap(startYear,endYear);

    raceType* racePtr = nullptr;
    for(int year = startYear; year <= endYear; year++)
    {
        racePtr = getRaceWithTag(year, raceTag);
        if(racePtr != nullptr)
        {
            int numberOfCompetitors = static_cast<int>(racePtr->getCompetitors().size());
            if(numberOfCompetitors < sizeOfList) sizeOfList = numberOfCompetitors;
            TimeT sumOfTimes = racePtr->getSumOf(sizeOfList);
            std::shared_ptr<TimeT> averageTime = sumOfTimes.getAverageTime(sizeOfList);
            result.insert(std::pair<int,TimeT>(year,*averageTime));
        }

    }
    return result;
}


std::shared_ptr<Athlete> DataHandler::bestAthleteByGenderInPeriod(std::string gender, int startYear, int endYear, std::string raceTag)
{
    std::shared_ptr<Athlete> athPtr = nullptr;
    raceType* racePtr = nullptr;
    const TimeT* fastestTime = nullptr;
    if(endYear < startYear) std::swap(startYear,endYear);

    for(int year = startYear; year <= endYear; year++)
    {
        racePtr = getRaceWithTag(year,raceTag);
        if(racePtr != nullptr)
        {
            for(auto& competitor : *racePtr->getCompetitorsPtr())
            {
                if(competitor.second->getGender() == gender)
                {
                    if(fastestTime == nullptr || competitor.first < *fastestTime)
                    {
                        fastestTime = &(competitor.first);
                        athPtr = competitor.second;
                    }
                }
            }
        }
    }
    return athPtr;
}

std::map<std::string, std::vector<DataHandler::competitor *> > DataHandler::sortedResultsByClubName(int year)
{
    std::map<std::string, std::vector<competitor *> > result;
    auto oneYearRaces = _racesByYear.find(year);
    if(oneYearRaces != _racesByYear.end())
    {
        for(raceType& singleRace : oneYearRaces->second)
        {
            result[singleRace.getRaceTag()] = getResultsSortedByClub(singleRace);
        }
    }
    return result;
}

std::map<int, std::vector<std::string> > DataHandler::raceTagsYearly()
{
    std::map<int, std::vector<std::string> > result;

    for(auto& oneYearRaces : _racesByYear)
    {
        std::vector<std::string> yearly;
        for(raceType& race : oneYearRaces.second)
        {
            yearly.push_back(race.getRaceTag());
        }
        result[oneYearRaces.first] = yearly;
    }
            return result;
}


std::map<std::string, int> DataHandler::athleteDistributionByCountry()
{
    std::map<std::string, int> result;
    for(auto& athlete : _athletesByName)
    {
        const std::string nationality = athlete.second.getNationality();
        auto resultIt = result.find(nationality);
        if(resultIt != result.end())
        {
            resultIt->second = resultIt->second + 1;
        }
        else
        {
            result[nationality] = 1;
        }
    }
    return result;
}

std::map<std::string, std::list<Team>> DataHandler::tenBestTeams(int year, std::string raceTag)
{
    std::map<std::string, std::list<Team>> result;

    auto oneYearRaces = _racesByYear.find(year);
    if(oneYearRaces == _racesByYear.end()) return result; // check year exist

    raceType* racePtr = nullptr;
    // all races in given year
    if(raceTag == EMPTY)
    {
        for(raceType& singleRace : oneYearRaces->second)
        {
            std::string tag = singleRace.getRaceTag();
            std::list<Team> teams; // all teams
            std::list<Team*> validTeams; // pointers to teams of at least 4 athletes
            updateTeamsStats(teams, validTeams, singleRace);
            std::list<Team> tenBest = calculateTenBest(validTeams);
            result.insert(std::pair<std::string,std::list<Team>>(tag, tenBest));
        }
    }
    // only given race
    else
    {
        std::list<Team> teams; // all teams
        std::list<Team*> validTeams; // pointers to teams of at least 4 athletes
        racePtr = getRaceWithTag(year, raceTag);
        updateTeamsStats(teams, validTeams, *racePtr);
        std::list<Team> tenBest = calculateTenBest(validTeams);
        result.insert(std::pair<std::string,std::list<Team>>(raceTag, tenBest));
    }
    return result;
}

std::vector<TimeT> DataHandler::getTimesWithRaceTag(int year, std::string raceTag)
{
    std::vector<raceType> races = _racesByYear[year];
    raceType* singleRace = nullptr;
    std::vector<TimeT> times;

    for(std::vector<raceType>::size_type i = 0; i < races.size(); i++)
    {
        singleRace = &races[i];
        if(singleRace->getRaceTag() == raceTag)
        {
            for(auto& competitor : singleRace->getCompetitors())
            {
                times.push_back(competitor.first);
            }
            return times;
        }
    }
    return times; // empty if raceTag not found
}

std::multimap<TimeT, std::string> DataHandler::getTimesWithTagAndNames(int year, std::string raceTag, std::vector<std::string> &names)
{
    typedef std::pair<const TimeT,std::shared_ptr<Athlete>> com;
    std::vector<raceType> races = _racesByYear[year];
    raceType* singleRace = nullptr;
    bool nameFound = false;
    std::multimap<TimeT, std::string> times;

    for(std::vector<raceType>::size_type i = 0; i < races.size(); i++)
    {
        singleRace = &races[i];
        if(singleRace->getRaceTag() == raceTag)
        {   // correct race found
            for(std::string name : names)
            {
                nameFound = false;
                for(com& competitor : singleRace->getCompetitors()) // compare all competitors to given names
                {
                    if(competitor.second->getName() == name)
                    {
                        times.insert({competitor.first, name});
                        nameFound = true;
                        break;
                    }
                }
                if(!nameFound)
                {
                    times.insert({NO_TIME, name}); // NO_TIME if no matching competitor
                }
            }
            return times;
        }
    }
    return times; // empty if raceTag not found
}

RaceStats DataHandler::getRaceStats(raceType& singleRace)
{
    RaceStats result;
    auto competitorsPtr = singleRace.getCompetitorsPtr();
    int amountOfCompetitors = static_cast<int>(competitorsPtr->size());
    result.raceTag = singleRace.getRaceTag();
    result.competitors = amountOfCompetitors;
    result.fastest = &(competitorsPtr->begin()->first);
    result.slowest = &(competitorsPtr->rbegin()->first);
    std::shared_ptr<TimeT> sumOfTimes = std::make_shared<TimeT>(0,0,0);

    for(const auto& competitor : singleRace.getCompetitors())
    {
        *sumOfTimes = *sumOfTimes + competitor.first;
    }
    result.averageTime = sumOfTimes->getAverageTime(amountOfCompetitors);
    return result;
}

raceType* DataHandler::getRaceWithTag(int year, std::string raceTag)
{
    raceType* racePtr = nullptr;
    auto oneYearRaces = _racesByYear.find(year);
    if(oneYearRaces != _racesByYear.end())
    {
        for(auto it = oneYearRaces->second.begin(); it != oneYearRaces->second.end(); ++it)
        {
            if(it->getRaceTag() == raceTag)
            {
                racePtr = &(*it);
                return racePtr;
            }
        }
    }
    return racePtr;
}

std::vector<std::pair<const TimeT,std::shared_ptr<Athlete>>*> DataHandler::getResultsSortedByClub(raceType &race)
{
    typedef std::pair<const TimeT,std::shared_ptr<Athlete>> com;
    // copy pointers that points to map pairs
    std::vector<com*> sorted;
    for(com& competitor : *race.getCompetitorsPtr())
    {
        if(competitor.second->getClub() != ZERO){
            com* ptr = &competitor;
            sorted.push_back(ptr);
        }
    }
    // sort by club name
    std::sort(sorted.begin(),sorted.end(),[](const com* c1, const com* c2)
    {
        return c1->second->getClub() < c2->second->getClub();
    });
    return sorted;
}

void DataHandler::updateTeam(Team &team, const TimeT &newTime, std::list<Team*> &validTeams)
{
    ++team.count;
    team.times.push_back(newTime);
    if(team.count == 4)
    {
        team.isValid = true;
        Team* validteam = &team;
        validTeams.push_back(validteam);
    }
}

void DataHandler::updateTeamsStats(std::list<Team> &teams, std::list<Team*> &validTeams, raceType &race)
{
    typedef std::pair<const TimeT,std::shared_ptr<Athlete>> competitor;
    for(const competitor& competitor : race.getCompetitors())
    {
        std::string club = competitor.second->getClub();
        if(club != ZERO)
        {
            std::list<Team>::iterator it = std::find_if(teams.begin(),teams.end(),
                                                        [club](const Team& t){return t.clubName == club;});
            if(it != teams.end())
            {
                updateTeam(*it, competitor.first, validTeams);
            }
            else
            {
                // new value to teams
                Team newTeam = Team(club, 0, {},TimeT(0,0,0),false);
                updateTeam(newTeam, competitor.first, validTeams);
                teams.push_back(newTeam);
            }
        }
    }
}

std::list<Team> DataHandler::calculateTenBest(std::list<Team*> &validTeams)
{
    // calculate team times
    for(auto& team : validTeams)
    {
        for(unsigned int i = 0; i < 4; ++i)
        {
            team->teamTime = team->teamTime + team->times[i];
        }
    }
    // copy valid teams
    std::list<Team> tenBest;
    for(auto& team : validTeams)
    {
        Team t = *team;
        tenBest.push_back(t);
    }
    tenBest.sort(); // increasing time order
    // delete 11th and beyond ones
    if(tenBest.size() > 10)
    {
        std::list<Team>::iterator it = tenBest.begin();
        std::advance(it,10);
        tenBest.erase(it,tenBest.end());
    }
    return tenBest;
}



void DataHandler::initializeReader()
{
    _reader = std::make_shared<Reader>();
}
