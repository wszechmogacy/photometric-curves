#ifndef POLARGRAPH_H
#define POLARGRAPH_H

#include <QList>
#include <QMainWindow>
#include <QObject>
#include <QPointF>
#include <QScatterSeries>
#include <QString>
#include <QtCharts/QPolarChart>
#include <QValueAxis>

#include <point.h>

QT_CHARTS_USE_NAMESPACE

enum class GraphType
{
    section,
    curve
};

class PolarGraphWindow : public QMainWindow
{
    Q_OBJECT

    double find_max_polar_value(QList<QPointF> &plot_data);
    
    void setup_radial_axis(QScatterSeries *point_series, QList<QPointF> &plot_data, QPolarChart *chart);

    QValueAxis * setup_angular_axis();

    void get_data_series(QXYSeries *scatter_series, QString name, QList<QPointF> &plot_data);

public:
    PolarGraphWindow(const QString &graph_name, GraphType graph_type_,  QList<QPointF> &plot_data);
    QPolarChart *graph_;
    QValueAxis *setup_radial_axis(QList<QPointF> &plot_data);
private:
    GraphType graph_type_;
    QString graph_name_;
};

#endif // POLARGRAPH_H
