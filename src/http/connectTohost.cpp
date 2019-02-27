#include "connectTohost.h"
#include <QFile>
#include <QDebug>
#include <QAuthenticator>

ConnectToHost::ConnectToHost(QString destHostAddr) {
    url = QUrl::fromUserInput(destHostAddr);
}

void ConnectToHost::toConnect() {
    if(url.isValid()) {

        connect(&networkAccessManager, &QNetworkAccessManager::sslErrors, this,
                [&](QNetworkReply *reply, const QList<QSslError> &errors) {
            Q_UNUSED(errors);
            Q_UNUSED(reply);
            emit connectError(QString("error type: sslErrors [%1]").arg(reply->errorString()));
        });

        connect(&networkAccessManager, &QNetworkAccessManager::finished, this,
                [&](QNetworkReply* reply) {
#ifdef TEST_WITH_FILE
            file = new QFile("D://PROJECTs//TEST//TEST//pg-energo_test//input_response.txt");
            file->open(QIODevice::ReadOnly);
            if(file->isOpen()) {
                file->open(QIODevice::ReadOnly);
                qDebug() << "ConnectToHost: sendRequest Ready";
                emit sendRequestReadyResponse(file->readAll());
                file->close();
            } else {
            }
#else
            if(reply->error() == QNetworkReply::NetworkError::NoError) {
                auto data = reply->readAll();
                if(!data.isEmpty()) {
                    emit sendRequestReadyResponse(data);
                } else {
                    emit connectError("error type: empty response");
                }
            } else {
                emit connectError(QString("error type: empty response [%1]").arg(reply->errorString()));
            }
#endif
        });

        connect(&networkAccessManager, &QNetworkAccessManager::authenticationRequired, this, [&]
                (QNetworkReply *reply, QAuthenticator *authenticator) {
            Q_UNUSED(authenticator);
            Q_UNUSED(reply);
            emit connectError("error type: authenticator");
        });

        QNetworkRequest networkRequest(url);
        networkAccessManager.get(networkRequest);
    } else {
        emit connectError("error type: destination host address");
    }
}
