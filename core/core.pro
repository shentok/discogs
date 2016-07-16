TEMPLATE = lib
CONFIG += static create_prl
QT += network

INCLUDEPATH += ../../../cajun/src/json/

HEADERS += \
    Artist.h \
    ArtistResult.h \
    Label.h \
    Master.h \
    SearchResult.h \
    Release.h \
    Track.h

SOURCES += \
    Artist.cpp \
    ArtistResult.cpp \
    Label.cpp \
    Master.cpp \
    SearchResult.cpp \
    Release.cpp \
    Track.cpp
