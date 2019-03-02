#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include "src/model/tablemodel.h"
#include <src/http/connectTohost.h>
#include <src/responseParcer/responseParcer.h>
#include <memory>

class Application : public QObject
{
    Q_OBJECT
public:
    Application(QObject *parent = nullptr);

    Q_INVOKABLE TableModel* getModel();

signals:
    void connectToHostOk();
    void connectToHostError(QString errorMessage);
    void connectSendRequestError();
    void parceResponceError();

private:

    std::shared_ptr<ConnectToHost> connectToHost;
    std::shared_ptr<ResponseParcer> responseParcer;
    std::shared_ptr<TableModel> tableModel;
};

#endif // APPLICATION_H
