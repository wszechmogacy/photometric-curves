#ifndef _POLAR_GRAPH_SETTINGS_EDITOR_H_
#define _POLAR_GRAPH_SETTINGS_EDITOR_H_ 1

#include <qframe.h>
#include "polar-graph-plot.h"

class QCheckBox;

class PolarGraphSettingsEditor: public QFrame
{
    Q_OBJECT

public:
    PolarGraphSettingsEditor( QWidget *parent = NULL );

    void showSettings( const PolarGraphPlotSettings & );
    PolarGraphPlotSettings settings() const;

Q_SIGNALS:
    void edited( const PolarGraphPlotSettings& );

private Q_SLOTS:
    void edited();

private:
    void updateEditor();
    QString label( int flag ) const;

    QCheckBox *d_checkBox[PolarGraphPlotSettings::NumFlags];
};

#endif
