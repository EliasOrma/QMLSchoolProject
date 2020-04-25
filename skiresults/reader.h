#ifndef READER_H
#define READER_H

#include<map>
#include <string>
#include <unordered_map>

#include "athlete.h"
#include "racetype.h"

class Reader
{
public:
    ////
    /// \brief Constructor
    ///
    Reader();

    ////
    /// \brief readAthletes, reads skiDataByYearAndRoutes.txt and creates Athlete-objects based on it.
    /// \return a map with athlete's name as key and Athlete-object as value.
    ///
    std::map<std::string, Athlete> readAthletes();

    ////
    /// \brief readReaces, reads skiDataByYearAndRoutes.txt and creates RaceType-objects based on it.
    /// \param athleteMap, the map returned by the function above. Used for creating pointes to athletes.
    /// \return a map with athlete's name as key and RaceType-object as value.
    ///
    std::map<int, std::vector<raceType>> readReaces();

private:

    ////
    /// \brief split, funtion created to split lines from skiDataByYearAndRoutes.txt.
    /// \param line, the line to be splitted.
    /// \param delimeter
    /// \return a vector of strings.
    ///
    std::vector<std::string> split(std::string & line, char delimeter);

    std::unordered_map<std::string, std::shared_ptr<Athlete>> athletesByID;
};

#endif // READER_H
