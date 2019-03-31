#-------------------------------------------------
#
# Project created by QtCreator 2019-03-31T11:18:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyselfQQ
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    loginwidget.cpp \
    registerwidget.cpp \
    chatwidget.cpp

HEADERS  += mainwidget.h \
    loginwidget.h \
    registerwidget.h \
    chatwidget.h

FORMS    += mainwidget.ui \
    loginwidget.ui \
    registerwidget.ui \
    chatwidget.ui

RESOURCES += \
    image.qrc

CONFIG += C++11
