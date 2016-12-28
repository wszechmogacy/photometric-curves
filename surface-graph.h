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
    explicit SurfaceGraph(Q3DSurface *surface, std::vector<Point> data);
    ~SurfaceGraph();

private:
    void set_graph_details();
    void set_data(std::vector<Point> &data_table);
    void set_range_x();
    void set_range_y();
    void set_range_z();

    std::vector<Point> data_table;
    Q3DSurface *m_graph;
    QSurfaceDataProxy *m_PhotoLayerProxy;
    QSurface3DSeries *m_PhotoLayerSeries;
};

#endif // SURFACEGRAPH_H

