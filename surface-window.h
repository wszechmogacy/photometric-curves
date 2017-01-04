#ifndef SURFACEWINDOW_H
#define SURFACEWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QtDataVisualization/Q3DSurface>

#include <point.h>

using namespace QtDataVisualization;

class SurfaceWindow : public QWidget
{
     Q_OBJECT
public:
    SurfaceWindow(std::vector<Point> &data_table, unsigned columns_count, unsigned rows_count);
    Q3DSurface *graph;

public slots:
    void print_to_pdf();
};

#endif // SURFACEWINDOW_H
