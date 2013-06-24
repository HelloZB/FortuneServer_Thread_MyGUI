#-------------------------------------------------
#
# Project created by QtCreator 2013-05-13T19:58:27
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server_threded
TEMPLATE = app


SOURCES += main.cpp\
        mygui_threded_server.cpp \
    myfortuneserver.cpp \
    myfortunethread.cpp

HEADERS  += mygui_threded_server.h \
    myfortuneserver.h \
    myfortunethread.h

FORMS    += mygui_threded_server.ui
