QT += quick
QT += charts
QT += qml
QT += network

CONFIG += qml_debug
CONFIG += c++14


SOURCES += \
    app.cpp \
    application.cpp \
    src/responseParcer/responseParcer.cpp \
    src/http/connectTohost.cpp \
    src/model/tablemodel.cpp \
    src/model/tableitem.cpp \
    src/responseParcer/responseData.cpp

TARGET = pg-energo-TEST
TEMPLATE = app

OTHER_FILES +=

HEADERS += \
    application.h \
    src/responseParcer/responseParcer.h \
    src/http/connectTohost.h \
    src/model/tablemodel.h \
    src/model/tableitem.h \
    src/responseParcer/responseData.h

DISTFILES += \
    qml/app.qml

RESOURCES += \
    res.qrc
