#-------------------------------------------------
#
# Project created by QtCreator 2016-11-10T20:25:04
#
#-------------------------------------------------
QT += core gui printsupport widgets gui datavisualization charts
TARGET = photometric-curves
TEMPLATE = app


SOURCES += main.cpp\
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
    polar-graph-view.cpp \
    main-window.cpp

HEADERS  += \
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
    polar-graph-view.h \
    main-window.h

FORMS    += mainwindow.ui \
    luminous-flux-window.ui \
    introduction-dialog-window.ui \
    setup-project-dialog-window.ui
