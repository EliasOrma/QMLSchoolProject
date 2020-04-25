#include "controller.h"

Controller::Controller(TableModel *tbmodel, QStringListModel *rctagModel, QObject *parent) : QObject (parent)
{
    racetagModel = rctagModel;
    tableModel = tbmodel;
}

std::vector<QString> Controller::getEveryYear()
{
    auto var = dataHandler.raceTagsYearly();
    std::vector<QString> toReturn;
    for(auto i : var)
    {
        toReturn.push_back(QString::number(i.first));
    }
    return toReturn;
}

class timeFormatException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Time given in wrong format";
  }
} timeFormatEx;


void Controller::logError(std::string msg)
{
    std::cout << msg << std::endl;
}

void Controller::callShowResultsInQML(int tableType)
{
    // Tabletypes:
    // 1 : Table
    // 2 : Chart
    // 3 : Table & Chart
    emit showResults(tableType);
}


TimeT Controller::convertToTimeT(QString str)
{
    // time as string in form h:mm:ss.ss
    std::string s = str.toStdString();


    size_t n = std::count(s.begin(), s.end(), ':');
    if(n != 2)
    {
        throw timeFormatEx;
    }

    std::string delimiter = ":";
    size_t pos = 0;
    std::vector<std::string> token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token.push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }
    token.push_back(s);

    // time as string in form h:mm:ss.ss
    return TimeT(token[0],token[1],token[2]);
}



void Controller::search(QString state, QString year1, QString year2, QString starttime,
                        QString endtime, QString racetag1, QString racetag2,
                        QString athletename, QString sizeofranking, QString gender)
{
    // Different state IDs:
    // readbytime = 1
    // compareresultbyyear = 2
    // comparedistancebyyear = 3
    // showstatsbyeachyear = 4
    // athletetimedevelopment= 5
    // averagespeedbyranking = 6
    // bestathletebygenderinperiod = 7
    // showsortedresultsbyclubname = 8
    // showathletedistributionbycountry = 9
    // showtenbestteams = 10

    if(state == "1")
    {
        if(year1 == "" || starttime == "" || endtime == "" || racetag1 == "")
        {
            logError("Not enough parameters");
            return;
        }
        try
        {
            // Time Conversion
            int year = std::stoi(year1.toStdString());
            TimeT stime = convertToTimeT(starttime);
            TimeT etime = convertToTimeT(endtime);
            std::string rctag = racetag1.toStdString();
            if(stime > etime)
            {
                // Inform about stime being greater than end time
            }
            else
            {
                auto var = dataHandler.readByTime(year,stime,etime,rctag);
                auto result = dataconverter.readbytime(var);
                tableModel->changeData(result);
                callShowResultsInQML(1);
            }
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << '\n';;
        }
    }
    else if(state == "2")
    {
        // view: Table
        // std::string raceTag,int Year1, int Year2
        // std::map<int, std::vector<TimeT>> Best

        if(year1 == "" || year2 == "" || racetag1 == "" || sizeofranking == "")
        {
            logError("Not enough parameters");
            return;
        }
        try
        {
            // Time Conversion
            int firstyear = std::stoi(year1.toStdString());
            int secondyear = std::stoi(year2.toStdString());
            int sizeOfList = std::stoi(sizeofranking.toStdString());
            std::string rctag = racetag1.toStdString();
            if(firstyear > secondyear)
            {
                // Inform about this
            }
            else
            {
                auto var = dataHandler.compareResultByYear(rctag,firstyear,secondyear,sizeOfList);
                auto result = dataconverter.compareResultByYear(var);
                tableModel->changeData(result);
                callShowResultsInQML(1);
            }
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << '\n';;
        }
    }
    else if(state == "3")
    {
        // view: Table
        // Example: 1. 1.
        //          2. 2.
        // std::string raceTag1, std::string raceTag2, int year
        // std::map<std::string, std::vector<TimeT>>
        if(racetag1 == "" || racetag2 == "" || year1 == "")
        {
            logError("Not enough parameters");
            return;
        }
        try
        {
            // Time Conversion
            int year = std::stoi(year1.toStdString());
            std::string rctag1 = racetag1.toStdString();
            std::string rctag2 = racetag2.toStdString();
            if(rctag1 == rctag2)
            {
                // Inform about this
            }
            else
            {
                auto var = dataHandler.compareDistanceByYear(rctag1,rctag2,year);
                auto result = dataconverter.compareDistanceByYear(var);
                tableModel->changeData(result);
                callShowResultsInQML(1);
            }
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << '\n';;
        }
    }
    else if(state == "4")
    {
        // View: table
        // worst, best and average times of each race each year
        // std::map<int, std::vector<RaceStats>>
        auto var = dataHandler.statsByEachYear();
        auto result = dataconverter.statsByEachYear(var);
        tableModel->changeData(result);
        callShowResultsInQML(1);
    }
    else if(state == "5")
    {
        // Table
        // std::string athlete, int startYear, int endYear
        // Raceresult = Tuple<RaceTag,TimeT>
        // std::map<int, std::vector<raceResult>>
        if(athletename == "" || year1 == "" || year2 == "")
        {
            logError("Not enough parameters");
            return;
        }
        try
        {
            // Time Conversion
            int firstyear = std::stoi(year1.toStdString());
            int secondyear = std::stoi(year2.toStdString());
            std::string athName = athletename.toStdString();
            if(firstyear >= secondyear)
            {
                // Inform about this
            }
            else
            {
                auto var = dataHandler.athleteTimeDevelopment(athName,firstyear,secondyear);
                auto result = dataconverter.athleteTimeDevelopment(var);
                tableModel->changeData(result);
                callShowResultsInQML(1);
            }
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << '\n';;
        }
    }
    else if(state == "6")
    {
        // View: Table & Graph
        if(sizeofranking == "" || year1 == "" || year2 == "" || racetag1 == "")
        {
            logError("Not enough parameters");
            return;
        }
        try
        {
            // Time Conversion
            int firstyear = std::stoi(year1.toStdString());
            int secondyear = std::stoi(year2.toStdString());
            int sizeOfList = std::stoi(sizeofranking.toStdString());
            std::string rctag = racetag1.toStdString();
            if(firstyear > secondyear)
            {
                // Inform about this
            }
            else
            {
                auto var = dataHandler.averageSpeedByRanking(firstyear,secondyear,sizeOfList,rctag);
                auto result = dataconverter.averageSpeedByRanking(var,rctag);
                tableModel->changeData(result);
                callShowResultsInQML(1);
            }
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << '\n';;
        }
    }
    else if(state == "7")
    {
        // View: Table
        // year1, year2, gender, racetag
        // std::shared_ptr<Athlete>
        if(gender == "" || year1 == "" || year2 == "" || racetag1 == "")
        {
            logError("Not enough parameters");
            return;
        }
        try
        {
            // Time Conversion
            int firstyear = std::stoi(year1.toStdString());
            int secondyear = std::stoi(year2.toStdString());
            std::string athletegender = gender.toStdString();
            std::string rctag = racetag1.toStdString();
            if(firstyear > secondyear)
            {
                // Inform about this
            }
            else
            {
                auto var = dataHandler.bestAthleteByGenderInPeriod(athletegender,firstyear,secondyear,rctag);
                auto result = dataconverter.bestAthleteByGenderInPeriod(var);
                tableModel->changeData(result);
                callShowResultsInQML(1);
            }
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << '\n';
        }
    }
    else if(state == "8")
    {
        // View: Table
        if(year1 == "")
        {
            logError("Not enough parameters");
            return;
        }
        try
        {
            // Time Conversion
            int firstyear = std::stoi(year1.toStdString());
            auto var =  dataHandler.sortedResultsByClubName(firstyear);
            auto result = dataconverter.sortedResultsByClubName(var, firstyear);
            tableModel->changeData(result);
            callShowResultsInQML(1);
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << '\n';;
        }
    }
    else if(state == "9")
    {
        // TODO Piirakkamalli?
        auto var =  dataHandler.athleteDistributionByCountry();
        auto result = dataconverter.athleteDistributionByCountry(var);
        tableModel->changeData(result);
        callShowResultsInQML(1);
    }
    else if(state == "10")
    {
        // View: Table
        if(year1 == "" || racetag1 == "")
        {
            logError("Not enough parameters");
            return;
        }
        try
        {
            int firstyear = std::stoi(year1.toStdString());
            std::string rctag = racetag1.toStdString();

            auto var =  dataHandler.tenBestTeams(firstyear,rctag);
            auto result = dataconverter.tenBestTeams(var);
            tableModel->changeData(result);
            callShowResultsInQML(1);
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << '\n';;
        }
    }
    else
    {
        // Throw error
    }
}

void Controller::setNewRaceTags(int searchType, QString year1, QString year2)
{
    // searchtypes that have two inputs 2,5,6,7
    // If there is two years in input, newracetags is populated
    // with racetags that exists in both years
    if(searchType == 2 || searchType == 5 || searchType == 6 || searchType == 7)
    {
        int firstyear = std::stoi(year1.toStdString());
        int secondyear = std::stoi(year2.toStdString());
        auto data = dataHandler.raceTagsYearly();
        QStringList newRaceTags;
        newRaceTags.append("");
        for(auto firstRacetag : data[firstyear])
        {
            for(auto secondRacetag : data[secondyear])
            {
                if(secondRacetag == firstRacetag)
                {
                    newRaceTags.append(QString::fromStdString(firstRacetag));
                    break;
                }
            }
        }
        racetagModel->setStringList(newRaceTags);
    }
    else
    {
        int year = std::stoi(year1.toStdString());
        auto data = dataHandler.raceTagsYearly();
        QStringList newRaceTags;
        newRaceTags.append("");
        for(auto i : data[year])
        {
            newRaceTags.append(QString::fromStdString(i));
        }
        racetagModel->setStringList(newRaceTags);
    }
}



