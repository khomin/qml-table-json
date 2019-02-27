#ifndef TABLEITEM_H
#define TABLEITEM_H

#include <QObject>
#include <QVector>
#include <QPair>
#include "src/responseParcer/responseData.h"

class TableItem : public QObject
{
    Q_OBJECT
public:
    explicit TableItem(QString key, QString value, ResponseData::ColorType colorType) {
        this->key = key;
        this->value = value;
        this->colorType = colorType;
    }
    QString getKey() { return key; }
    QString getValue() { return value; }
    ResponseData::ColorType getColorType() {return colorType; }
private:
    QString key;
    QString value;
    ResponseData::ColorType colorType;
};

#endif // TABLEITEM_H
