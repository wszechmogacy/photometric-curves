#-------------------------------------------------
#
# Project created by QtCreator 2016-11-10T20:25:04
#
#-------------------------------------------------

QT       += core gui svg printsupport datavisualization charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = photometric-curves-a
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    polar-graph-plot.cpp \
    polar-graph-window.cpp \
    point.cpp \
    luminous-flux-calculator.cpp \
    luminous-flux-window.cpp \
    introduction-dialog-window.cpp \
    setup-project-dialog-window.cpp \
    surface-window.cpp \
    surface-graph.cpp \
    project-settings.cpp \
    polar-graph.cpp \
    chartview.cpp

HEADERS  += mainwindow.h \
    polar-graph-plot.h \
    polar-graph-window.h \
    point.h \
    luminous-flux-calculator.h \
    luminous-flux-window.h \
    introduction-dialog-window.h \
    setup-project-dialog-window.h \
    surface-window.h \
    surface-graph.h \
    project-settings.h \
    polar-graph.h \
    chartview.h

FORMS    += mainwindow.ui \
    polar-graph-window.ui \
    luminous-flux-window.ui \
    introduction-dialog-window.ui \
    setup-project-dialog-window.ui

QWR_PATH = /usr/local/qwt-6.1.2/

LIBS += -L/usr/local/qwt-6.1.2/lib/ -lqwt
INCLUDEPATH += /usr/local/qwt-6.1.2/include
DEPENDPATH += /usr/local/qwt-6.1.2/include

LIBS += -L/usr/local/qwtpolar-1.1.1-svn/lib/ -lqwtpolar
INCLUDEPATH += /usr/local/qwtpolar-1.1.1-svn/include/
DEPENDPATH += /usr/local/qwtpolar-1.1.1-svn/include/

DISTFILES +=
