#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <timet.h>
#include <vector>

class Team
{
public:
    Team(std::string _clubName, int _count, std::vector<TimeT> _times, TimeT _teamTime,  bool _isValid);
    std::string clubName;
    int count;
    std::vector<TimeT> times;
    TimeT teamTime;
    bool isValid;

    inline bool operator<(const Team& other)
    {
        if( !isValid ) return false;
        if( teamTime < other.teamTime) return true;
        else return false;
    }
};

#endif // TEAM_H
