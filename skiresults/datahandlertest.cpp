#include "datahandlertest.h"
#include "timet.h"
#include "racetype.h"
#include <iostream>
#include <QDebug>

DataHandlerTest::DataHandlerTest(): DataHandler()
{

}

void DataHandlerTest::test_readByTime()
{
    std::cout<<"\n----readByTime-----\n"<<std::endl;
    TimeT start(0,2,0);
    TimeT end(2,50,0);
    std::string tag = "P20";
    int year = 2019;
    auto result = readByTime(year,start,end,tag);
    for(auto& a : result){
        std::cout<<a.first.toString()<<"  "<<a.second<<std::endl;
    }
}

void DataHandlerTest::test_compareResultsByYear()
{
    std::cout<<"\n----compareResultsByYear-----\n"<<std::endl;
    std::string tag = "P32";
    int year1 = 2018;
    int year2 = 2015;
    int sizeOfList = 7;
    std::map<int, std::vector<TimeT>> result = compareResultByYear(tag,year1,year2,sizeOfList);
    for(std::pair< const int, std::vector<TimeT>>& race : result)
    {
        std::cout<<"-------"<<race.first<<"  "<<tag<<std::endl;
        for(TimeT& time : race.second)
        {
            std::cout<< time.toString() << std::endl;
        }
    }

}

void DataHandlerTest::test_compareResultsByYearNames()
{
    std::cout<<"\n----compareResultsByYearNames-----\n"<<std::endl;
    std::string tag = "P32";
    int year1 = 2018;
    int year2 = 2014;
    std::vector<std::string> names = {"Berg Noora","Lusa Tua","Leino Elli"};
    std::map<int, std::multimap<TimeT, std::string>> result = compareResultByYearNames(tag,year1,year2,names);
    for(std::pair<int, std::multimap<TimeT, std::string>> year : result)
    {
        std::cout<<year.first<<std::endl;
        for(std::pair<const TimeT,std::string>& ath : year.second)
        {
            std::cout << ath.first.toString()<<"  "<<ath.second<<std::endl;
        }
    }
}

void DataHandlerTest::test_compareDistanceByYear()
{
    std::cout<<"\n----compareDistanceByYear-----\n"<<std::endl;
    std::string tag1 = "P32";
    std::string tag2 = "P100";
    int year = 2017;
    auto result = compareDistanceByYear(tag1,tag2,year);
    for(std::pair< const std::string, std::vector<TimeT>>& race : result)
    {
        std::cout<<race.first<<std::endl;
        for(TimeT& time : race.second)
        {
            std::cout<< time.toString() << std::endl;
        }
    }
}

void DataHandlerTest::test_statsByEachYear()
{
    std::cout<<"\n----statsByEachYear-----\n"<<std::endl;
    auto result = statsByEachYear();
    for(auto& year : result)
    {
        std::cout<< year.first << std::endl;
        for(RaceStats& race : year.second)
        {
            std::cout << race.raceTag<<"  "<< race.competitors<<"  "<< race.fastest->toString()<<"  "
                      << race.slowest->toString()<<"  "<< race.averageTime->toString()<<"  "<<std::endl;
        }
    }
}

void DataHandlerTest::test_athleteTimeDevelopment()
{
    std::cout<<"\n----athleteTimeDevelopment-----\n"<<std::endl;
    std::string athName = "Kanerva Petri";
    int year1 = 2020;
    int year2 = 2015;
    std::map<int, std::vector<raceResult>> result = athleteTimeDevelopment(athName, year1, year2);
    for(auto& res : result)
    {
        std::cout<<res.first<<std::endl;
        for(auto& race : res.second)
        {
            std::cout<< std::get<0>(race) <<"  "<< std::get<1>(race).toString() <<std::endl;
        }
    }
}

void DataHandlerTest::test_averageSpeedByRanking()
{
    std::cout<<"\n----averageSpeedByRanking-----\n"<<std::endl;
    std::string tag = "P32";
    int year1 = 2020;
    int year2 = 2015;
    int listSize = 2;
    std::map<int, TimeT> result = averageSpeedByRanking(year1,year2,listSize,tag);
    for(auto& year : result)
    {
        std::cout<<year.first<< "   " <<year.second.toString()<<std::endl;
    }
}

void DataHandlerTest::test_bestAthleteByGenderInPeriod()
{
    std::cout<<"\n----bestAthleteByGenderInPeriod-----\n"<<std::endl;
    int year1 = 2010;
    int year2 = 2020;
    std::string gender = "M";
    std::string tag = "P32";
    std::shared_ptr<Athlete> result = bestAthleteByGenderInPeriod(gender,year1, year2,tag);

    std::cout << result->getGender() <<"  "<<result->getName()<<"  "<<result->getYearOfBirth()<<"  "<<result->getNationality();
}

void DataHandlerTest::test_sortedResultsByClubName()
{
    std::cout<<"\n----sortedResultsByClubName-----\n"<<std::endl;
    int year = 2018;
    std::map<std::string ,std::vector<std::pair<const TimeT, std::shared_ptr<Athlete>>*> > result = sortedResultsByClubName(year);
    for(auto& race : result)
    {
        std::cout<<race.first<<std::endl;
        for(auto& res : race.second)
        {
            std::cout<< res->first.toString() <<"  "<< res->second->getName() <<"  "<< res->second->getClub() <<std::endl;
        }
    }
}

void DataHandlerTest::test_athleteDistributionByCountry()
{
    std::cout<<"\n----athleteDistributionByCountry-----\n"<<std::endl;
    std::map<std::string, int> result = athleteDistributionByCountry();
    for(auto country: result)
    {
        std::cout << country.first <<"   "<<country.second<<std::endl;
    }
}

void DataHandlerTest::test_tenBestTeams()
{
    std::cout<<"\n----tenBestTeams-----\n"<<std::endl;
    int year = 2019;
    std::string tag = "V50";
    std::map<std::string, std::list<Team>> result = tenBestTeams(year,tag);
    for(auto& race : result)
    {
        std::cout << race.first <<std::endl;
        for(auto& team : race.second)
        {
            std::cout << team.clubName <<"  "<< team.teamTime.toString()<<std::endl;

        }
    }
}

void DataHandlerTest::test_tags()
{
    std::map<int, std::vector<std::string>> result = raceTagsYearly();
    for(auto year : result)
    {
        std::cout<<year.first<<std::endl;
        for(auto tag : year.second)
        {
            std::cout<<"  "<<tag<<std::endl;
        }
    }
}

void DataHandlerTest::test_all()
{
    test_readByTime();

    test_compareResultsByYear();

    test_compareResultsByYearNames();

    test_compareDistanceByYear();

    test_statsByEachYear();

    test_athleteTimeDevelopment();

    test_averageSpeedByRanking();

    test_bestAthleteByGenderInPeriod();

    test_sortedResultsByClubName();

    test_athleteDistributionByCountry();

    test_tenBestTeams();

    test_tags();
}
