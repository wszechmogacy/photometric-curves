#include <QString>

#include <luminous-flux-window.h>
#include <ui_luminous-flux-window.h>

LuminousFluxWindow::LuminousFluxWindow(double flux, QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::LuminousFluxWindow)
{
    ui_->setupUi(this);
    ui_->closeButton->setText(tr("Close"));
    ui_->luminousFluxtxt->setTextInteractionFlags(Qt::TextSelectableByMouse);
    QString window_txt = "Luminous Flux = " + QString::number(flux * 683, 'g', 8) + " " + "lm";
    ui_->luminousFluxtxt->setText(window_txt);
}

LuminousFluxWindow::~LuminousFluxWindow()
{
    delete ui_;
}

void LuminousFluxWindow::on_closeButton_clicked()
{
   close();
}
