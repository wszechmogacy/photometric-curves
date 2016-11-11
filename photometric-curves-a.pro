#-------------------------------------------------
#
# Project created by QtCreator 2016-11-10T20:25:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = photometric-curves-a
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

QWR_PATH = /usr/local/qwt-6.1.2/

LIBS += -L/usr/local/qwt-6.1.2/lib/ -lqwt
INCLUDEPATH += /usr/local/qwt-6.1.2/include
DEPENDPATH += /usr/local/qwt-6.1.2/include
