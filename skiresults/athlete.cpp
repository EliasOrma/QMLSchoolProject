#include "athlete.h"

Athlete::Athlete(std::string id, std::string name, std::string gender, std::string yearOfBirth, std::string locality, std::string club, std::string nationality)
{
    _id = id;
    _name = name;
    _gender = gender;
    _club = club;
    _nationality = nationality;
    _yearOfBirth = yearOfBirth;
    _locality = locality;
}

std::string Athlete::getID()
{
    return _id;
}

std::string Athlete::getName()
{
    return _name;
}

std::string Athlete::getGender()
{
    return _gender;
}

std::string Athlete::getClub()
{
    return _club;
}

std::string Athlete::getNationality()
{
    return _nationality;
}

std::string Athlete::getYearOfBirth()
{
    return _yearOfBirth;
}

std::string Athlete::getLocality()
{
    return _locality;
}
