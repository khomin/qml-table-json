#include "tablemodel.h"
#include <QDebug>

TableModel::TableModel(QObject *parent) {
    roleNameMapping[TableRoles::TableModelRoleKey] = "columnKey";
    roleNameMapping[TableRoles::TableModelRoleValue] = "columnValue";
    roleNameMapping[TableRoles::TableModelRoleIsColorType] = "colorType";
}

void TableModel::loadDataToModel(QVector<std::shared_ptr<ResponseData>> & data) {
    for(auto root: data) {
        auto result = root->getResult();
        for(auto item: result) {
            addItem(item->key, item->value, item->colorType);
        }
    }
}

void TableModel::addItem(QVariant name, QVariant value, ResponseData::ColorType colorType) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    tableItems << std::make_shared<TableItem>(name.toString(), value.toString(), colorType);
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

    TableItem * item = tableItems[index.row()].get();
    if (role == TableRoles::TableModelRoleKey) {
        return item->getKey();
    } else if (role == TableRoles::TableModelRoleValue) {
        return item->getValue();
    } else if (role == TableRoles::TableModelRoleIsColorType) {
        return item->getColorType();
    }
    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const {
    return roleNameMapping;
}
