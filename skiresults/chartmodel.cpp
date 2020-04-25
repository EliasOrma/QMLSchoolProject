#include "chartmodel.h"

ChartModel::ChartModel(QObject *parent) : QStandardItemModel(parent)
{

}

bool ChartModel::addData()
{
    setColumnCount(2);
    setRowCount(100);
    for (int row = 0; row < rowCount(); row++)
    {
        QStandardItem *item1 = new QStandardItem(QString::number(row));
        QStandardItem *item2 = new QStandardItem(QString::number(row*row));
        setItem(row, 0, item1);
        setItem(row, 1, item2);
    }

    return true;
}
