#-------------------------------------------------
#
# Project created by QtCreator 2017-09-29T08:12:52
#
#-------------------------------------------------

QT       -= gui

QMAKE_CXXFLAGS += -std=c++11

TARGET = DNRLogger
TEMPLATE = lib

CONFIG += staticlib

SOURCES += dnrlogger.cpp

HEADERS += dnrlogger.h
unix {
    target.path = /usr/local/lib
    INSTALLS += target
}

unix {
    headers.path = /usr/local/include
    headers.files = *.h
    INSTALLS += headers
}

