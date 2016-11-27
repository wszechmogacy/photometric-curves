#include <qpen.h>
#include <qwt_series_data.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_polar_grid.h>
#include <qwt_polar_curve.h>

#include <qwt_scale_engine.h>
#include "polar-graph-plot.h"


const QwtInterval azimuthInterval( 0.0, 360.0 );

class Data: public QwtSeriesData<QwtPointPolar>
{
public:
    Data( QList<QPointF> plot_data ):
        d_size( plot_data.size() ),
        d_data( plot_data )
    {
    }

    virtual size_t size() const
    {
        return d_size;
    }


protected:
    size_t d_size;
    QList<QPointF> d_data;
};

class PolarData: public Data
{
public:
    PolarData( QList<QPointF> plot_data ):
        Data( plot_data ),
        d_data( plot_data )
    {
    }
    QList<QPointF> d_data;

    virtual QwtPointPolar sample( size_t i ) const
    {
        return QwtPointPolar( d_data[i].y(), d_data[i].x() );
    }

    virtual QRectF boundingRect() const
    {
        if ( d_boundingRect.width() < 0.0 )
            d_boundingRect = qwtBoundingRect( *this );

        return d_boundingRect;
    }
};

PolarGraphPlot::PolarGraphPlot( QList<QPointF> &plot_data, QWidget *parent ):
    QwtPolarPlot( QwtText( "Name of curve, parameters, author" ), parent )
{
    d_data = plot_data;

    setAutoReplot( false );
    setPlotBackground( Qt::darkBlue );

    // scales
    setScale( QwtPolar::Azimuth,
        azimuthInterval.minValue(), azimuthInterval.maxValue(),
        azimuthInterval.width() / 12 );

    double max = 0.0;
    for(size_t i = 0; i < plot_data.size(); i++) {
        if (plot_data[i].x() > max) max = plot_data[i].x();
    }

    setScaleMaxMinor( QwtPolar::Azimuth, 2 );
    const double scale_factor = 1.1;
    const QwtInterval radialInterval( 0.0, max * scale_factor );
    setScale( QwtPolar::Radius,
        radialInterval.minValue(), radialInterval.maxValue() );

    // grids, axes

    d_grid = new QwtPolarGrid();
    d_grid->setPen( QPen( Qt::white ) );
    for ( int scaleId = 0; scaleId < QwtPolar::ScaleCount; scaleId++ )
    {
        d_grid->showGrid( scaleId );
        d_grid->showMinorGrid( scaleId );

        QPen minorPen( Qt::gray );
#if 0
        minorPen.setStyle( Qt::DotLine );
#endif
        d_grid->setMinorGridPen( scaleId, minorPen );
    }
    d_grid->setAxisPen( QwtPolar::AxisAzimuth, QPen( Qt::black ) );

    d_grid->showAxis( QwtPolar::AxisAzimuth, true );
    d_grid->showAxis( QwtPolar::AxisLeft, false );
    d_grid->showAxis( QwtPolar::AxisRight, true );
    d_grid->showAxis( QwtPolar::AxisTop, true );
    d_grid->showAxis( QwtPolar::AxisBottom, false );
    d_grid->showGrid( QwtPolar::Azimuth, true );
    d_grid->showGrid( QwtPolar::Radius, true );
    d_grid->attach( this );

    // curves
    d_curve = createCurve();
    d_curve->attach( this );

    QwtLegend *legend = new QwtLegend;
    insertLegend( legend,  QwtPolarPlot::BottomLegend );
}

PolarGraphPlotSettings PolarGraphPlot::settings() const
{
    PolarGraphPlotSettings s;
    for ( int scaleId = 0; scaleId < QwtPolar::ScaleCount; scaleId++ )
    {
        s.flags[PolarGraphPlotSettings::MajorGridBegin + scaleId] =
            d_grid->isGridVisible( scaleId );
        s.flags[PolarGraphPlotSettings::MinorGridBegin + scaleId] =
            d_grid->isMinorGridVisible( scaleId );
    }
    for ( int axisId = 0; axisId < QwtPolar::AxesCount; axisId++ )
    {
        s.flags[PolarGraphPlotSettings::AxisBegin + axisId] =
            d_grid->isAxisVisible( axisId );
    }

    s.flags[PolarGraphPlotSettings::AutoScaling] =
        d_grid->testGridAttribute( QwtPolarGrid::AutoScaling );

    s.flags[PolarGraphPlotSettings::Logarithmic] = 
        scaleEngine( QwtPolar::Radius )->transformation();

    const QwtScaleDiv *sd = scaleDiv( QwtPolar::Radius );
    s.flags[PolarGraphPlotSettings::Inverted] = sd->lowerBound() > sd->upperBound();

    s.flags[PolarGraphPlotSettings::Antialiasing] =
        d_grid->testRenderHint( QwtPolarItem::RenderAntialiased );

    s.flags[PolarGraphPlotSettings::CurveBegin] = d_curve->isVisible();

    return s;
}

void PolarGraphPlot::applySettings( const PolarGraphPlotSettings& s )
{
    for ( int scaleId = 0; scaleId < QwtPolar::ScaleCount; scaleId++ )
    {
        d_grid->showGrid( scaleId,
            s.flags[PolarGraphPlotSettings::MajorGridBegin + scaleId] );
        d_grid->showMinorGrid( scaleId,
            s.flags[PolarGraphPlotSettings::MinorGridBegin + scaleId] );
    }

    for ( int axisId = 0; axisId < QwtPolar::AxesCount; axisId++ )
    {
        d_grid->showAxis( axisId,
            s.flags[PolarGraphPlotSettings::AxisBegin + axisId] );
    }

    d_grid->setGridAttribute( QwtPolarGrid::AutoScaling,
        s.flags[PolarGraphPlotSettings::AutoScaling] );

    const QwtInterval interval =
        scaleDiv( QwtPolar::Radius )->interval().normalized();
    if ( s.flags[PolarGraphPlotSettings::Inverted] )
    {
        setScale( QwtPolar::Radius,
            interval.maxValue(), interval.minValue() );
    }
    else
    {
        setScale( QwtPolar::Radius,
            interval.minValue(), interval.maxValue() );
    }

    if ( s.flags[PolarGraphPlotSettings::Logarithmic] )
    {
        setScaleEngine( QwtPolar::Radius, new QwtLogScaleEngine() );
    }
    else
    {
        setScaleEngine( QwtPolar::Radius, new QwtLinearScaleEngine() );
    }

    d_grid->setRenderHint( QwtPolarItem::RenderAntialiased,
        s.flags[PolarGraphPlotSettings::Antialiasing] );

    d_curve->setRenderHint( QwtPolarItem::RenderAntialiased,
                            s.flags[PolarGraphPlotSettings::Antialiasing] );
    d_curve->setVisible(
                s.flags[PolarGraphPlotSettings::CurveBegin] );

    replot();
}

QwtPolarCurve *PolarGraphPlot::createCurve() const
{
    QwtPolarCurve *curve = new QwtPolarCurve();
    curve->setStyle( QwtPolarCurve::Lines );
    curve->setTitle( "Params of curve" );
    curve->setPen( QPen( Qt::red, 2 ) );
    curve->setSymbol( new QwtSymbol( QwtSymbol::Rect,
                                     QBrush( Qt::cyan ), QPen( Qt::white ), QSize( 3, 3 ) ) );

    PolarData *polar_data = new PolarData( d_data );
    curve->setData( polar_data );

    return curve;
}
