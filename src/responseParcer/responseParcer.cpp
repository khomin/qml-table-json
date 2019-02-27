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
    auto i = data.indexOf("\r\n\r\n");
    if(i > 0) {
        try {
            QByteArray d = QByteArray(data.data() + i + strlen("\r\n\r\n"));
            QJsonDocument document = QJsonDocument::fromJson(d);

            QJsonArray rootArray = document.array();

            for(auto arrayItem: rootArray) {
                std::shared_ptr<ResponseData> tres = std::make_shared<ResponseData>();

                auto obj = arrayItem.toObject();

                // --- id должен менять цвет ---//
                int id = obj.value("id").toInt();
                auto idColor = ResponseData::COLOR_TYPE_TRANSPARENT;

                tres->addValue("name", obj.value("name").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);
                tres->addValue("username", obj.value("username").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);
                tres->addValue("email", obj.value("email").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);

                auto addrArray = obj.value("address").toObject();
                tres->addValue("street", addrArray.value("street").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);
                tres->addValue("suite", addrArray.value("suite").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);
                tres->addValue("city", addrArray.value("city").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);

                auto geo = addrArray.value("geo").toObject();

                //--- geo должны менять цвет ---//
                tres->addValue("lat", geo.value("lat").toString(), QString(geo.value("lat").toString()).toDouble() >= 0 ? ResponseData::COLOR_TYPE_GREEN : ResponseData::COLOR_TYPE_RED);
                tres->addValue("lng", geo.value("lng").toString(), QString(geo.value("lng").toString()).toDouble() >= 0 ? ResponseData::COLOR_TYPE_GREEN : ResponseData::COLOR_TYPE_RED);

                // --- в конце можно понять каким цветом id ---//
                idColor = QString(geo.value("lat").toString()).toDouble() >= 0 ? ResponseData::COLOR_TYPE_GREEN : ResponseData::COLOR_TYPE_RED;

                tres->addValue("phone", obj.value("phone").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);
                tres->addValue("website", obj.value("website").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);

                auto company = obj.value("company").toObject();
                tres->addValue("nameCompany", company.value("name").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);
                tres->addValue("catchPhrase", company.value("catchPhrase").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);
                tres->addValue("bs", company.value("bs").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);
                tres->addValue("website", obj.value("website").toString(), ResponseData::COLOR_TYPE_TRANSPARENT);

                // --- в конце можно понять каким цветом id ---//
                tres->addValue("id", id, idColor);

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
