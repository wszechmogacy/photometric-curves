#-------------------------------------------------
#
# Project created by QtCreator 2016-11-10T20:25:04
#
#-------------------------------------------------

QT       += core gui svg printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = photometric-curves-a
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    polar-graph-plot.cpp \
    polar-graph-settingseditor.cpp \
    polar-graph-window.cpp \
    point.cpp

HEADERS  += mainwindow.h \
    polar-graph-pixmaps.h \
    polar-graph-plot.h \
    polar-graph-settingseditor.h \
    polar-graph-window.h \
    point.h

FORMS    += mainwindow.ui \
    polar-graph-window.ui

QWR_PATH = /usr/local/qwt-6.1.2/

LIBS += -L/usr/local/qwt-6.1.2/lib/ -lqwt
INCLUDEPATH += /usr/local/qwt-6.1.2/include
DEPENDPATH += /usr/local/qwt-6.1.2/include

LIBS += -L/usr/local/qwtpolar-1.1.1-svn/lib/ -lqwtpolar
INCLUDEPATH += /usr/local/qwtpolar-1.1.1-svn/include/
DEPENDPATH += /usr/local/qwtpolar-1.1.1-svn/include/

DISTFILES +=
