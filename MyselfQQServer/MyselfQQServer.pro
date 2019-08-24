#-------------------------------------------------
#
# Project created by QtCreator 2019-04-23T16:20:38
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyselfQQServer
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    getinfo.cpp \
    dealloginmsg.cpp \
    dealallmsg.cpp \
    resource.cpp

HEADERS  += widget.h \
    getinfo.h \
    dealloginmsg.h \
    dealallmsg.h \
    resource.h

FORMS    += widget.ui

CONFIG += C++11
