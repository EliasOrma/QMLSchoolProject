#include "team.h"

Team::Team(std::string _clubName, int _count, std::vector<TimeT> _times, TimeT _teamTime,  bool _isValid)
{
    clubName = _clubName;
    count = _count;
    times = _times;
    teamTime = _teamTime;
    isValid = _isValid;
}
