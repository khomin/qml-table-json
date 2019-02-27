#include "application.h"
#include <QTimer>
#include <QtDebug>

Application::Application(QObject *parent) : QObject(parent) {
    this->tableModel = new TableModel();

    this->connectToHost = new ConnectToHost("jsonplaceholder.typecode.com");

    this->responseParcer = new ResponseParcer();

    connect(connectToHost, &ConnectToHost::connectError, this, &Application::connectToHostError);

    connect(connectToHost, &ConnectToHost::sendRequestReadyResponse, this, [&](QByteArray data) {
        responseParcer->startParce(data);

        if(responseParcer->getStatus() == ResponseParcer::Status::Status_Ok) {

            qDebug() << "Responce parcer: status Ok";

            tableModel->loadDataToModel(responseParcer->getResult());
        } else {
            qDebug() << "Responce parcer: status Error";
            emit parceResponceError();
        }
    });

    connect(connectToHost, &ConnectToHost::sendRequestError, this, &Application::connectSendRequestError);

    QTimer::singleShot(500, Qt::CoarseTimer, this, [&] {
        connectToHost->toConnect();
    });
}

TableModel* Application::getModel() {
    return tableModel;
}
