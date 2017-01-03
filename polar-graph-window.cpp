#include "polar-graph-view.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPolarChart>
#include <QtCore/QDebug>


#include "polar-graph-window.h"

using namespace QtCharts;

PolarGraphWindow::PolarGraphWindow(QList<QPointF> &plot_data)
{

    const qreal angularMin = 0.0;
    const qreal angularMax = 360.0;

    const qreal radialMin = 0.0;
    const qreal radialMax = 1.5;


    QScatterSeries *point_series = new QScatterSeries();
    point_series->setName("scatter");

    for (auto each : plot_data)
    {
        point_series->append(each.y(), each.x());
    }



    QPolarChart *chart = new QPolarChart();

    chart->addSeries(point_series);


    QValueAxis *angularAxis = new QValueAxis();
    angularAxis->setTickCount(19);
    angularAxis->setLabelFormat("%d");
    angularAxis->setShadesVisible(true);
    angularAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));
    chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);


    QValueAxis *radialAxis = new QValueAxis();
    radialAxis->setTickCount(9);
    radialAxis->setLabelFormat("%.2f");
    chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);


    point_series->attachAxis(radialAxis);
    point_series->attachAxis(angularAxis);

    radialAxis->setRange(radialMin, radialMax);
    angularAxis->setRange(angularMin, angularMax);

    ChartView *chartView = new ChartView();
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow *window = new QMainWindow;
    window->setCentralWidget(chartView);
    window->resize(800, 600);
    window->show();
}
