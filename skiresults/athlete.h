#ifndef ATHLETE_H
#define ATHLETE_H

#include <iostream>

///
/// \brief The Athlete class contains data of spesific athlete.
///
class Athlete
{

public:
    Athlete(std::string id,std::string name, std::string gender, std::string yearOfBirth, std::string locality, std::string club, std::string nationality);

    ///
    /// \brief getID
    /// \return
    ///
    std::string getID();

    ///
    /// \brief getName gets the name of the athlete
    /// \return
    ///
    std::string getName();

    ///
    /// \brief getGender
    /// \return
    ///
    std::string getGender();

    ///
    /// \brief getClub
    /// \return
    ///
    std::string getClub();

    ///
    /// \brief getNationality
    /// \return
    ///
    std::string getNationality();

    ///
    /// \brief getYearOfBirth
    /// \return
    ///
    std::string getYearOfBirth();

    ///
    /// \brief getLocality
    /// \return
    ///
    std::string getLocality();

private:
    std::string _id;
    std::string _name;
    std::string _gender;
    std::string _yearOfBirth;
    std::string _locality;
    std::string _club;
    std::string _nationality;
};

#endif // ATHLETE_H
