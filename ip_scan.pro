#-------------------------------------------------
#
# Project created by QtCreator 2013-12-07T21:09:51
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ip_scan
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    shellprocess.cpp

HEADERS  += mainwindow.h \
    shellprocess.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    application.qrc
