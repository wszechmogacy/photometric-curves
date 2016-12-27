#ifndef SURFACEGRAPH_H
#define SURFACEGRAPH_H

#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtWidgets/QSlider>

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

    void set_graph_details(bool enable);

    void set_data(std::vector<Point> &data_table);
    std::vector<Point> data_table;

public Q_SLOTS:
    void changeTheme(int theme);

private:
    Q3DSurface *m_graph;
    QHeightMapSurfaceDataProxy *m_heightMapProxy;
    QSurfaceDataProxy *m_sqrtSinProxy;
    QSurface3DSeries *m_heightMapSeries;
    QSurface3DSeries *m_sqrtSinSeries;

    QSlider *m_axisMaxSliderX;
    QSlider *m_axisMaxSliderZ;
    float m_rangeMinX;
    float m_rangeMinZ;
    float m_stepX;
    float m_stepZ;
    int m_heightMapWidth;
    int m_heightMapHeight;

};

#endif // SURFACEGRAPH_H

