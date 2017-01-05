#include <QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPolarChart>
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include <polar-graph-view.h>
#include <polar-graph-window.h>


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
    radialAxis->setTickCount(11);
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
    const unsigned step = 15;
    angularAxis->setTickCount(360 / step + 1);
    angularAxis->setLabelFormat("%d");
    angularAxis->setShadesVisible(true);
    angularAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));

    const double angularMin = 0.0;
    const double angularMax = 360.0;
    angularAxis->setRange(angularMin, angularMax);

    return angularAxis;
}

void PolarGraphWindow::get_data_series(QXYSeries *scatter_series, QString name, QList<QPointF> &plot_data)
{
    scatter_series->setName(name);

    for (auto each : plot_data)
    {
        scatter_series->append(each.y(), each.x());
    }
}

PolarGraphWindow::PolarGraphWindow(GraphType graph_type, QList<QPointF> &plot_data) :
    graph_type(graph_type)
{
    QScatterSeries *scatter_series = new QScatterSeries();
    QLineSeries *line_series = new QLineSeries();
    get_data_series(scatter_series, "dots", plot_data);
    get_data_series(line_series, "curve", plot_data);

    QPolarChart *chart = new QPolarChart();

    chart->addSeries(scatter_series);
    chart->addSeries(line_series);

    QValueAxis *angularAxis = setup_angular_axis();
    chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);
    scatter_series->attachAxis(angularAxis);
    line_series->attachAxis(angularAxis);

    QValueAxis *radialAxis = setup_radial_axis(plot_data);
    chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);
    scatter_series->attachAxis(radialAxis);
    line_series->attachAxis(radialAxis);

    if (graph_type == GraphType::curve) {
        chart->scroll(-180.0, 0);
    }

    ChartView *chartView = new ChartView();
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    this->setCentralWidget(chartView);
    this->resize(800, 600);
}
