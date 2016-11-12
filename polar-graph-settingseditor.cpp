#include <qcheckbox.h>
#include <qgroupbox.h>
#include <qlayout.h>
#include "polar-graph-settingseditor.h"

PolarGraphSettingsEditor::PolarGraphSettingsEditor( QWidget *parent ):
    QFrame( parent )
{
    QGroupBox *axesBox = new QGroupBox( "Axes", this );
    QVBoxLayout* axesBoxLayout = new QVBoxLayout( axesBox );
    axesBoxLayout->setMargin( 20 );


    for ( int i = PolarGraphPlotSettings::AxisBegin;
        i <= PolarGraphPlotSettings::Logarithmic; i++ )
    {
        d_checkBox[i] = new QCheckBox( axesBox );
        axesBoxLayout->addWidget( d_checkBox[i] );
    }

    QGroupBox *gridBox = new QGroupBox( "Grids", this );
    QVBoxLayout* gridBoxLayout = new QVBoxLayout( gridBox );
    gridBoxLayout->setMargin( 20 );

    for ( int scaleId = 0; scaleId < QwtPolar::ScaleCount; scaleId++ )
    {
        int idx = PolarGraphPlotSettings::MajorGridBegin + scaleId;
        d_checkBox[idx] = new QCheckBox( gridBox );
        gridBoxLayout->addWidget( d_checkBox[idx] );

        idx = PolarGraphPlotSettings::MinorGridBegin + scaleId;
        d_checkBox[idx] = new QCheckBox( gridBox );
        gridBoxLayout->addWidget( d_checkBox[idx] );
    }
    gridBoxLayout->addStretch( 10 );

    QGroupBox *otherBox = new QGroupBox( "Other", this );
    QVBoxLayout* otherBoxLayout = new QVBoxLayout( otherBox );
    otherBoxLayout->setMargin( 20 );

    for ( int i = PolarGraphPlotSettings::Logarithmic + 1;
        i < PolarGraphPlotSettings::NumFlags; i++ )
    {
        d_checkBox[i] = new QCheckBox( otherBox );
        otherBoxLayout->addWidget( d_checkBox[i] );
    }
    otherBoxLayout->addStretch( 10 );

    QVBoxLayout *layout = new QVBoxLayout( this );
    layout->addWidget( axesBox );
    layout->addWidget( gridBox );
    layout->addWidget( otherBox );
    layout->addStretch( 10 );

    for ( int i = 0; i < PolarGraphPlotSettings::NumFlags; i++ )
    {
        d_checkBox[i]->setText( label( i ) );
        connect( d_checkBox[i], SIGNAL( clicked() ), this, SLOT( edited() ) );
    }
}

void PolarGraphSettingsEditor::showSettings( const PolarGraphPlotSettings &settings )
{
    blockSignals( true );
    for ( int i = 0; i < PolarGraphPlotSettings::NumFlags; i++ )
        d_checkBox[i]->setChecked( settings.flags[i] );

    blockSignals( false );
    updateEditor();
}

PolarGraphPlotSettings PolarGraphSettingsEditor::settings() const
{
    PolarGraphPlotSettings s;
    for ( int i = 0; i < PolarGraphPlotSettings::NumFlags; i++ )
        s.flags[i] = d_checkBox[i]->isChecked();
    return s;
}

void PolarGraphSettingsEditor::edited()
{
    updateEditor();

    const PolarGraphPlotSettings s = settings();
    Q_EMIT edited( s );
}

void PolarGraphSettingsEditor::updateEditor()
{
    for ( int scaleId = 0; scaleId < QwtPolar::ScaleCount; scaleId++ )
    {
        d_checkBox[PolarGraphPlotSettings::MinorGridBegin+scaleId]->setEnabled(
            d_checkBox[PolarGraphPlotSettings::MajorGridBegin+scaleId]->isChecked() );
    }
}

QString PolarGraphSettingsEditor::label( int flag ) const
{
    switch( flag )
    {
        case PolarGraphPlotSettings::MajorGridBegin + QwtPolar::ScaleAzimuth:
            return "Azimuth";
        case PolarGraphPlotSettings::MajorGridBegin + QwtPolar::ScaleRadius:
            return "Radius";
        case PolarGraphPlotSettings::MinorGridBegin + QwtPolar::ScaleAzimuth:
            return "Azimuth Minor";
        case PolarGraphPlotSettings::MinorGridBegin + QwtPolar::ScaleRadius:
            return "Radius Minor";
        case PolarGraphPlotSettings::AxisBegin + QwtPolar::AxisAzimuth:
            return "Azimuth";
        case PolarGraphPlotSettings::AxisBegin + QwtPolar::AxisLeft:
            return "Left";
        case PolarGraphPlotSettings::AxisBegin + QwtPolar::AxisRight:
            return "Right";
        case PolarGraphPlotSettings::AxisBegin + QwtPolar::AxisTop:
            return "Top";
        case PolarGraphPlotSettings::AxisBegin + QwtPolar::AxisBottom:
            return "Bottom";
        case PolarGraphPlotSettings::AutoScaling:
            return "Auto Scaling";
        case PolarGraphPlotSettings::Inverted:
            return "Inverted";
        case PolarGraphPlotSettings::Logarithmic:
            return "Logarithmic";
        case PolarGraphPlotSettings::Antialiasing:
            return "Antialiasing";
        case PolarGraphPlotSettings::CurveBegin:
            return "Spiral Curve";
    }
    return QString();
}
