#ifndef SURFACEGRAPH_H
#define SURFACEGRAPH_H

#include <algorithm>
#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>

#include <point.h>
#include <vector>

using namespace QtDataVisualization;

class SurfaceGraph : public QObject
{
    Q_OBJECT
public:
    explicit SurfaceGraph(QString graph_name, Q3DSurface *surface, std::vector<Point> data, unsigned columns_count, unsigned rows_count);
    ~SurfaceGraph();
    void rotate_x(int rotation);
    void rotate_y(int rotation);

    void convert_point_on_meridian(std::vector<Point> data, unsigned i, int &index, QSurfaceDataRow *newRow, unsigned j);

private:
    void set_graph_details();
    void set_data(std::vector<Point> &data_table_);
    void set_range_x();
    void set_range_y();
    void set_range_z();

    unsigned sample_count_on_meridian_;
    unsigned sample_count_on_parallel_;
    std::vector<Point> data_table_;
    Q3DSurface *graph_;
    QSurfaceDataProxy *photo_layer_proxy_;
    QSurface3DSeries *photo_layer_series_;
    float x_rotation_;
    float y_rotation_;

};

#endif // SURFACEGRAPH_H

