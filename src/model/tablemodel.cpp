#include "tablemodel.h"
#include <QDebug>

TableModel::TableModel(QObject *parent) {
    roleNameMapping[TableRoles::TableModelRoleKey] = "columnKey";
    roleNameMapping[TableRoles::TableModelRoleValue] = "columnValue";
    roleNameMapping[TableRoles::TableModelRoleIsCoordinate] = "isCoordinate";
}

void TableModel::loadDataToModel(QVector<std::shared_ptr<ResponseData>> & data) {
    for(auto root: data) {
        auto result = root->getResult();
        for(auto item: result) {
            addItem(item->key, item->value, item->isCoordinate);
        }
    }
}

void TableModel::addItem(QVariant name, QVariant value, QVariant isCoordinate) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    tableItems << new TableItem(name.toString(), value.toString(), isCoordinate.toBool());
    endInsertRows();
}

int TableModel::rowCount(const QModelIndex & index) const {
    Q_UNUSED(index);
    return tableItems.count();
}

int TableModel::columnCount(const QModelIndex & index) const {
    Q_UNUSED(index);
    return 2;
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= tableItems.count())
        return QVariant();

    TableItem * item = tableItems[index.row()];
    if (role == TableRoles::TableModelRoleKey) {
        return item->getKey();
    } else if (role == TableRoles::TableModelRoleValue) {
        return item->getValue();
    } else if (role == TableRoles::TableModelRoleIsCoordinate) {
        return item->getIsCoordinate();
    }
    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const {
    return roleNameMapping;
}
