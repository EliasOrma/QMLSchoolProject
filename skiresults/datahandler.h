#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <tuple>
#include <QObject>
#include <list>

#include "racetype.h"
#include "athlete.h"
#include "reader.h"
#include "timet.h"
#include "team.h"
#include "racestats.h"

const std::string EMPTY = "";
const std::string ZERO ="0";

class DataHandler
{

public:

    typedef std::string raceTag;
    typedef std::tuple<raceTag, TimeT> raceResult;
    typedef std::pair<const TimeT,std::shared_ptr<Athlete>> competitor;

    DataHandler();

    ///
    /// \brief readByTime gets times of the skiers in certain time period and race.
    /// \param year, year of the results
    /// \param startTime, lowest time in time period
    /// \param endTime, highest time in time period
    /// \note only one race per search
    /// \return map<time, name>
    ///
    std::map<TimeT, std::string> readByTime(int year, TimeT startTime, TimeT endTime, std::string raceTag);

    ///
    /// \brief compareResultByYear gets results of the same distance in two different years.
    /// \param raceTag tag of the certain race
    /// \param Year1, first year to be compared
    /// \param Year2, second year to be compared
    /// \param sizeOfList the number of rankings counted from 1st place.
    /// \note if sizeOfList is greater than number of results, all results are passed without any information
    /// \return map, < year, vector of race results(times)>, vector is empty if raceTag is not found.
    ///         map is empty if either year is not found.
    ///
    std::map<int, std::vector<TimeT>> compareResultByYear(std::string raceTag,int Year1, int Year2, int sizeOfList);
    // saman vuoden vertailu?
    ///
    /// \brief compareResultByYearNames
    /// \param raceTag tag of the certain race
    /// \param Year1, first year to be compared
    /// \param Year2, second year to be compared
    /// \param names the list of the names that the user wants to compare
    /// \return map<year, map<time,athlete name>>
    ///         empty if either year is not found.
    ///         the results of the year are not included if the race has not been in a particular year.
    ///         times have been replaced with NO_TIME if the athlete has not participated in the race.
    ///
    std::map<int, std::multimap<TimeT, std::string>> compareResultByYearNames(std::string raceTag,int Year1, int Year2, std::vector<std::string> names);

    ///
    /// \brief compareDistanceByYear gets two different race results in the same year.
    /// \param raceTag1, first distance to be compared
    /// \param raceTag2, second distance to be compared
    /// \param year, year of the races.
    /// \return map, < raceTag, vector of race results(times)>, vector is empty if raceTag is not found.
    ///         map is empty if year is not found.
    ///
    std::map<std::string, std::vector<TimeT>>  compareDistanceByYear(std::string raceTag1, std::string raceTag2, int year);

    ///
    /// \brief statsByEachYear gets amount of competitors, winners finish time, last participants finish time
    /// and average speeds of each distance
    /// \return map, < year, vector of each race stats per year>
    ///
    std::map<int, std::vector<RaceStats>>  statsByEachYear();


    ///
    /// \brief athleteTimeDevelopment gets the data of the certain athlete's results in certain time period.
    /// \param athlete, name of the certain athlete
    /// \param startYear, first year of the time period
    /// \param endYear, second year of the time period
    /// \return map, < year, vector of results each race separated >
    ///
    std::map<int, std::vector<raceResult>>  athleteTimeDevelopment(std::string athlete, int startYear, int endYear);

    ///
    /// \brief averageSpeedByRanking gets the average speed by ranking in certain time period and race
    /// \param startYear, first year of the time period
    /// \param endYear, second year of the time period
    /// \param sizeOfList, amount of wanted results starting by the best athlete.
    /// \return map, <year, average time> if no certain year or race is found, it is not added to the data structure
    ///
    std::map<int, TimeT> averageSpeedByRanking(int startYear, int endYear, int sizeOfList, std::string raceTag);

    ///
    /// \brief bestAthleteByGenderInPeriod, gets the best man's or woman's ranking in certain time period
    /// \param gender
    /// \param startYear, first year of the time period
    /// \param endYear, second year of the time period
    /// \return pointer to the athlete, null if none is found
    ///
    std::shared_ptr<Athlete> bestAthleteByGenderInPeriod(std::string gender,int startYear, int endYear, std::string raceTag);

    ///
    /// \brief sortedResultsByClubName, gets each result of the certain year and sorts it alphabetically by club name.
    /// \param year, year of the results
    /// \return map<raceTag, map<time, athlete pointer> >
    ///
    //std::map<std::string ,std::map<TimeT, std::shared_ptr<Athlete>>> sortedResultsByClubName(int year); // yksi kisa vai kaikki? nyt tulee kaikki
    std::map<std::string, std::vector<competitor *> > sortedResultsByClubName(int year);


    ///
    /// \brief athleteDistributionByCountry, gets the distribution of the athletes by countries
    /// \note also empty nationalities are added with key "" (all athletes are taken into account when displayed)
    /// \return map<nationality, count>
    ///
    std::map<std::string,int> athleteDistributionByCountry(); // voisi lisätä haun per vuosi tai kisa

    ///
    /// \brief tenBestTeams, gets ten best teams. Team is a group of 4 best athletes in same club. If there is not 4 skiers
    /// in the same club, team can not be formed. If there is more than 4 athletes, only the athletes with best finish times
    /// are taken in to count. Team result is sum of 4 best athletes results.
    /// \note if raceTag is empty all races in year are included
    /// \return list<raceTag, team data>
    ///
    std::map<std::string, std::list<Team>> tenBestTeams(int year, std::string raceTag);


    ///
    /// \brief raceTagsYearly
    /// \return
    ///
    std::map<int, std::vector<std::string> > raceTagsYearly();

private:

    std::map<int, std::vector<raceType>> _racesByYear;
    std::map<std::string, Athlete> _athletesByName;
    std::shared_ptr<Reader> _reader;

    ///
    /// \brief Initialized Reader-object, called in constructor
    ///
    void initializeReader();

    ///
    /// \brief getTimesWithRaceTag, called in compareResultsByYear
    /// \param year
    /// \param raceTag
    /// \return vector of finish times in certain year and race
    ///
    std::vector<TimeT> getTimesWithRaceTag(int year, std::string raceTag);

    ///
    /// \brief getTimesWithTagAndNames
    /// \param year
    /// \param raceTag
    /// \param names
    /// \return multimap of finish times in certain year and race.
    ///         Only athletes whose names are on the 'names' list will be included.
    ///         times have been replaced with NO_TIME if the athlete has not participated in the race.
    ///
    std::multimap<TimeT,std::string> getTimesWithTagAndNames(int year, std::string raceTag, std::vector<std::string>& names);

    ///
    /// \brief getRaceStats, called in statsByEachYear
    /// \param singleRace
    /// \return
    ///
    RaceStats getRaceStats(raceType& singleRace);

    ///
    /// \brief getRaceWithTag, called in datahandler public functions
    /// \param year
    /// \param raceTag
    /// \return pointer to the race in certain year.
    ///         nullptr if any race not found
    ///
    raceType* getRaceWithTag(int year, std::string raceTag);

    ///
    /// \brief getResultsSortedByClub resorts certain race results alphabetically by club name. Called in sortedResultsByClubName
    /// \param race
    /// \return resorted vector
    ///
    std::vector<std::pair<const TimeT,std::shared_ptr<Athlete>>*> getResultsSortedByClub(raceType& race);

    ///
    /// \brief updateTeam Updates team times when new a competitor added to team. Called in updateTeamsStats.
    /// \param team
    /// \param newTime
    /// \param validTeams
    ///
    void updateTeam(Team& team, const TimeT& newTime, std::list<Team*>& validTeams);

    ///
    /// \brief updateTeamsStats updates all teams with times from one race. Called in tenBestTeams
    /// \param teams
    /// \param validTeams
    /// \param race
    ///
    void updateTeamsStats(std::list<Team>& teams, std::list<Team*>& validTeams, raceType& race);

    ///
    /// \brief calculateTenBest Calculates teams's total times and determines the top ten. Called in tenBestTeams
    /// \param validTeams
    /// \return
    ///
    std::list<Team> calculateTenBest(std::list<Team*>& validTeams);


};

#endif // DATAHANDLER_H
