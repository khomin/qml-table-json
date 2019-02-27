#ifndef RESPONSEDATA_H
#define RESPONSEDATA_H

#include <QObject>
#include <QVariant>
#include <QVector>
#include <QPair>
#include <memory>

class ResponseData : public QObject
{
    Q_OBJECT
public:
    explicit ResponseData(QObject *parent = nullptr);

    void addValue(QVariant key, QVariant value, QVariant isCoordinate);

    typedef struct {
        QVariant key;
        QVariant value;
        QVariant isCoordinate;
    }sRes;

    QVector<std::shared_ptr<ResponseData::sRes>> getResult();

private:
    QVector<std::shared_ptr<sRes>> res;

};

#endif // RESPONSEDATA_H
