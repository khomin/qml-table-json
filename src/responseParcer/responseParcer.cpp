#include "responseParcer.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QtDebug>

ResponseParcer::ResponseParcer() {
    parceStatus = Status::Status_EMPTY;
}

ResponseParcer::ResponseParcer(QByteArray data) {
    parceStatus = Status::Status_EMPTY;
    startParce(data);
}

ResponseParcer::~ResponseParcer() {

}

void ResponseParcer::startParce(QByteArray data) {
    auto i = data.indexOf("\n\n");
    if(i > 0) {
        try {
            QByteArray d = QByteArray(data.data() + i + strlen("\n\n"));
            QJsonDocument document = QJsonDocument::fromJson(d);

            QJsonArray rootArray = document.array();

            for(auto arrayItem: rootArray) {
                std::shared_ptr<ResponseData> tres = std::make_shared<ResponseData>();

                auto obj = arrayItem.toObject();

                tres->appendValue("id", obj.value("id").toInt(), ResponseData::COLOR_TYPE_TRANSPARENT);

                // --- name должен менять цвет ---//
                int nameIndex = tres->appendValue("name", obj.value("name").toString(),
                        ResponseData::COLOR_TYPE_TRANSPARENT);
                tres->appendValue("username", obj.value("username").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);
                tres->appendValue("email", obj.value("email").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);

                auto addrArray = obj.value("address").toObject();
                tres->appendValue("street", addrArray.value("street").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);
                tres->appendValue("suite", addrArray.value("suite").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);
                tres->appendValue("city", addrArray.value("city").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);

                auto geo = addrArray.value("geo").toObject();

                //--- geo lat должен менять цвет ---//
                auto latIndex = tres->appendValue("lat", geo.value("lat").toString(),
                               QString(geo.value("lat").toString()).toDouble() >= 0 ? ResponseData::COLOR_TYPE_GREEN : ResponseData::COLOR_TYPE_RED);
                tres->appendValue("lng", geo.value("lng").toString(),
                               QString(geo.value("lng").toString()).toDouble() >= 0 ? ResponseData::COLOR_TYPE_GREEN : ResponseData::COLOR_TYPE_RED);

                tres->appendValue("phone", obj.value("phone").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);
                tres->appendValue("website", obj.value("website").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);

                auto company = obj.value("company").toObject();
                tres->appendValue("nameCompany", company.value("name").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);
                tres->appendValue("catchPhrase", company.value("catchPhrase").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);
                tres->appendValue("bs", company.value("bs").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);
                tres->appendValue("website", obj.value("website").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);

                // --- в конце можно понять каким цветом name ---//
                auto nameColor = tres->getValueColorType(latIndex);

                // --- теперь делаем цвет name таким как latidute ---//
                tres->updateValueColor(nameIndex, nameColor);

                parceData.push_back(std::move(tres));
            }
        } catch(...) {
            qDebug() << "ResponseParcer: parce Exception";
            parceStatus = Status::Status_Error;
            return;
        }
        parceStatus = Status::Status_Ok;
    } else {
        parceStatus = Status::Status_Error;
    }
}

ResponseParcer::Status ResponseParcer::getStatus() {
    return parceStatus;
}

QVector<std::shared_ptr<ResponseData>>& ResponseParcer::getResult() const {
    return parceData;
}
