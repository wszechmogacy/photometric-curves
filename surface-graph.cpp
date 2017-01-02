#include "surface-graph.h"

#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/Q3DTheme>
#include <QtGui/QImage>
#include <QtCore/qmath.h>
#include <utility>
#include <vector>
#include <string>

#include <QDebug>

using namespace QtDataVisualization;


SurfaceGraph::SurfaceGraph(Q3DSurface *surface, std::vector<Point> data, unsigned columns_count, unsigned rows_count)
    : m_graph(surface),
    data_table(data),
    sampleCountOnMeridian(columns_count + 1),
    sampleCountOnParallel(rows_count + 1),
    m_xRotation(0.0f),
    m_yRotation(0.0f)
{
    m_graph->setAxisX(new QValue3DAxis);
    m_graph->setAxisY(new QValue3DAxis);
    m_graph->setAxisZ(new QValue3DAxis);

    m_PhotoLayerProxy = new QSurfaceDataProxy();
    m_PhotoLayerSeries = new QSurface3DSeries(m_PhotoLayerProxy);

    set_data(data_table);

    m_graph->activeTheme()->setType(Q3DTheme::ThemeQt);
    set_graph_details();
}

void SurfaceGraph::set_data(std::vector<Point> &data_table)
{
    std::vector<Point> data(data_table);
    auto sampleCountAll = data.size();
    std::sort(data.begin(), data.end());

    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(sampleCountAll);
    for (unsigned i = 0; i < sampleCountOnParallel; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(sampleCountOnParallel);
        int index = 0;
        for (unsigned j = 0; j < sampleCountOnMeridian; j++) {
            size_t pos = i * sampleCountOnMeridian + j;
            (*newRow)[index].setPosition(QVector3D(data[pos].x, data[pos].y, data[pos].z));
            qDebug() << QString::number(pos) << ": "
                     << QString::number(index)
                     << QString::number(data[pos].lat_angle_deg, 'g', 8)
                     << QString::number(data[pos].lon_angle_deg, 'g', 8)
                     << QString::number(data[pos].z, 'g', 8);
            index++;
        }
        *dataArray << newRow;
    }

    m_PhotoLayerProxy->resetArray(dataArray);

}

SurfaceGraph::~SurfaceGraph()
{
    delete m_graph;
}


void SurfaceGraph::set_range_x()
{
    const double scale_factor = 1.5;
    auto range = std::minmax_element(data_table.begin(), data_table.end(),
          [](const Point &px, const Point &py){
              return px.x < py.x;
          }
    );
    m_graph->axisX()->setRange(scale_factor * range.first->x, scale_factor * range.second->x);
}


void SurfaceGraph::set_range_y()
{
    const double scale_factor = 1.5;
    auto range = std::minmax_element(data_table.begin(), data_table.end(),
          [](const Point &px, const Point &py){
              return px.y < py.y;
          }
    );
    m_graph->axisY()->setRange(scale_factor * range.first->y, scale_factor * range.second->y);
}


void SurfaceGraph::set_range_z()
{
    const double scale_factor = 1.5;
    auto range = std::minmax_element(data_table.begin(), data_table.end(),
          [](const Point &px, const Point &py){
              return px.z < py.z;
          }
    );
    m_graph->axisZ()->setRange(scale_factor * range.first->z, scale_factor * range.second->z);
}


void SurfaceGraph::set_graph_details()
{
    set_range_x();
    set_range_y();
    set_range_z();

    m_PhotoLayerSeries->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
    m_PhotoLayerSeries->setFlatShadingEnabled(true);

    m_graph->axisX()->setLabelFormat("%.2f");
    m_graph->axisZ()->setLabelFormat("%.2f");

    m_graph->axisX()->setLabelAutoRotation(30);
    m_graph->axisY()->setLabelAutoRotation(90);
    m_graph->axisZ()->setLabelAutoRotation(30);

    m_graph->addSeries(m_PhotoLayerSeries);
}


void SurfaceGraph::rotateX(int rotation)
{
    m_xRotation = rotation;
    m_graph->scene()->activeCamera()->setCameraPosition(m_xRotation, m_yRotation);
}
void SurfaceGraph::rotateY(int rotation)
{
    m_yRotation = rotation;
    m_graph->scene()->activeCamera()->setCameraPosition(m_xRotation, m_yRotation);
}
