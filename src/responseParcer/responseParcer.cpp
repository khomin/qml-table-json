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

                tres->addValue("id", obj.value("id").toInt(), false);
                tres->addValue("name", obj.value("name").toString(), false);
                tres->addValue("username", obj.value("username").toString(), false);
                tres->addValue("email", obj.value("email").toString(), false);

                auto addrArray = obj.value("address").toObject();
                tres->addValue("street", addrArray.value("street").toString(), false);
                tres->addValue("suite", addrArray.value("suite").toString(), false);
                tres->addValue("city", addrArray.value("city").toString(), false);

                auto geo = addrArray.value("geo").toObject();
                tres->addValue("lat", geo.value("lat").toString(), true);
                tres->addValue("lng", geo.value("lng").toString(), true);

                tres->addValue("phone", obj.value("phone").toString(), false);
                tres->addValue("website", obj.value("website").toString(), false);

                auto company = obj.value("company").toObject();
                tres->addValue("nameCompany", company.value("name").toString(), false);
                tres->addValue("catchPhrase", company.value("catchPhrase").toString(), false);
                tres->addValue("bs", company.value("bs").toString(), false);
                tres->addValue("website", obj.value("website").toString(), false);

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
