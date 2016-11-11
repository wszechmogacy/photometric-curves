#include <qregexp.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qprinter.h>
#include <qprintdialog.h>
#include <qfiledialog.h>
#include <qimagewriter.h>
#include <qfileinfo.h>
#include <qlayout.h>
#ifdef QT_SVG_LIB
#include <qsvggenerator.h>
#endif
#include <qwt_polar_panner.h>
#include <qwt_polar_magnifier.h>
#include <qwt_polar_renderer.h>
#include "polar-graph-window.h"
#include "polar-graph-plot.h"
#include "polar-graph-settingseditor.h"
#include "polar-graph-pixmaps.h"

PolarGraphWindow::PolarGraphWindow( QWidget *parent ):
    QMainWindow( parent )
{
    QWidget *w = new QWidget( this );

    d_plot = new PolarGraphPlot( w );

    d_panner = new QwtPolarPanner( d_plot->canvas() );
    d_panner->setEnabled( false );

    d_zoomer = new QwtPolarMagnifier( d_plot->canvas() );
    d_zoomer->setEnabled( false );

    d_settingsEditor = new PolarGraphSettingsEditor( w );

    d_settingsEditor->showSettings( d_plot->settings() );
    connect( d_settingsEditor, SIGNAL( edited( const PolarGraphPlotSettings & ) ),
        d_plot, SLOT( applySettings( const PolarGraphPlotSettings & ) ) );

    QHBoxLayout *layout = new QHBoxLayout( w );
    layout->addWidget( d_settingsEditor, 0 );
    layout->addWidget( d_plot, 10 );

    setCentralWidget( w );

    QToolBar *toolBar = new QToolBar( this );

    QToolButton *btnZoom = new QToolButton( toolBar );

    const QString zoomHelp =
        "Use the wheel to zoom in/out.\n"
        "When the plot is zoomed in,\n"
        "use the left mouse button to m~/devel/qt/polardemo/ove it.";

    btnZoom->setText( "Zoom" );
    btnZoom->setIcon( QPixmap( zoom_xpm ) );
    btnZoom->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    btnZoom->setToolTip( zoomHelp );
    btnZoom->setCheckable( true );
    toolBar->addWidget( btnZoom );
    connect( btnZoom, SIGNAL( toggled( bool ) ), SLOT( enableZoomMode( bool ) ) );

    QToolButton *btnPrint = new QToolButton( toolBar );
    btnPrint->setText( "Print" );
    btnPrint->setIcon( QPixmap( print_xpm ) );
    btnPrint->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnPrint );
    connect( btnPrint, SIGNAL( clicked() ), SLOT( printDocument() ) );

#ifdef QT_SVG_LIB
    QToolButton *btnExport = new QToolButton( toolBar );
    btnExport->setText( "Export" );
    btnExport->setIcon( QPixmap( print_xpm ) );
    btnExport->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnExport );

    connect( btnExport, SIGNAL( clicked() ), SLOT( exportDocument() ) );
#endif

    addToolBar( toolBar );
}

void PolarGraphWindow::printDocument()
{
    QPrinter printer( QPrinter::HighResolution );

    QString docName = d_plot->title().text();
    if ( !docName.isEmpty() )
    {
        docName.replace ( QRegExp ( QString::fromLatin1 ( "\n" ) ), tr ( " -- " ) );
        printer.setDocName ( docName );
    }

    printer.setCreator( "polar plot demo example" );
    printer.setOrientation( QPrinter::Landscape );

    QPrintDialog dialog( &printer );
    if ( dialog.exec() )
    {
        QwtPolarRenderer renderer;
        renderer.renderTo( d_plot, printer );
    }
}

void PolarGraphWindow::exportDocument()
{
    QString fileName = "polarplot.pdf";

    QwtPolarRenderer renderer;
    renderer.exportTo( d_plot, "polarplot.pdf" );
}

void PolarGraphWindow::enableZoomMode( bool on )
{
    d_panner->setEnabled( on );
    d_zoomer->setEnabled( on );
}
