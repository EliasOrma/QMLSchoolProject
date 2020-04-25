#ifndef DATAHANDLERTEST_H
#define DATAHANDLERTEST_H

#include "datahandler.h"
#include "racetype.h"
#include "timet.h"

class DataHandlerTest: public DataHandler
{
public:
    DataHandlerTest();

    void test_readByTime();

    void test_compareResultsByYear();

    void test_compareResultsByYearNames();

    void test_compareDistanceByYear();

    void test_statsByEachYear();

    void test_athleteTimeDevelopment();

    void test_averageSpeedByRanking();

    void test_bestAthleteByGenderInPeriod();

    void test_sortedResultsByClubName();

    void test_athleteDistributionByCountry();

    void test_tenBestTeams();

    void test_tags();

    void test_all();
private:

};

#endif // DATAHANDLERTEST_H
