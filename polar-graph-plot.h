#ifndef _PLOT_H_
#define _PLOT_H_ 1

#include <qwt_polar_plot.h>

class QwtPolarGrid;
class QwtPolarCurve;

class PolarGraphPlotSettings
{
public:
    enum Curve
    {
        Spiral,
        Rose,

        NumCurves
    };

    enum Flag
    {
        MajorGridBegin,
        MinorGridBegin = MajorGridBegin + QwtPolar::ScaleCount,
        AxisBegin = MinorGridBegin + QwtPolar::ScaleCount,

        AutoScaling = AxisBegin + QwtPolar::AxesCount,
        Inverted,
        Logarithmic,

        Antialiasing,

        CurveBegin,

        NumFlags = CurveBegin + NumCurves
    };

    bool flags[NumFlags];
};

class PolarGraphPlot: public QwtPolarPlot
{
    Q_OBJECT

public:
    PolarGraphPlot( QWidget * = NULL );
    PolarGraphPlotSettings settings() const;

public Q_SLOTS:
    void applySettings( const PolarGraphPlotSettings & );

private:
    QwtPolarCurve *createCurve( int id ) const;

    QwtPolarGrid *d_grid;
    QwtPolarCurve *d_curve[PolarGraphPlotSettings::NumCurves];
};

#endif


