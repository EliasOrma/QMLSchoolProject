#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <QObject>
#include <QVariant>
#include <exception>
#include <algorithm>
#include <QStringListModel>

#include <datahandler.h>
#include <timet.h>
#include <tablemodel.h>
#include <datatypeconverter.h>

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(TableModel *tbmodel, QStringListModel *rctagModel, QObject *parent = nullptr);
    std::vector<QString> getEveryYear();
    Q_INVOKABLE void search(QString state, QString year1, QString year2,
                            QString starttime, QString endtime, QString racetag1,
                            QString racetag2, QString athletename, QString sizeofranking,
                            QString gender);

    Q_INVOKABLE void setNewRaceTags(int searchType, QString year1, QString year2);

private:
    DataHandler dataHandler;
    DataTypeConverter dataconverter;

    QStringListModel *racetagModel;
    TableModel *tableModel;

    TimeT convertToTimeT(QString str);
    void logError(std::string msg);

    void callShowResultsInQML(int tableType);
    void callInitYearsInQML();

signals:
    void showResults(int tableType);
    void initYears();

};

#endif // CONTROLLER_H
