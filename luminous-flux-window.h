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
    explicit LuminousFluxWindow(double flux, QWidget *parent = 0);
    ~LuminousFluxWindow();

private slots:
    void on_CloseButton_clicked();

private:
    Ui::LuminousFluxWindow *ui;
};

#endif // LUMINOUSFLUXWINDOW_H
