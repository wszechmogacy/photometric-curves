#ifndef POLARGRAPH_H
#define POLARGRAPH_H

#include <point.h>
#include <QtCharts/QPolarChart>
#include <QObject>
#include <QMainWindow>
#include "ui_polar-graph-window.h"

QT_CHARTS_USE_NAMESPACE

class PolarGraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    PolarGraphWindow(QList<QPointF> &plot_data);
    QPolarChart *graph;
};

#endif // POLARGRAPH_H



