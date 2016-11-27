#ifndef LUMINOUSFLUXWINDOW_H
#define LUMINOUSFLUXWINDOW_H

#include <QDialog>

namespace Ui {
class LuminousFluxWindow;
}

class LuminousFluxWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LuminousFluxWindow(QWidget *parent = 0);
    ~LuminousFluxWindow();

    void set_luminous_flux_value(double flux);
    void set_luminous_flux_units(QString units);

private slots:
    void on_CloseButton_clicked();

private:
    Ui::LuminousFluxWindow *ui;
};

#endif // LUMINOUSFLUXWINDOW_H
