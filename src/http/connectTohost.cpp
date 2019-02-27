#include "connectTohost.h"
#include <QFile>
#include <QDebug>
#include <QAuthenticator>

#ifdef TEST_WITH_FILE
#include <QDir>
#endif

ConnectToHost::ConnectToHost(QString destHostAddr) {
    url = QUrl::fromUserInput(destHostAddr);
}

void ConnectToHost::toConnect() {
#ifdef TEST_WITH_FILE
    qDebug() << QDir::currentPath();
            file = new QFile(QDir::currentPath() +  "/input_response.txt");
            if(file->open(QIODevice::ReadOnly)) {
                qDebug() << "ConnectToHost: sendRequest Ready";
                emit sendRequestReadyResponse(file->readAll());
                file->close();
            }
#else
    if(url.isValid()) {

        connect(&networkAccessManager, &QNetworkAccessManager::sslErrors, this,
                [&](QNetworkReply *reply, const QList<QSslError> &errors) {
            Q_UNUSED(errors);
            Q_UNUSED(reply);
            emit connectError(QString("error type: sslErrors [%1]").arg(reply->errorString()));
        });

        connect(&networkAccessManager, &QNetworkAccessManager::finished, this,
                [&](QNetworkReply* reply) {
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
#endif
}
