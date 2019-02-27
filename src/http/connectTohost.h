#ifndef CONNECTTOHOST_H
#define CONNECTTOHOST_H

#include <QObject>
#include <QByteArray>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#define TEST_WITH_FILE
#ifdef TEST_WITH_FILE
#include <QFile>
#endif

class ConnectToHost : public QObject
{
    Q_OBJECT
public:
    ConnectToHost(QString destIpAddr);

    void startRequest(const QUrl &requestedUrl);
    void toConnect();

signals:
    void connectError(QString erroMessage);
    void sendRequestReadyResponse(QByteArray data);
    void sendRequestError();

private:
    QByteArray responseResult;
    QNetworkAccessManager networkAccessManager;
    QUrl url;

#ifdef TEST_WITH_FILE
    QFile* file;
#endif
};

#endif // CONNECTTOHOST_H
