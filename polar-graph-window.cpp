#include <QCheckBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLineSeries>
#include <QPushButton>
#include <QRadioButton>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPolarChart>
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QSlider>
#include <QWidget>

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


PolarGraphWindow::PolarGraphWindow(const QString &graph_name, GraphType graph_type, QString units_name, QList<QPointF> &plot_data) :
    graph_type_(graph_type),
    graph_name_(graph_name)
{
    if (graph_type == GraphType::curve) {
        this->setWindowTitle(tr("Photometric curve"));
    } else if (graph_type == GraphType::section) {
        this->setWindowTitle(tr("Photometric section"));
    } else {
        this->setWindowTitle(tr("Photometric graph"));
    }

    QScatterSeries *scatter_series = new QScatterSeries();
    QLineSeries *line_series = new QLineSeries();
    QSplineSeries *spline_series = new QSplineSeries();
    get_data_series(scatter_series, tr("dots"), plot_data);
    get_data_series(line_series, tr("curve"), plot_data);
    get_data_series(spline_series, tr("spline"), plot_data);

    QPolarChart *chart = new QPolarChart();

    chart->addSeries(scatter_series);
    chart->addSeries(line_series);
    chart->addSeries(spline_series);
    chart->setTitle(graph_name);

    QValueAxis *angularAxis = setup_angular_axis();
    angularAxis->setTitleText(units_name);
    angularAxis->setTitleVisible();
    chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);
    scatter_series->attachAxis(angularAxis);
    line_series->attachAxis(angularAxis);
    spline_series->attachAxis(angularAxis);

    QValueAxis *radialAxis = setup_radial_axis(plot_data);
    chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);
    scatter_series->attachAxis(radialAxis);
    line_series->attachAxis(radialAxis);
    spline_series->attachAxis(radialAxis);

    scatter_series->hide();
    line_series->hide();
    spline_series->show();

    if (graph_type == GraphType::curve) {
        chart->scroll(-180.0, 0);
    }

    ChartView *chartView = new ChartView();
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QWidget *widget = new QWidget();
    QHBoxLayout *hlayout = new QHBoxLayout;

    QGroupBox *styleSelectionGroupBox = new QGroupBox(tr("Graph curve type"));
    QVBoxLayout *selectionVBox = new QVBoxLayout;

    QCheckBox *splineCheckBox = new QCheckBox(tr("smooth line"));
    QCheckBox *lineCheckBox = new QCheckBox(tr("line"));
    QCheckBox *scatterCheckBox = new QCheckBox(tr("scatter"));

    splineCheckBox->setCheckState(Qt::Checked);
    lineCheckBox->setCheckState(Qt::Unchecked);
    scatterCheckBox->setCheckState(Qt::Unchecked);

    spline_series->show();
    scatter_series->hide();
    line_series->hide();

    QObject::connect(splineCheckBox,&QCheckBox::stateChanged, [spline_series](){
        if (spline_series->isVisible()) spline_series->hide();
        else spline_series->show();
    });
    QObject::connect(lineCheckBox,&QCheckBox::stateChanged, [line_series](){
        if (line_series->isVisible()) line_series->hide();
        else line_series->show();
    });
    QObject::connect(scatterCheckBox,&QCheckBox::stateChanged, [scatter_series](){
        if (scatter_series->isVisible()) scatter_series->hide();
        else scatter_series->show();
    });

    selectionVBox->addWidget(splineCheckBox);
    selectionVBox->addWidget(lineCheckBox);
    selectionVBox->addWidget(scatterCheckBox);
    selectionVBox->setAlignment(Qt::AlignTop);
    styleSelectionGroupBox->setLayout(selectionVBox);

    QPushButton *printToPdfButton = new QPushButton(tr("Export to PDF"));

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addWidget(printToPdfButton);
    vlayout->addWidget(styleSelectionGroupBox);

    hlayout->addWidget(chartView);
    hlayout->addLayout(vlayout);

    widget->setLayout(hlayout);
    setCentralWidget(widget);

    this->resize(800, 600);
}
