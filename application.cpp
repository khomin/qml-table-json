#include "application.h"
#include <QTimer>
#include <QtDebug>

Application::Application(QObject *parent) : QObject(parent) {
    this->tableModel = std::make_shared<TableModel>();

    this->connectToHost = std::make_shared<ConnectToHost>("jsonplaceholder.typecode.com");

    this->responseParcer = std::make_shared<ResponseParcer>();

    connect(connectToHost.get(), &ConnectToHost::connectError, this, &Application::connectToHostError);

    connect(connectToHost.get(), &ConnectToHost::sendRequestReadyResponse, this, [&](QByteArray data) {
        responseParcer->startParce(data);

        if(responseParcer->getStatus() == ResponseParcer::Status::Status_Ok) {

            qDebug() << "Responce parcer: status Ok";

            tableModel->loadDataToModel(responseParcer->getResult());
        } else {
            qDebug() << "Responce parcer: status Error";
            emit parceResponceError();
        }
    });

    connect(connectToHost.get(), &ConnectToHost::sendRequestError, this, &Application::connectSendRequestError);

    QTimer::singleShot(500, Qt::CoarseTimer, this, [&] {
        connectToHost->toConnect();
    });
}

TableModel* Application::getModel() {
    return tableModel.get();
}
