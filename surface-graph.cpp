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


SurfaceGraph::SurfaceGraph(Q3DSurface *surface, std::vector<Point> data)
    : m_graph(surface),
    data_table(data)
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
    auto sampleCountZ = data.size();
    std::sort(data.begin(), data.end());
    for (auto zm : data)
    {
        qDebug() << QString::number(zm.lat_angle_deg) << " " << QString::number(zm.lon_angle_deg);
    }

    size_t sampleCountX = 9;

    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(sampleCountZ);
    for (size_t i = 0 ; i < sampleCountZ ; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(sampleCountX);
        int index = 0;
        for (size_t j = 0; j < sampleCountX; j++) {
            (*newRow)[index++].setPosition(QVector3D(data[i].x, data[i].y, data[i].z));
        }
        *dataArray << newRow;
    }

    m_PhotoLayerProxy->resetArray(dataArray);

}

SurfaceGraph::~SurfaceGraph()
{
    delete m_graph;
}

void SurfaceGraph::set_graph_details()
{
    auto el_x = std::minmax_element(data_table.begin(), data_table.end(),
          [](const Point &px, const Point &py){
              return px.x < py.x;
          }
    );
    const float sampleMinX = el_x.first()->x;
    //const float sampleMinX = min_el_x->x;



    const float sampleMinZ = -8.0f;
    const float sampleMax = 8.0f;
    m_PhotoLayerSeries->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
    m_PhotoLayerSeries->setFlatShadingEnabled(true);

    m_graph->axisX()->setLabelFormat("%.2f");
    m_graph->axisZ()->setLabelFormat("%.2f");
    m_graph->axisX()->setRange(sampleMinX, sampleMax);
    m_graph->axisY()->setRange(0.0f, 2.0f);
    m_graph->axisZ()->setRange(sampleMinZ, sampleMax);
    m_graph->axisX()->setLabelAutoRotation(30);
    m_graph->axisY()->setLabelAutoRotation(90);
    m_graph->axisZ()->setLabelAutoRotation(30);

    m_graph->addSeries(m_PhotoLayerSeries);
}
