#ifndef POLARGRAPH_H
#define POLARGRAPH_H

#include <point.h>
#include <QtCharts/QPolarChart>
#include <QObject>
#include <QMainWindow>
#include <QScatterSeries>
#include <QList>
#include <QPointF>
#include "ui_polar-graph-window.h"
#include <QValueAxis>

QT_CHARTS_USE_NAMESPACE

class PolarGraphWindow : public QMainWindow
{
    Q_OBJECT

    double find_max_polar_value(QList<QPointF> &plot_data);
    
    void setup_radial_axis(QScatterSeries *point_series, QList<QPointF> &plot_data, QPolarChart *chart);

    QValueAxis * setup_angular_axis();

    void get_data_series(QXYSeries *scatter_series, QString name, QList<QPointF> &plot_data);

public:
    PolarGraphWindow(QList<QPointF> &plot_data);
    QPolarChart *graph;
    QValueAxis * setup_radial_axis(QList<QPointF> &plot_data);
};

#endif // POLARGRAPH_H



