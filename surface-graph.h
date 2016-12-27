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

    std::vector<Point> data_table;
    Q3DSurface *m_graph;
    QSurfaceDataProxy *m_sqrtSinProxy;
    QSurface3DSeries *m_sqrtSinSeries;
};

#endif // SURFACEGRAPH_H

