#include <QDebug>
#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>
#include <QtDataVisualization/Q3DTheme>
#include <QtDataVisualization/QValue3DAxis>
#include <QtGui/QImage>
#include <QtCore/qmath.h>
#include <string>
#include <utility>
#include <vector>

#include <surface-graph.h>


using namespace QtDataVisualization;

SurfaceGraph::SurfaceGraph(Q3DSurface *surface, std::vector<Point> data, unsigned columns_count, unsigned rows_count)
    : sample_count_on_meridian_(columns_count + 1),
    sample_count_on_parallel_(rows_count),
    data_table_(data),
    graph_(surface),
    x_rotation_(0.0f),
    y_rotation_(0.0f)
{
    graph_->setAxisX(new QValue3DAxis);
    graph_->setAxisY(new QValue3DAxis);
    graph_->setAxisZ(new QValue3DAxis);

    photo_layer_proxy_ = new QSurfaceDataProxy();
    photo_layer_series_ = new QSurface3DSeries(photo_layer_proxy_);

    set_data(data_table_);

    graph_->activeTheme()->setType(Q3DTheme::ThemeQt);
    set_graph_details();
}

void SurfaceGraph::convert_point_on_meridian(std::vector<Point> data, unsigned i, int &index, QSurfaceDataRow *newRow, unsigned j)
{
    size_t pos = i * sample_count_on_meridian_ + j;
    (*newRow)[index].setPosition(QVector3D(data[pos].x_, data[pos].y_, data[pos].z_));
    qDebug() << QString::number(pos) << ": "
             << QString::number(index)
             << QString::number(data[pos].lat_angle_deg_, 'g', 8)
             << QString::number(data[pos].lon_angle_deg_, 'g', 8)
             << QString::number(data[pos].z_, 'g', 8);
    index++;
}

void SurfaceGraph::set_data(std::vector<Point> &data_table)
{
    std::vector<Point> data(data_table);
    auto sampleCountAll = data.size();
    std::sort(data.begin(), data.end());

    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(sampleCountAll);
    for (unsigned i = 0; i < sample_count_on_parallel_; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(sample_count_on_parallel_);
        int index = 0;
        for (unsigned j = 0; j < sample_count_on_meridian_; j++) {
            convert_point_on_meridian(data, i, index, newRow, j);
        }
        *dataArray << newRow;
    }
    //workaround to close the surface (add 0 parallel at the end of curve
    QSurfaceDataRow *newRow = new QSurfaceDataRow(sample_count_on_parallel_);
    int index = 0;
    for (unsigned j = 0; j < sample_count_on_meridian_; j++) {
        convert_point_on_meridian(data, 0, index, newRow, j);
    }
    *dataArray << newRow;

    photo_layer_proxy_->resetArray(dataArray);

}

SurfaceGraph::~SurfaceGraph()
{
    delete graph_;
}


void SurfaceGraph::set_range_x()
{
    const double scale_factor = 1.2;
    auto range = std::minmax_element(data_table_.begin(), data_table_.end(),
          [](const Point &px, const Point &py){
              return px.x_ < py.x_;
          }
    );
    graph_->axisX()->setRange(scale_factor * range.first->x_, scale_factor * range.second->x_);
}


void SurfaceGraph::set_range_y()
{
    const double scale_factor = 1.2;
    auto range = std::minmax_element(data_table_.begin(), data_table_.end(),
          [](const Point &px, const Point &py){
              return px.y_ < py.y_;
          }
    );
    graph_->axisY()->setRange(scale_factor * range.first->y_, scale_factor * range.second->y_);
}


void SurfaceGraph::set_range_z()
{
    const double scale_factor = 1.2;
    auto range = std::minmax_element(data_table_.begin(), data_table_.end(),
          [](const Point &px, const Point &py){
              return px.z_ < py.z_;
          }
    );
    graph_->axisZ()->setRange(scale_factor * range.first->z_, scale_factor * range.second->z_);
}


void SurfaceGraph::set_graph_details()
{
    set_range_x();
    set_range_y();
    set_range_z();

    photo_layer_series_->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
    photo_layer_series_->setFlatShadingEnabled(true);

    graph_->axisX()->setLabelFormat("%.2f");
    graph_->axisZ()->setLabelFormat("%.2f");

    graph_->axisX()->setLabelAutoRotation(30);
    graph_->axisY()->setLabelAutoRotation(90);
    graph_->axisZ()->setLabelAutoRotation(30);

    graph_->addSeries(photo_layer_series_);
}


void SurfaceGraph::rotate_x(int rotation)
{
    x_rotation_ = rotation;
    graph_->scene()->activeCamera()->setCameraPosition(x_rotation_, y_rotation_);
}
void SurfaceGraph::rotate_y(int rotation)
{
    y_rotation_ = rotation;
    graph_->scene()->activeCamera()->setCameraPosition(x_rotation_, y_rotation_);
}


