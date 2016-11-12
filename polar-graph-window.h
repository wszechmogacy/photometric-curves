#include <qmainwindow.h>
#include <QWidget>


namespace Ui {
class MainWindow;
}

class PolarGraphPlot;
class PolarGraphSettingsEditor;
class QwtPolarPanner;
class QwtPolarMagnifier;

class PolarGraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    PolarGraphWindow( QWidget *parent = NULL );

private Q_SLOTS:
    void enableZoomMode( bool on );
    void printDocument();
    void exportDocument();

private:
    PolarGraphPlot *d_plot;
    QwtPolarPanner *d_panner;
    QwtPolarMagnifier *d_zoomer;
    PolarGraphSettingsEditor *d_settingsEditor;
};
