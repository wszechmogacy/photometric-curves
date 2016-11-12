#include <qpen.h>
#include <qwt_series_data.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_polar_grid.h>
#include <qwt_polar_curve.h>

#include <qwt_scale_engine.h>
#include "polar-graph-plot.h"

const QwtInterval radialInterval( 0.0, 10.0 );
const QwtInterval azimuthInterval( 0.0, 360.0 );

class Data: public QwtSeriesData<QwtPointPolar>
{
public:
    Data( const QwtInterval &radialInterval,
          const QwtInterval &azimuthInterval, size_t size ):
        d_radialInterval( radialInterval ),
        d_azimuthInterval( azimuthInterval ),
        d_size( size )
    {
    }

    virtual size_t size() const
    {
        return d_size;
    }

protected:
    QwtInterval d_radialInterval;
    QwtInterval d_azimuthInterval;
    size_t d_size;
};

class PolarData: public Data
{
public:
    PolarData( const QwtInterval &radialInterval,
            const QwtInterval &azimuthInterval, size_t size ):
        Data( radialInterval, azimuthInterval, size )
    {
    }

    virtual QwtPointPolar sample( size_t i ) const
    {
        const double stepA = 4 * d_azimuthInterval.width() / d_size;
        const double a = d_azimuthInterval.minValue() + i * stepA;

        const double stepR = d_radialInterval.width() / d_size;
        const double r = d_radialInterval.minValue() + i * stepR;

        return QwtPointPolar( a, r );
    }

    virtual QRectF boundingRect() const
    {
        if ( d_boundingRect.width() < 0.0 )
            d_boundingRect = qwtBoundingRect( *this );

        return d_boundingRect;
    }
};

PolarGraphPlot::PolarGraphPlot( QWidget *parent ):
    QwtPolarPlot( QwtText( "Polar Plot Demo" ), parent )
{
    setAutoReplot( false );
    setPlotBackground( Qt::darkBlue );

    // scales
    setScale( QwtPolar::Azimuth,
        azimuthInterval.minValue(), azimuthInterval.maxValue(),
        azimuthInterval.width() / 12 );

    setScaleMaxMinor( QwtPolar::Azimuth, 2 );
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
    const int numPoints = 200;

    QwtPolarCurve *curve = new QwtPolarCurve();
    curve->setStyle( QwtPolarCurve::Lines );
    curve->setTitle( "Spiral" );
    curve->setPen( QPen( Qt::yellow, 2 ) );
    curve->setSymbol( new QwtSymbol( QwtSymbol::Rect,
                                     QBrush( Qt::cyan ), QPen( Qt::white ), QSize( 3, 3 ) ) );
    curve->setData( new PolarData( radialInterval, azimuthInterval, numPoints ) );

    return curve;
}
