#include "responseData.h"

ResponseData::ResponseData(QObject *parent) : QObject(parent) {}

int ResponseData::appendValue(QVariant key, QVariant value, ColorType colorType) {
    auto i = std::make_shared<sRes>();
    i->key = key;
    i->value = value;
    i->colorType = colorType;
    res.push_back(std::move(i));
    return res.count() - 1;
}

ResponseData::ColorType ResponseData::getValueColorType(int index) {
    ResponseData::ColorType colorType = ResponseData::COLOR_TYPE_TRANSPARENT;
    if(res.count() >= index) {
        colorType = (*(res.begin() + index))->colorType;
    }
    return colorType;
}

void ResponseData::updateValueColor(int index, ResponseData::ColorType colorType) {
    if(res.count() >= index) {
        (*(res.begin() + index))->colorType = colorType;
    }
}

QVector<std::shared_ptr<ResponseData::sRes>> ResponseData::getResult() {
    return res;
}
