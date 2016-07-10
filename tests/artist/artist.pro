TEMPLATE = app

QT += testlib
CONFIG += testcase link_prl

INCLUDEPATH += ../../core
LIBS *= -L../../core -lcore
DEPENDPATH += ../../core

SOURCES += main.cpp

RESOURCES += \
    json.qrc
