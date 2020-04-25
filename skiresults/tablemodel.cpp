#include "tablemodel.h"
#include "iostream"
TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent)
{
    // Header
    table.append({"1","2","3"});
}

int TableModel::rowCount(const QModelIndex &) const
{
    return table.size();
}

int TableModel::columnCount(const QModelIndex &) const
{
    return table.at(0).size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case TableDataRole:
    {
        return table.at(index.row()).at(index.column());
    }
    case HeadingRole:
    {
        if(index.row()==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TableDataRole] = "tabledata";
    roles[HeadingRole] = "heading";
    return roles;
}

void TableModel::changeData(QVector<QVector<QString>> inputtable)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    table.clear();
    table = inputtable;
    endInsertRows();
}
