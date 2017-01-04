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

double PolarGraphWindow::find_max_polar_value(QList<QPointF> &plot_data)
{
    double max_value = 0.0;
    for (auto each : plot_data) {
        if (each.x() > max_value) max_value = each.x();
    }
    return max_value;
}


QValueAxis * PolarGraphWindow::setup_radial_axis(QList<QPointF> &plot_data)
{
    QValueAxis *radialAxis = new QValueAxis();
    radialAxis->setTickCount(9);
    radialAxis->setLabelFormat("%.2f");

    const double radialMin = 0.0;
    const double scale_factor = 1.2;
    const double radialMax = scale_factor * find_max_polar_value(plot_data);
    radialAxis->setRange(radialMin, radialMax);


    return radialAxis;
}

QValueAxis * PolarGraphWindow::setup_angular_axis()
{
    QValueAxis *angularAxis = new QValueAxis();
    angularAxis->setTickCount(19);
    angularAxis->setLabelFormat("%d");
    angularAxis->setShadesVisible(true);
    angularAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));

    const double angularMin = 0.0;
    const double angularMax = 360.0;
    angularAxis->setRange(angularMin, angularMax);

    return angularAxis;
}

void PolarGraphWindow::get_data_series(QScatterSeries *scatter_series, QString name, QList<QPointF> &plot_data)
{
    scatter_series->setName(name);

    for (auto each : plot_data)
    {
        scatter_series->append(each.y(), each.x());
    }
}

PolarGraphWindow::PolarGraphWindow(QList<QPointF> &plot_data)
{
    QScatterSeries *scatter_series = new QScatterSeries();
    get_data_series(scatter_series, "dots", plot_data);

    QPolarChart *chart = new QPolarChart();

    chart->addSeries(scatter_series);

    QValueAxis *angularAxis = setup_angular_axis();
    chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);
    scatter_series->attachAxis(angularAxis);

    QValueAxis *radialAxis = setup_radial_axis(plot_data);
    chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);
    scatter_series->attachAxis(radialAxis);

    ChartView *chartView = new ChartView();
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow *window = new QMainWindow;
    window->setCentralWidget(chartView);
    window->resize(800, 600);
    window->show();
}
