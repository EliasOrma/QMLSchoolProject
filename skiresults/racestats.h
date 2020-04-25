#ifndef RACESTATS_H
#define RACESTATS_H

#include <iostream>
#include <timet.h>

class RaceStats
{
public:
    RaceStats();
    std::string raceTag;
    int competitors;
    const TimeT* fastest;
    const TimeT* slowest;
    std::shared_ptr<TimeT> averageTime;
};

#endif // RACESTATS_H
