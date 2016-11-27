#include <QString>

#include "luminous-flux-window.h"
#include "ui_luminous-flux-window.h"

LuminousFluxWindow::LuminousFluxWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LuminousFluxWindow)
{
    ui->setupUi(this);
}

LuminousFluxWindow::~LuminousFluxWindow()
{
    delete ui;
}

void LuminousFluxWindow::on_CloseButton_clicked()
{
    this->close();
}

void LuminousFluxWindow::set_luminous_flux_value(double flux)
{
    //TODO: format to not show power values
    ui->luminousFluxValue->setText(QString::number(flux));
}

void LuminousFluxWindow::set_luminous_flux_units(QString units)
{
    ui->luminousUnitsName->setText(units);
}
