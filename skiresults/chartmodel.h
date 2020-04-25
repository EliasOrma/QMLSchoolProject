#ifndef CHARTMODEL_H
#define CHARTMODEL_H

#include <QStandardItemModel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

class ChartModel : public QStandardItemModel
{
    Q_OBJECT
public:
    ChartModel(QObject*parent = 0);

    Q_INVOKABLE bool addData();

private:
    QNetworkAccessManager _networkManager;
    QNetworkRequest _request;
    QByteArray _networkReplyData;
};

#endif // CHARTMODEL_H
