#include "reader.h"
#include "timet.h"

#include <QDebug>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

Reader::Reader()
{
    athletesByID = {};
}

std::map<std::string, Athlete> Reader::readAthletes()
{
    std::map<std::string, Athlete> athleteMap;
    std::string line;
    const char *delimeter = ";";
    std::ifstream file("../skiresults/athleteData.txt");
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::vector<std::string> lineParts = split(line, *delimeter);
            std::string name = lineParts.at(2);
            std::string clubName = lineParts.at(6);
            clubName.erase(std::remove(clubName.begin(), clubName.end(), '\r'), clubName.end()); // removes \r from back
            std::shared_ptr<Athlete> athlete = std::make_shared<Athlete>(lineParts.at(0), name, lineParts.at(1), lineParts.at(5), lineParts.at(3), clubName, lineParts.at(4));
            athleteMap.insert({name, *athlete});

            athletesByID.insert(std::pair<std::string,std::shared_ptr<Athlete>>(lineParts.at(0),athlete));
        }
        file.close();
    }
    return athleteMap;
}

std::map<int, std::vector<raceType> > Reader::readReaces()
{
    std::map<int, std::vector<raceType>> raceMap;
    std::string line;
    const char *delimeter = ";";
    const char *timeDelimeter = ":";
    std::ifstream file("../skiresults/skiDataByYearAndRoutes.txt");
    if (file.is_open())
    {
        int year = 0;
        std::string raceTag;
        QChar x = *"~";
        QChar y = *"#";
        raceType* racePtr = nullptr;
        while (std::getline(file, line))
        {
            if (line.at(0) == x)
            {
                year = std::stoi(line.substr(1, line.size()));
                std::vector<raceType> emptyVector;
                raceMap.insert({year, emptyVector});
            }
            else if (line.at(0) == y)
            {     
                raceTag = line.substr(1,line.size());
                raceTag.erase(std::remove(raceTag.begin(), raceTag.end(), '\r'), raceTag.end());
                raceType newRace(year, raceTag);
                raceMap.at(year).push_back(newRace);
                for(auto& race : raceMap[year]){
                    if(race.getRaceTag() == raceTag){
                        racePtr = &race;
                        continue;
                    }
                }
            }
            else
            {
                std::vector<std::string> lineParts = split(line, *delimeter);
                std::vector<std::string> timeElems = split(lineParts.at(2), *timeDelimeter);
                try
                {
                    TimeT time(timeElems.at(0), timeElems.at(1), timeElems.at(2));
                    std::string athID = lineParts.at(0);
                    auto athIt = athletesByID.find(athID);
                    if(athIt != athletesByID.end())
                    {
                        racePtr->addCompetitors(time,athIt->second);
                    }
                }
                catch (std::out_of_range & exeption)
                {
                    std::cerr << "Invalid time format: " << exeption.what() << '\n';
                }

            }
        }
        file.close();
    }
    return raceMap;
}

std::vector<std::string> Reader::split(std::string &line, char delimeter)
{
    std::vector<std::string> lineParts;
    size_t pos = 0;
    std::string part;
    while ((pos = line.find(delimeter)) != std::string::npos) {
        part = line.substr(0, pos);
        lineParts.push_back(part);
        line.erase(0, pos + 1);
    }
    lineParts.push_back(line);
    return lineParts;
}
