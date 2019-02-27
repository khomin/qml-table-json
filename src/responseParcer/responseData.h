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

    typedef enum {
        COLOR_TYPE_TRANSPARENT,
        COLOR_TYPE_RED,
        COLOR_TYPE_GREEN
    }ColorType;

    typedef struct {
        QVariant key;
        QVariant value;
        ColorType colorType;
    }sRes;

    int appendValue(QVariant key, QVariant value, ColorType colorType);

    ResponseData::ColorType getValueColorType(int index);

    void updateValueColor(int index, ResponseData::ColorType colorType);

    QVector<std::shared_ptr<ResponseData::sRes>> getResult();

private:
    QVector<std::shared_ptr<sRes>> res;

};

#endif // RESPONSEDATA_H
