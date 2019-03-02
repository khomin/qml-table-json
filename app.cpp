#include <QtWidgets/QApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <QQmlContext>
#include "application.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Application application;

    engine.rootContext()->setContextProperty("test_application", &application);

    engine.rootContext()->setContextProperty("tableDataModel", application.getModel());

    engine.load(QUrl(QStringLiteral("qrc:/qml/app.qml")));

    return app.exec();
}
