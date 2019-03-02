#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>
#include <QHash>
#include <QAbstractTableModel>
#include <src/model/tableitem.h>
#include "src/responseParcer/responseData.h"
#include <memory>
#include <QVariant>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = nullptr);

    enum TableRoles {
        TableModelRoleKey = Qt::UserRole + 1,
        TableModelRoleValue,
        TableModelRoleIsColorType
    };

    void loadDataToModel(QVector<std::shared_ptr<ResponseData>> & data);

    void addItem(QVariant name, QVariant value, ResponseData::ColorType colorType);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    int columnCount(const QModelIndex & = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<std::shared_ptr<TableItem>> tableItems;
    QHash<int, QByteArray> roleNameMapping;
};

#endif // TABLEMODEL_H
