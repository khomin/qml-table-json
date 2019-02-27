#include "responseData.h"

ResponseData::ResponseData(QObject *parent) : QObject(parent)
{

}

void ResponseData::addValue(QVariant key, QVariant value, QVariant isCoordinate) {
    auto i = std::make_shared<sRes>();
    i->key = key;
    i->value = value;
    i->isCoordinate = isCoordinate;
    res.push_back(std::move(i));
}

QVector<std::shared_ptr<ResponseData::sRes>> ResponseData::getResult() {
    return res;
}
