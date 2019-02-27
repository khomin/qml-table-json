#ifndef TABLEITEM_H
#define TABLEITEM_H

#include <QObject>
#include <QVector>
#include <QPair>

class TableItem : public QObject
{
    Q_OBJECT
public:
    explicit TableItem(QString key, QString value, bool isCoordinate) {
        this->key = key;
        this->value = value;
        this->isCoordinate = isCoordinate;
    }
    QString getKey() { return key; }
    QString getValue() { return value; }
    bool getIsCoordinate() {return isCoordinate; }
private:
    QString key;
    QString value;
    bool isCoordinate;
};

#endif // TABLEITEM_H
