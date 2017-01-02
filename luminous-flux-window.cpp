#include <QString>

#include "luminous-flux-window.h"
#include "ui_luminous-flux-window.h"

LuminousFluxWindow::LuminousFluxWindow(double flux, QString units, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LuminousFluxWindow)
{
    ui->setupUi(this);
    ui->luminousFluxtxt->setTextInteractionFlags(Qt::TextSelectableByMouse);
    QString window_txt = "Luminous Flux = " + QString::number(flux, 'g', 8) + " " + units;
    ui->luminousFluxtxt->setText(window_txt);
}

LuminousFluxWindow::~LuminousFluxWindow()
{
    delete ui;
}

void LuminousFluxWindow::on_CloseButton_clicked()
{
    this->close();
}
