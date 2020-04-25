#include "datatypeconverter.h"

DataTypeConverter::DataTypeConverter()
{

}

QVector<QVector<QString>> DataTypeConverter::readbytime(std::map<TimeT, std::string> data)
{
    if(data.size() == 0)
    {
        QVector<QVector<QString>> toReturn;
        toReturn.append({"No Results found with these parameters"});
        return toReturn;
    }

    QVector<QVector<QString>> toReturn;
    QVector<QString> toAdd = {"Name","Time"};

    // Header
    toReturn.append(toAdd);

    for(auto i : data)
    {
        toAdd = {QString::fromStdString(i.second), QString::fromStdString(i.first.toString())};
        toReturn.append(toAdd);
    }
    return toReturn;
}

QVector<QVector<QString>> DataTypeConverter::compareResultByYear(std::map<int, std::vector<TimeT> > data)
{
    std::cout << "Size Of Data: " + std::to_string(data.size()) << std::endl;
    if(data.size() == 0 || data.size() == 1)
    {
        QVector<QVector<QString>> toReturn;
        toReturn.append({"No Results found with these parameters"});
        return toReturn;
    }

    std::vector<int> years;
    for(auto i : data)
    {
        years.push_back(i.first);
    }
    std::sort(years.begin(),years.begin());

    int firstYear = years.at(0);
    int secondYear = years.at(1);
    std::vector<TimeT> firstYearResults = data[firstYear];
    std::vector<TimeT> secondYearResults = data[secondYear];

    QVector<QVector<QString>> toReturn;
    QVector<QString> toAdd = {"Place",QString::fromStdString(std::to_string(firstYear)),
                              QString::fromStdString(std::to_string(secondYear))};
    // Header
    toReturn.append(toAdd);

    unsigned int index = 0;
    while(true)
    {
        if(firstYearResults.size() <= index || secondYearResults.size() <= index)
        {
            break;
        }

        QString firstAdd = "";
        QString secondAdd = "";

        if(firstYearResults.size() > index)
        {
            firstAdd = QString::fromStdString(firstYearResults.at(index).toString());
        }
        if(secondYearResults.size() > index)
        {
            secondAdd = QString::fromStdString(secondYearResults.at(index).toString());
        }
        toAdd = {QString::number(index+1) + ".",firstAdd,secondAdd};
        toReturn.append(toAdd);
        index++;
    }
    return toReturn;
}

QVector<QVector<QString> > DataTypeConverter::compareDistanceByYear(std::map<std::string, std::vector<TimeT> > data)
{
    if(data.size() == 0)
    {
        QVector<QVector<QString>> toReturn;
        toReturn.append({"No Results found with these parameters"});
        return toReturn;
    }

    QVector<QVector<QString>> toReturn;
    QVector<QString> toAdd;

    std::vector<QString> raceTags;
    for(auto i : data)
    {
        raceTags.push_back(QString::fromStdString(i.first));
    }
    QString firstRaceTag = raceTags.at(0);
    QString secondRaceTag = raceTags.at(1);
    std::vector<TimeT> firstYearResults = data[firstRaceTag.toStdString()];
    std::vector<TimeT> secondYearResults = data[secondRaceTag.toStdString()];

    toAdd = {"Place",firstRaceTag,secondRaceTag};
    toReturn.append(toAdd);

    unsigned int index = 0;
    while(true)
    {
        if(firstYearResults.size() <= index || secondYearResults.size() <= index)
        {
            break;
        }

        QString firstAdd = "";
        QString secondAdd = "";

        if(firstYearResults.size() > index)
        {
            firstAdd = QString::fromStdString(firstYearResults.at(index).toString());
        }
        if(secondYearResults.size() > index)
        {
            secondAdd = QString::fromStdString(secondYearResults.at(index).toString());
        }
        QString rankingNumber = QString::number(index+1) + ".";
        toAdd = {rankingNumber,firstAdd,secondAdd};
        toReturn.append(toAdd);
        index++;
    }
    return toReturn;
}

QVector<QVector<QString> > DataTypeConverter::statsByEachYear(std::map<int, std::vector<RaceStats> > data)
{
    if(data.size() == 0)
    {
        QVector<QVector<QString>> toReturn;
        toReturn.append({"No Results found with these parameters"});
        return toReturn;
    }

    QVector<QVector<QString>> toReturn;
    QVector<QString> toAdd;

    // Header
    toReturn.append({"Year","Racetag","Competitor amount","Winner's time","Worst time","Average time"});

    for(auto i : data)
    {
        QString year = QString::number(i.first);
        for(auto raceStats : i.second)
        {
            toAdd = {
                year,
                QString::fromStdString(raceStats.raceTag),
                QString::number(raceStats.competitors),
                QString::fromStdString(raceStats.fastest->toString()),
                QString::fromStdString(raceStats.slowest->toString()),
                QString::fromStdString(raceStats.averageTime->toString())
            };
            toReturn.append(toAdd);
        }
    }
    return toReturn;
}

QVector<QVector<QString> > DataTypeConverter::athleteTimeDevelopment(std::map<int, std::vector<DataHandler::raceResult> > data)
{
    // TODO
    // Structure:
    // rctag| 2016 | 2017 | 2018
    // P20  | time | time | time
    // ...
    if(data.size() == 0 || data.size() == 1)
    {
        QVector<QVector<QString>> toReturn;
        toReturn.append({"No Results found with these parameters"});
        return toReturn;
    }

    QVector<QVector<QString>> toReturn;
    QVector<QString> toAdd;

    toAdd.append("Racetag");
    // Create header & Get all racetags
    std::vector<QString> raceTags;

    for(auto i : data)
    {
        toAdd.append(QString::number(i.first));
        for(auto race : i.second)
        {
            // get tag from tuple and check if doesn't exist in tag list
            QString tag = QString::fromStdString(std::get<0>(race));
            if (std::find(raceTags.begin(), raceTags.end(),tag) == raceTags.end())
            {
                raceTags.push_back(tag);
            }
        }
    }
    // Add Header
    toReturn.append(toAdd);
    toAdd.clear();

    bool tagFound = false;
    for(auto rcTag : raceTags)
    {
        toAdd.append(rcTag);
        for(auto i : data)
        {
            tagFound = false;
            for(auto vec : i.second)
            {
                QString tag = QString::fromStdString(std::get<0>(vec));
                if(tag == rcTag)
                {
                    QString time = QString::fromStdString(std::get<1>(vec).toString());
                    toAdd.append(time);
                    tagFound = true;
                    break;
                }
            }
            if(!tagFound)
            {
                toAdd.append("");
            }
        }
        toReturn.append(toAdd);
        toAdd.clear();
    }
    return toReturn;
}

QVector<QVector<QString> > DataTypeConverter::averageSpeedByRanking(std::map<int, TimeT> data, std::string racetag)
{
    // Structure
    // Racetag | 2016 | 2017 | 2018
    // Avgtime | time | time | time
    if(data.size() == 0)
    {
        QVector<QVector<QString>> toReturn;
        toReturn.append({"No Results found with these parameters"});
        return toReturn;
    }

    QVector<QVector<QString>> toReturn;
    QVector<QString> toAddfirst;
    QVector<QString> toAddsecond;

    toAddfirst.append("Racetag");
    toAddsecond.append(QString::fromStdString(racetag));

    for(auto i : data)
    {
        toAddfirst.append(QString::number(i.first));
        toAddsecond.append(QString::fromStdString(i.second.toString()));
    }
    toReturn.append(toAddfirst);
    toReturn.append(toAddsecond);
    return toReturn;
}

QVector<QVector<QString> > DataTypeConverter::bestAthleteByGenderInPeriod(std::shared_ptr<Athlete> data)
{
    // Structure
    // Name | YearOfBirth | Nationality | Club | Locality
    // ...  | ....
    if(data == nullptr)
    {
        QVector<QVector<QString>> toReturn;
        toReturn.append({"No Results found with these parameters"});
        return toReturn;
    }
    QVector<QVector<QString>> toReturn;
    toReturn.append({"Name","Year of Birth", "Nationality","Locality", "Club"});
    Athlete ath = *data.get();
    toReturn.append({
                        QString::fromStdString(ath.getName()),
                        QString::fromStdString(ath.getYearOfBirth()),
                        QString::fromStdString(ath.getNationality()),
                        QString::fromStdString(ath.getClub()),
                        QString::fromStdString(ath.getLocality())
                    });

    return toReturn;
}

QVector<QVector<QString> > DataTypeConverter::sortedResultsByClubName(std::map<std::string, std::vector<DataHandler::competitor *> > data, int year)
{
    // TODO
    // Structure:
    // Year |
    // P20  | Name |
    //      | Time |
    if(data.size() == 0)
    {
        QVector<QVector<QString>> toReturn;
        toReturn.append({"No Results found with these parameters"});
        return toReturn;
    }

    unsigned int mostCompetitors = 0;

    for(auto i : data)
    {
        if(i.second.size() > mostCompetitors)
        {
            mostCompetitors = i.second.size();
        }
    }

    QVector<QVector<QString>> toReturn;
    QVector<QString> toAdd;
    QVector<QString> toAdd2;
    QVector<QString> toAdd3;
    toAdd.append(QString::number(year));

    for(unsigned int i = 0; i != mostCompetitors; i++)
    {
        toAdd.append("");
    }

    toReturn.append(toAdd);
    toAdd.clear();

    //std::cout << "mostcomps: " + std::to_string(mostCompetitors) << std::endl;

    for(auto i : data)
    {
        toAdd.append(QString::fromStdString(i.first));
        toAdd2.append("Club");
        toAdd3.append("Name");
        for(auto j : i.second)
        {
            toAdd.append(QString::fromStdString(j->first.toString()));
            toAdd2.append(QString::fromStdString(j->second.get()->getClub()));
            toAdd3.append(QString::fromStdString(j->second.get()->getName()));
        }
        //std::cout << "first: " + std::to_string(toAdd.size()) << std::endl;
        while(toAdd.size() < mostCompetitors + 1)
        {
            toAdd.append("");
            toAdd2.append("");
            toAdd3.append("");
        }
        //std::cout << "second: " + std::to_string(toAdd.size()) << std::endl;

        toReturn.append(toAdd);
        toReturn.append(toAdd2);
        toReturn.append(toAdd3);
        toAdd.clear();
        toAdd2.clear();
        toAdd3.clear();
    }

    return toReturn;
}

QVector<QVector<QString> > DataTypeConverter::athleteDistributionByCountry(std::map<std::string, int> data)
{
    // Structure:
    // Nationality | Count
    // ...         |   5
    if(data.size() == 0)
    {
        QVector<QVector<QString>> toReturn;
        toReturn.append({"No Results found with these parameters"});
        return toReturn;
    }

    QVector<QVector<QString>> toReturn;
    QVector<QString> toAdd;
    toAdd = {"Nationality", "Count"};
    toReturn.append(toAdd);
    toAdd.clear();

    for(auto i : data)
    {
        toAdd = {QString::fromStdString(i.first),QString::number(i.second)};
        toReturn.append(toAdd);
        toAdd.clear();
    }
    return toReturn;
}

QVector<QVector<QString> > DataTypeConverter::tenBestTeams(std::map<std::string, std::list<Team> > data)
{
    // Structure:
    // Ranking | Team
    //     1.  | Teamname

    if(data.size() == 0)
    {
        QVector<QVector<QString>> toReturn;
        toReturn.append({"No Results found with these parameters"});
        return toReturn;
    }

    QVector<QVector<QString>> toReturn;
    QVector<QString> toAdd;
    toAdd = {"Ranking", "Club Name"};
    toReturn.append(toAdd);
    toAdd.clear();

    int ranking = 1;
    for(auto i : data)
    {
        for(auto j : i.second)
        {
            toAdd.append({ QString::number(ranking) + ".", QString::fromStdString(j.clubName) });
            ranking++;
            toReturn.append(toAdd);
            toAdd.clear();
        }
    }
    return toReturn;
}
