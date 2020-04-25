#ifndef DATATYPECONVERTER_H
#define DATATYPECONVERTER_H

#include <QObject>
#include <map>
#include <QVector>
#include <algorithm>
#include <tuple>

#include <racestats.h>
#include <timet.h>
#include <datahandler.h>

class DataTypeConverter
{
public:
    DataTypeConverter();

    QVector<QVector<QString>> readbytime(std::map<TimeT, std::string> data);
    QVector<QVector<QString>> compareResultByYear(std::map<int, std::vector<TimeT>> data);
    QVector<QVector<QString>> compareDistanceByYear(std::map<std::string, std::vector<TimeT>> data);
    QVector<QVector<QString>> statsByEachYear(std::map<int, std::vector<RaceStats>> data);
    QVector<QVector<QString>> athleteTimeDevelopment(std::map<int, std::vector<DataHandler::raceResult> > data);
    QVector<QVector<QString>> averageSpeedByRanking(std::map<int, TimeT> data, std::string racetag);
    QVector<QVector<QString>> bestAthleteByGenderInPeriod(std::shared_ptr<Athlete> data);
    QVector<QVector<QString>> sortedResultsByClubName(std::map<std::string, std::vector<DataHandler::competitor *>> data, int year);
    QVector<QVector<QString>> athleteDistributionByCountry(std::map<std::string,int> data);
    QVector<QVector<QString>> tenBestTeams(std::map<std::string, std::list<Team>> data);
};

#endif // DATATYPECONVERTER_H
