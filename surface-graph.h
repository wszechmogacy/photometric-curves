#ifndef SURFACEGRAPH_H
#define SURFACEGRAPH_H

#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>

#include <algorithm>
#include <point.h>
#include <vector>

using namespace QtDataVisualization;

class SurfaceGraph : public QObject
{
    Q_OBJECT
public:
    explicit SurfaceGraph(Q3DSurface *surface, std::vector<Point> data, unsigned columns_count, unsigned rows_count);
    ~SurfaceGraph();
    void rotateX(int rotation);
    void rotateY(int rotation);

    void convert_point_on_meridian(std::vector<Point> data, unsigned i, int &index, QSurfaceDataRow *newRow, unsigned j);

private:
    void set_graph_details();
    void set_data(std::vector<Point> &data_table);
    void set_range_x();
    void set_range_y();
    void set_range_z();
    unsigned sampleCountOnMeridian;
    unsigned sampleCountOnParallel;

    std::vector<Point> data_table;
    Q3DSurface *m_graph;
    QSurfaceDataProxy *m_PhotoLayerProxy;
    QSurface3DSeries *m_PhotoLayerSeries;
    float m_xRotation;
    float m_yRotation;

};

#endif // SURFACEGRAPH_H

